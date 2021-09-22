//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_SolveLP_api.cpp
//
// Code generation for function 'SolveLP'
//

// Include files
#include "_coder_SolveLP_api.h"
#include "_coder_SolveLP_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131610U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "SolveLP",                                            // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real_T b_emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *tariff_rate,
                                 const char_T *identifier);

static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static const mxArray *b_emlrt_marshallOut(const real_T u[25]);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[24];

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *load_values,
                                 const char_T *identifier))[24];

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[24];

static const mxArray *emlrt_marshallOut(const real_T u[24]);

// Function Definitions
static real_T b_emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *tariff_rate,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(tariff_rate), &thisId);
  emlrtDestroyArray(&tariff_rate);
  return y;
}

static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = d_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *b_emlrt_marshallOut(const real_T u[25])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 25};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[24]
{
  static const int32_T dims[2]{1, 24};
  real_T(*ret)[24];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[24])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp,
                                 const mxArray *load_values,
                                 const char_T *identifier))[24]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[24];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(load_values), &thisId);
  emlrtDestroyArray(&load_values);
  return y;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[24]
{
  real_T(*y)[24];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u[24])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 24};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

void SolveLP_api(const mxArray *const prhs[10], int32_T nlhs,
                 const mxArray *plhs[3])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*soc)[25];
  real_T(*battery_flow)[24];
  real_T(*cost_values)[24];
  real_T(*costs)[24];
  real_T(*initial_solution)[24];
  real_T(*load_values)[24];
  real_T(*res_values)[24];
  real_T battery_initial_soc;
  real_T battery_max_discharge;
  real_T battery_maximum_soc;
  real_T battery_minimum_soc;
  real_T battery_size;
  real_T tariff_rate;
  st.tls = emlrtRootTLSGlobal;
  battery_flow = (real_T(*)[24])mxMalloc(sizeof(real_T[24]));
  soc = (real_T(*)[25])mxMalloc(sizeof(real_T[25]));
  costs = (real_T(*)[24])mxMalloc(sizeof(real_T[24]));
  // Marshall function inputs
  load_values = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "load_values");
  cost_values = emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "cost_values");
  res_values = emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "res_values");
  tariff_rate = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "tariff_rate");
  battery_size = b_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "battery_size");
  battery_initial_soc =
      b_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "battery_initial_soc");
  battery_minimum_soc =
      b_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "battery_minimum_soc");
  battery_maximum_soc =
      b_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "battery_maximum_soc");
  battery_max_discharge =
      b_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "battery_max_discharge");
  initial_solution =
      emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "initial_solution");
  // Invoke the target function
  SolveLP(*load_values, *cost_values, *res_values, tariff_rate, battery_size,
          battery_initial_soc, battery_minimum_soc, battery_maximum_soc,
          battery_max_discharge, *initial_solution, *battery_flow, *soc,
          *costs);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*battery_flow);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*soc);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(*costs);
  }
}

void SolveLP_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  SolveLP_xil_terminate();
  SolveLP_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void SolveLP_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void SolveLP_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (_coder_SolveLP_api.cpp)
