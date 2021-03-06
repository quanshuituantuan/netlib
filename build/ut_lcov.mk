## Parameter
ifeq (,$(strip $(LCOV_OBJS_ROOT)))
ifeq (,$(strip $(TU_INTERMEDIATE_DIR)))
$(error please define LCOV_OBJS_ROOT to root dir contains obj files.)
else
LCOV_OBJS_ROOT := $(TU_INTERMEDIATE_DIR)
endif
endif

ifeq (,$(strip $(LCOV_SRC_PATTERNS)))
$(error please define LCOV_SRC_PATTERNS to extract src files.)
endif

### the directory where gcc executed
ifeq (,$(strip $(LCOV_BASE_DIR)))
LCOV_BASE_DIR := .
endif

## Configuration
LCOV_TOOL_DIR:=${VOBTAG}/SS_ILThirdpart/lcov-1.11
LCOV_BIN:=$(LCOV_TOOL_DIR)/bin/lcov
LCOV_GENHTML:=$(LCOV_TOOL_DIR)/bin/genhtml

LCOV_OUTPUT_DIR:=lcov_report
LCOV_OUTPUT_FILE:=$(LCOV_OUTPUT_DIR)/lcov.report.txt
LCOV_ENABLE_BRANCH_COV:=--rc lcov_branch_coverage=1
LCOV_C_CPP_FILES := '*.c' '*.cpp' '*.cxx' '*.h' '*.hpp' '*.hxx'

LDFLAGS += -lgcov
ifneq (,$(strip $(filter "coverage","$(MAKECMDGOALS)") $(filter "y","$(gcov)")))
CPPFLAGS += -fprofile-arcs -ftest-coverage
endif

CPPFLAGS += -D__NO_TIME_TYPE
CXXFLAGS += $(CPPFLAGS) $(LIB) -fpermissive
CFLAGS += $(CPPFLAGS) $(LIB)

ifeq ($(strip $(TNSDLUNIT_HOME)), ${VOBTAG}/SS_ILThirdpart/tnsdlunit/2.4-5)
SDL_FILES := $(TU_PRB_SRC_DIR)/$(PRB_MAIN_TNSDL)
sdl_files_exist = $(shell if [ -f $(SDL_FILES) ]; then echo "exist"; else echo "notexist"; fi;)
endif

## Target
.PHONY: coverage clean_coverage
clean_coverage:
        -$(SILENCE)rm -rf $(LCOV_OUTPUT_DIR)

clean: clean_coverage

coverage:
	-$(SILENCE)mkdir -p $(LCOV_OUTPUT_DIR)
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_FILE) -c -b $(LCOV_BASE_DIR) $(foreach x,$(LCOV_OBJS_ROOT),-d $x)
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_FILE) -e $(LCOV_OUTPUT_FILE) $(LCOV_SRC_PATTERNS)
ifneq (,$(strip $(LCOV_REMOVE_PATTERNS)))
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_FILE) -r $(LCOV_OUTPUT_FILE) $(LCOV_REMOVE_PATTERNS)
endif


ifeq ($(strip $(TNSDLUNIT_HOME)), ${VOBTAG}/SS_ILThirdpart/tnsdlunit/2.4-5)
	-$(SILENCE)mkdir -p $(LCOV_OUTPUT_DIR)/C $(LCOV_OUTPUT_DIR)/TNSDL
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/cpp.lcov -e $(LCOV_OUTPUT_FILE) $(LCOV_C_CPP_FILES)
	-$(SILENCE)$(LCOV_GENHTML) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/C $(LCOV_OUTPUT_DIR)/cpp.lcov
ifeq ($(sdl_files_exist), exist)
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/tnsdl.lcov -e $(LCOV_OUTPUT_FILE) '*.sdl'
	-$(SILENCE)$(LCOV_GENHTML) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/TNSDL $(LCOV_OUTPUT_DIR)/tnsdl.lcov
endif
else
ifdef TNSDL_OPT
	-$(SILENCE)mkdir -p $(LCOV_OUTPUT_DIR)/TNSDL
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/tnsdl.lcov -e $(LCOV_OUTPUT_FILE) '*.sdl' $(LCOV_C_CPP_FILES)
	-$(SILENCE)$(LCOV_GENHTML) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/TNSDL $(LCOV_OUTPUT_DIR)/tnsdl.lcov
else
	-$(SILENCE)mkdir -p $(LCOV_OUTPUT_DIR)/C
	-$(SILENCE)$(LCOV_BIN) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/cpp.lcov -e $(LCOV_OUTPUT_FILE) $(LCOV_C_CPP_FILES)
	-$(SILENCE)$(LCOV_GENHTML) $(LCOV_ENABLE_BRANCH_COV) -o $(LCOV_OUTPUT_DIR)/C $(LCOV_OUTPUT_DIR)/cpp.lcov
endif
endif