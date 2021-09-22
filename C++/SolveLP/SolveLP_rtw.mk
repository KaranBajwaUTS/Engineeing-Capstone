###########################################################################
## Makefile generated for component 'SolveLP'. 
## 
## Makefile     : SolveLP_rtw.mk
## Generated on : Tue Sep 21 15:41:21 2021
## Final product: .\SolveLP.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = SolveLP
MAKEFILE                  = SolveLP_rtw.mk
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2021a
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2021a\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
START_DIR                 = C:\Users\Administrator0\Documents\MATLAB\Capstone\codegen\lib\SolveLP
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
COMPILER_COMMAND_FILE     = SolveLP_rtw_comp.rsp
CMD_FILE                  = SolveLP_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1
MODELLIB                  = SolveLP.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2019 v16.0 | nmake (64-bit Windows)
# Supported Version(s):    16.0
# ToolchainInfo Version:   2021a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS /wd4251
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = .\SolveLP.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=SolveLP

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\SolveLP_data.cpp $(START_DIR)\rt_nonfinite.cpp $(START_DIR)\rtGetNaN.cpp $(START_DIR)\rtGetInf.cpp $(START_DIR)\SolveLP_initialize.cpp $(START_DIR)\SolveLP_terminate.cpp $(START_DIR)\SolveLP.cpp $(START_DIR)\fmincon.cpp $(START_DIR)\factoryConstruct.cpp $(START_DIR)\computeDualFeasError.cpp $(START_DIR)\computeComplError.cpp $(START_DIR)\xnrm2.cpp $(START_DIR)\loadProblem.cpp $(START_DIR)\computeConstraints_.cpp $(START_DIR)\computeFiniteDifferences.cpp $(START_DIR)\finDiffEvalAndChkErr.cpp $(START_DIR)\setProblemType.cpp $(START_DIR)\modifyOverheadPhaseOne_.cpp $(START_DIR)\driver.cpp $(START_DIR)\computeGradLag.cpp $(START_DIR)\updateWorkingSetForNewQP.cpp $(START_DIR)\xgeqp3.cpp $(START_DIR)\xzgeqp3.cpp $(START_DIR)\xzlarfg.cpp $(START_DIR)\xzlarf.cpp $(START_DIR)\computeQ_.cpp $(START_DIR)\xgemv.cpp $(START_DIR)\xtrsv.cpp $(START_DIR)\sortLambdaQP.cpp $(START_DIR)\saveJacobian.cpp $(START_DIR)\countsort.cpp $(START_DIR)\removeConstr.cpp $(START_DIR)\RemoveDependentIneq_.cpp $(START_DIR)\step.cpp $(START_DIR)\driver1.cpp $(START_DIR)\PresolveWorkingSet.cpp $(START_DIR)\feasibleX0ForWorkingSet.cpp $(START_DIR)\factorQR.cpp $(START_DIR)\maxConstraintViolation.cpp $(START_DIR)\phaseone.cpp $(START_DIR)\computeFval.cpp $(START_DIR)\linearForm_.cpp $(START_DIR)\iterate.cpp $(START_DIR)\computeGrad_StoreHx.cpp $(START_DIR)\computeFval_ReuseHx.cpp $(START_DIR)\xrotg.cpp $(START_DIR)\compute_deltax.cpp $(START_DIR)\xpotrf.cpp $(START_DIR)\partialColLDL3_.cpp $(START_DIR)\fullColLDL2_.cpp $(START_DIR)\solve.cpp $(START_DIR)\xgemm.cpp $(START_DIR)\feasibleratiotest.cpp $(START_DIR)\addAineqConstr.cpp $(START_DIR)\addBoundToActiveSetMatrix_.cpp $(START_DIR)\checkStoppingAndUpdateFval.cpp $(START_DIR)\addAeqConstr.cpp $(START_DIR)\relaxed.cpp $(START_DIR)\linesearch.cpp $(START_DIR)\test_exit.cpp $(START_DIR)\BFGSUpdate.cpp $(START_DIR)\SolveLP_rtwutil.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = SolveLP_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj SolveLP_initialize.obj SolveLP_terminate.obj SolveLP.obj fmincon.obj factoryConstruct.obj computeDualFeasError.obj computeComplError.obj xnrm2.obj loadProblem.obj computeConstraints_.obj computeFiniteDifferences.obj finDiffEvalAndChkErr.obj setProblemType.obj modifyOverheadPhaseOne_.obj driver.obj computeGradLag.obj updateWorkingSetForNewQP.obj xgeqp3.obj xzgeqp3.obj xzlarfg.obj xzlarf.obj computeQ_.obj xgemv.obj xtrsv.obj sortLambdaQP.obj saveJacobian.obj countsort.obj removeConstr.obj RemoveDependentIneq_.obj step.obj driver1.obj PresolveWorkingSet.obj feasibleX0ForWorkingSet.obj factorQR.obj maxConstraintViolation.obj phaseone.obj computeFval.obj linearForm_.obj iterate.obj computeGrad_StoreHx.obj computeFval_ReuseHx.obj xrotg.obj compute_deltax.obj xpotrf.obj partialColLDL3_.obj fullColLDL2_.obj solve.obj xgemm.obj feasibleratiotest.obj addAineqConstr.obj addBoundToActiveSetMatrix_.obj checkStoppingAndUpdateFval.obj addAeqConstr.obj relaxed.obj linesearch.obj test_exit.obj BFGSUpdate.obj SolveLP_rtwutil.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = /source-charset:utf-8
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = /source-charset:utf-8
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{C:\Users\Administrator0\Documents\MATLAB\Capstone}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{C:\Users\Administrator0\Documents\MATLAB\Capstone}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


SolveLP_data.obj : $(START_DIR)\SolveLP_data.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SolveLP_data.cpp


rt_nonfinite.obj : $(START_DIR)\rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rt_nonfinite.cpp


rtGetNaN.obj : $(START_DIR)\rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rtGetNaN.cpp


rtGetInf.obj : $(START_DIR)\rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rtGetInf.cpp


SolveLP_initialize.obj : $(START_DIR)\SolveLP_initialize.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SolveLP_initialize.cpp


SolveLP_terminate.obj : $(START_DIR)\SolveLP_terminate.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SolveLP_terminate.cpp


SolveLP.obj : $(START_DIR)\SolveLP.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SolveLP.cpp


fmincon.obj : $(START_DIR)\fmincon.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\fmincon.cpp


factoryConstruct.obj : $(START_DIR)\factoryConstruct.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\factoryConstruct.cpp


computeDualFeasError.obj : $(START_DIR)\computeDualFeasError.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeDualFeasError.cpp


computeComplError.obj : $(START_DIR)\computeComplError.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeComplError.cpp


xnrm2.obj : $(START_DIR)\xnrm2.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xnrm2.cpp


loadProblem.obj : $(START_DIR)\loadProblem.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\loadProblem.cpp


computeConstraints_.obj : $(START_DIR)\computeConstraints_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeConstraints_.cpp


computeFiniteDifferences.obj : $(START_DIR)\computeFiniteDifferences.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeFiniteDifferences.cpp


finDiffEvalAndChkErr.obj : $(START_DIR)\finDiffEvalAndChkErr.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\finDiffEvalAndChkErr.cpp


setProblemType.obj : $(START_DIR)\setProblemType.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\setProblemType.cpp


modifyOverheadPhaseOne_.obj : $(START_DIR)\modifyOverheadPhaseOne_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\modifyOverheadPhaseOne_.cpp


driver.obj : $(START_DIR)\driver.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\driver.cpp


computeGradLag.obj : $(START_DIR)\computeGradLag.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeGradLag.cpp


updateWorkingSetForNewQP.obj : $(START_DIR)\updateWorkingSetForNewQP.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\updateWorkingSetForNewQP.cpp


xgeqp3.obj : $(START_DIR)\xgeqp3.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xgeqp3.cpp


xzgeqp3.obj : $(START_DIR)\xzgeqp3.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xzgeqp3.cpp


xzlarfg.obj : $(START_DIR)\xzlarfg.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xzlarfg.cpp


xzlarf.obj : $(START_DIR)\xzlarf.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xzlarf.cpp


computeQ_.obj : $(START_DIR)\computeQ_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeQ_.cpp


xgemv.obj : $(START_DIR)\xgemv.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xgemv.cpp


xtrsv.obj : $(START_DIR)\xtrsv.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xtrsv.cpp


sortLambdaQP.obj : $(START_DIR)\sortLambdaQP.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\sortLambdaQP.cpp


saveJacobian.obj : $(START_DIR)\saveJacobian.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\saveJacobian.cpp


countsort.obj : $(START_DIR)\countsort.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\countsort.cpp


removeConstr.obj : $(START_DIR)\removeConstr.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\removeConstr.cpp


RemoveDependentIneq_.obj : $(START_DIR)\RemoveDependentIneq_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\RemoveDependentIneq_.cpp


step.obj : $(START_DIR)\step.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\step.cpp


driver1.obj : $(START_DIR)\driver1.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\driver1.cpp


PresolveWorkingSet.obj : $(START_DIR)\PresolveWorkingSet.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\PresolveWorkingSet.cpp


feasibleX0ForWorkingSet.obj : $(START_DIR)\feasibleX0ForWorkingSet.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\feasibleX0ForWorkingSet.cpp


factorQR.obj : $(START_DIR)\factorQR.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\factorQR.cpp


maxConstraintViolation.obj : $(START_DIR)\maxConstraintViolation.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\maxConstraintViolation.cpp


phaseone.obj : $(START_DIR)\phaseone.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\phaseone.cpp


computeFval.obj : $(START_DIR)\computeFval.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeFval.cpp


linearForm_.obj : $(START_DIR)\linearForm_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\linearForm_.cpp


iterate.obj : $(START_DIR)\iterate.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\iterate.cpp


computeGrad_StoreHx.obj : $(START_DIR)\computeGrad_StoreHx.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeGrad_StoreHx.cpp


computeFval_ReuseHx.obj : $(START_DIR)\computeFval_ReuseHx.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\computeFval_ReuseHx.cpp


xrotg.obj : $(START_DIR)\xrotg.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xrotg.cpp


compute_deltax.obj : $(START_DIR)\compute_deltax.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\compute_deltax.cpp


xpotrf.obj : $(START_DIR)\xpotrf.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xpotrf.cpp


partialColLDL3_.obj : $(START_DIR)\partialColLDL3_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\partialColLDL3_.cpp


fullColLDL2_.obj : $(START_DIR)\fullColLDL2_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\fullColLDL2_.cpp


solve.obj : $(START_DIR)\solve.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\solve.cpp


xgemm.obj : $(START_DIR)\xgemm.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\xgemm.cpp


feasibleratiotest.obj : $(START_DIR)\feasibleratiotest.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\feasibleratiotest.cpp


addAineqConstr.obj : $(START_DIR)\addAineqConstr.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\addAineqConstr.cpp


addBoundToActiveSetMatrix_.obj : $(START_DIR)\addBoundToActiveSetMatrix_.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\addBoundToActiveSetMatrix_.cpp


checkStoppingAndUpdateFval.obj : $(START_DIR)\checkStoppingAndUpdateFval.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\checkStoppingAndUpdateFval.cpp


addAeqConstr.obj : $(START_DIR)\addAeqConstr.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\addAeqConstr.cpp


relaxed.obj : $(START_DIR)\relaxed.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\relaxed.cpp


linesearch.obj : $(START_DIR)\linesearch.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\linesearch.cpp


test_exit.obj : $(START_DIR)\test_exit.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\test_exit.cpp


BFGSUpdate.obj : $(START_DIR)\BFGSUpdate.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\BFGSUpdate.cpp


SolveLP_rtwutil.obj : $(START_DIR)\SolveLP_rtwutil.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SolveLP_rtwutil.cpp


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


