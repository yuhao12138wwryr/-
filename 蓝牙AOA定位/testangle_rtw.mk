###########################################################################
## Makefile generated for MATLAB file/project 'testangle'. 
## 
## Makefile     : testangle_rtw.mk
## Generated on : Sun Jun 18 15:58:11 2023
## MATLAB Coder version: 3.4 (R2017b)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/testangle.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.
# GEN_LINKER_RESPONSE     Command to generate a linker response file 
# CMD_FILE                Command file

PRODUCT_NAME              = testangle
MAKEFILE                  = testangle_rtw.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = D:/MATLAB2017b
MATLAB_BIN                = D:/MATLAB2017b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = D:/MATLAB2017b/work/xianche/ceshixintianxian
ARCH                      = win64
RELATIVE_PATH_TO_ANCHOR   = .
GEN_LINKER_RESPONSE       = $(MATLAB_ARCH_BIN)/createResponseFile.exe 1 
CMD_FILE                  = $(PRODUCT_NAME).rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   R2017b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64
MEX_OPTS_FILE      = $(MATLAB_ROOT/rtw/c/tools/lcc-win64.xml

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              =
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           = -win64 $(MEX_SRC) $(MEX_OPT_FILE)$(INCLUDES) -outdir $(RELATIVE_PATH_TO_ANCHOR)
MEX_LDFLAGS          = LINKFLAGS="$$LINKFLAGS $(LDFLAGS_ADDITIONAL)"
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE)

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
EXE_EXT             = .exe
SHAREDLIB_EXT       = .dll
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/testangle.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle -I$(MATLAB_ROOT)/work/xianche/ceshixintianxian -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=testangle -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/testangle_rtwutil.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/testangle_initialize.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/testangle_terminate.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/testangle.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/Angle2.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/atan.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/abs.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/sum.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/exp.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/diag.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/eig.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/anyNonFinite.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/isfinite.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/ishermitian.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/schur.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/triu.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xgehrd.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzlarfg.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xnrm2.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/sqrt.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xdlapy3.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xscal.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/recip.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzlarf.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xgemv.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xgerc.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xungorghr.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xhseqr.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzhseqr.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/relop.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzgeev.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzggev.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzlangeM.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzlascl.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzggbal.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzgghrd.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzlartg.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzhgeqz.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xztgevc.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/xzggbak.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/sort1.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/fliplr.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/kron.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/testangle_emxutil.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/rt_nonfinite.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/rtGetNaN.c $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/rtGetInf.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = testangle_rtwutil.obj testangle_initialize.obj testangle_terminate.obj testangle.obj Angle2.obj atan.obj abs.obj sum.obj exp.obj diag.obj eig.obj anyNonFinite.obj isfinite.obj ishermitian.obj schur.obj triu.obj xgehrd.obj xzlarfg.obj xnrm2.obj sqrt.obj xdlapy3.obj xscal.obj recip.obj xzlarf.obj xgemv.obj xgerc.obj xungorghr.obj xhseqr.obj xzhseqr.obj relop.obj xzgeev.obj xzggev.obj xzlangeM.obj xzlascl.obj xzggbal.obj xzgghrd.obj xzlartg.obj xzhgeqz.obj xztgevc.obj xzggbak.obj sort1.obj fliplr.obj kron.obj testangle_emxutil.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj

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

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	$(GEN_LINKER_RESPONSE) $(CMD_FILE) $(subst /,\,$(OBJS))
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) /out:$(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"
	$(RM) $(CMD_FILE)


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/work/xianche/ceshixintianxian/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/work/xianche/ceshixintianxian/codegen/lib/testangle/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


