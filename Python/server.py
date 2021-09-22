import base64
import http.server
import io
import json
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as plticker
import pandas as pd
import random
from socketserver import ThreadingMixIn
import subprocess
from urllib.parse import urlparse
from urllib.parse import parse_qs


matplotlib.use('Agg')
loc = plticker.MultipleLocator(base=1)
hours_range = range(0,24)

class ThreadingSimpleServer(ThreadingMixIn, http.server.HTTPServer):
    pass

class MyHttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):          
        if self.path == '/' or self.path.startswith('/index.html'):
            self.path = 'index.html'
            return http.server.SimpleHTTPRequestHandler.do_GET(self)
        elif self.path.startswith('/generate?'):

            query_components = parse_qs(urlparse(self.path).query)
            
            input_data = dict()
            input_data["loads"] = [float(n.strip()) for n in query_components["loads"][0].split(',')][0:24]
            input_data["costs"] = [float(n.strip()) for n in query_components["costs"][0].split(',')][0:24]
            input_data["res"] = [float(n.strip()) for n in query_components["res"][0].split(',')][0:24]
            input_data["tariff_rate"] = float(query_components["tariff_rate"][0])

            input_data["battery"] = dict()
            input_data["battery"]["size"] = float(query_components["battery_size"][0])
            input_data["battery"]["initial_soc"] = float(query_components["battery_initial_soc"][0])
            input_data["battery"]["maximum_soc"] = float(query_components["battery_maximum_soc"][0])
            input_data["battery"]["minimum_soc"] = float(query_components["battery_minimum_soc"][0])
            input_data["battery"]["maximum_discharge"] = float(query_components["battery_max_power_flow"][0])


            converge = False
            converge_counter = 1
            while not converge:
                if 'random_initial_solution' in query_components:
                    input_data["initial_solution"] = [1*random.randint(0, int(input_data["battery"]["maximum_discharge"]*.95)) for i in hours_range]
                else:
                    input_data["initial_solution"] = [0 for i in hours_range]
                    converge = True
                
                with open('capstone.json', 'w') as f:
                    json.dump(input_data, f)
                
                subprocess.call('capstone.exe')
                
                with open('output.json') as f:
                    output_data = json.load(f)
                    if round(output_data["soc"][0],1) == round(output_data["soc"][-1],1):
                        converge = True
                    else:
                        converge = False
                        converge_counter+=1

            html = '<html><center>'

            plt.clf()
            
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()

            costs = output_data["costs"]

            ax1 = pd.Series(data=costs, index=hours_range).plot(figsize=(12,8), label='Optimised', marker='o')
            pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] for i in hours_range], index=hours_range).cumsum().plot(ax=ax1, label='Unoptimised (Not using RES)', marker='o')
            pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] - input_data["res"][i]*input_data["tariff_rate"] for i in hours_range], index=hours_range).cumsum().plot(ax=ax1, label='Unoptimised (Using RES)', marker='o')
            ax1.legend()
            ax1.set_xlabel('Hour')
            ax1.set_ylabel('Cost ($)')
            ax1.xaxis.set_major_locator(loc)
            ax1.grid(color='gray', alpha=0.25)  
            ax1.set_title('Optimisation results',fontsize=18)
            ax1.axhline(costs[-1], color='gray', alpha=0.5)
            ax1.axhline(pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] for i in hours_range], index=hours_range).cumsum().iat[-1], color='gray', alpha=0.5)
            ax1.axhline(pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] - input_data["res"][i]*input_data["tariff_rate"] for i in hours_range], index=hours_range).cumsum().iat[-1], color='gray', alpha=0.5)
            ax1.axhline(0, color='black')
            ax1.set_xlim(0,23)
            
            pic_IObytes = io.BytesIO()
            plt.savefig(pic_IObytes, bbox_inches='tight', format='png')
            pic_IObytes.seek(0)
            base64_data = base64.b64encode(pic_IObytes.read()).decode("utf-8").replace("\n", "")
            html += '<br><img src="data:image/png;base64, ' + base64_data + '">'
            html += '<br><br>' + 'The total cost with no optimisation and using no RES is $' + str(round(pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] for i in hours_range], index=hours_range).cumsum().iat[-1],2))
            html += '<br>The total cost with no optimisation and using RES is $' + str(round(pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] - input_data["res"][i]*input_data["tariff_rate"] for i in hours_range], index=hours_range).cumsum().iat[-1],2))
            html += '<br>The total cost with optimisation using RES and BESS is $' + str(round(costs[-1],2))
            if 'random_initial_solution' in query_components:
                html += '<br><br>The initial solution is [' + ', '.join([str(i) for i in input_data["initial_solution"]]) + ']'
                html += '<br>Took ' + str(converge_counter) + ' attempts to find a converging solution.' 

            plt.clf()

            ax2 = pd.Series(data=input_data["loads"], index=hours_range).plot(figsize=(12,8), marker='o', label="Load", alpha=0.33)
            pd.Series(data=input_data["res"], index=hours_range).plot(marker='o', label="RES power", ax=ax2, alpha=0.33)
            pd.Series(data=output_data["battery_power"], index=hours_range).plot(marker='o', label="Battery power", ax=ax2)
            pd.Series(data=[i*100 for i in input_data["costs"]], index=hours_range).plot(marker='o', label="Hourly cost (c)", ax=ax2, alpha=0.33)
            pd.Series(data=[soc*100 for soc in output_data["soc"]], index=range(0,25)).plot(marker='o', label='Battery state of charge (SOC)', ax=ax2)
            
            ax2.axhline(input_data["tariff_rate"]*100, color='b', alpha=0.5)
            ax2.axhline(0, color='black')
            ax2.legend()
            ax2.set_xlabel('Hour')
            ax2.xaxis.set_major_locator(loc)
            ax2.grid(color='gray', alpha=0.25)
            ax2.set_xlim(0,24)

            pic_IObytes = io.BytesIO()
            plt.savefig(pic_IObytes, bbox_inches='tight', format='png')
            pic_IObytes.seek(0)
            base64_data = base64.b64encode(pic_IObytes.read()).decode("utf-8").replace("\n", "")
            html += '<br><br><img src="data:image/png;base64, ' + base64_data + '">'
            plt.clf()

            hourly_costs = [costs[0]]
            for i in range(1, len(costs)):
                hourly_costs.append(costs[i]-costs[i-1])
            ax3 = pd.Series(data=hourly_costs, index=hours_range).plot(figsize=(12,8), label='Optimised cost', marker='o')
            pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] for i in hours_range], index=hours_range).plot(ax=ax3, label='Unoptimised (Not using RES) cost', marker='o')
            pd.Series(data=[input_data["loads"][i]*input_data["costs"][i] - input_data["res"][i]*input_data["tariff_rate"] for i in hours_range], index=hours_range).plot(ax=ax3, label='Unoptimised (Using RES) cost', marker='o')
            ax3.axhline(0, color='black')
            ax3.legend()
            ax3.set_xlabel('Hour')
            ax3.set_ylabel('Cost ($)')
            ax3.set_title('Cost ($) for each hour of operation',fontsize=18)
            ax3.xaxis.set_major_locator(loc)
            ax3.grid(color='gray', alpha=0.25)
            ax3.set_xlim(0,23)
            

            pic_IObytes = io.BytesIO()
            plt.savefig(pic_IObytes, bbox_inches='tight', format='png')
            pic_IObytes.seek(0)
            base64_data = base64.b64encode(pic_IObytes.read()).decode("utf-8").replace("\n", "")
            html += '<br><br><img src="data:image/png;base64, ' + base64_data + '">'

            html += '</center></html>'
            self.wfile.write(bytes(html, "utf8"))
        else:
            return http.server.SimpleHTTPRequestHandler.do_GET(self)

PORT = 80
handler = MyHttpRequestHandler

server = ThreadingSimpleServer(("", PORT), handler)
server.serve_forever()
