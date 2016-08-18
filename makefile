ifeq ($(OSTYPE),cygwin)
	CLEANUP=rm -rf
	MKDIR=mkdir -p
	TARGET_EXTENSION=out
else ifeq ($(OS),Windows_NT)
	CLEANUP=rm -rf
	MKDIR=mkdir
	TARGET_EXTENSION=exe
else
	CLEANUP=rm -rf
	MKDIR=mkdir -p
	TARGET_EXTENSION=out
endif
##########################################################################
## Includes +
##########################################################################
LIB_INCLUDE:= $(shell ls -d lib/*/ lib/)
SRC_INCLUDE:= $(shell ls -d src/*/ src/)
INCLUDES= $(subst lib,-Ilib,$(LIB_INCLUDE)) $(subst src,-Isrc,$(SRC_INCLUDE)) 
##########################################################################
## Commands +
##########################################################################
DEPEND=gcc -MM -MG -MF
LINK=gcc
COMPILE=gcc -Wall -c 
CFLAGS= $(INCLUDES)
##########################################################################
## Functions
##########################################################################
define changeSuffix
	$(addsuffix $(2),$(basename $(notdir $(1))))
endef
define getSourceFile_d 
	$(subst .exe,.c,$(notdir $(1)))
endef
##########################################################################
## Variables
##########################################################################
MAINSRC := $(shell ls src/*.c src/*/*.c)
MAINOBJ := $(foreach dir,$(MAINSRC),$(subst .c,.o,test/build/obj/$(shell basename $(dir))))
TESTSRC := $(shell ls test/src/*.c)
TEMPOBJ := $(subst test/src/, test/build/obj/, $(TESTSRC))
TESTOBJ := $(subst .c,.o ,$(TEMPOBJ))
TESTDEP := $(subst .c,.d ,$(TEMPOBJ))
TEMPBIN := $(subst test/src/, test/build/bin/, $(TESTSRC))
TESTBIN := $(subst .c,.exe ,$(TEMPBIN))
LIBSRC := $(-shell ls lib/*.c lib/*/*.c)
##########################################################################
#@echo -e $(join $(PATHOBJ),$(call changeSuffix,test/build/bin/TestLcdController.exe,.o))
PATHOBJ:=test/build/obj/
PATH_TSRC:=test/src/
BUILDPATHS=test/build/ test/build/bin/ test/build/obj/ test/build/reports/

test : $(TESTOBJ)
	@echo -e "-----------------------"
	@echo -e "Target : 1 $<"
	@echo -e "-----------------------"
	
%.o : $(TESTDEP)
	@echo -e "-----------------------"
	@echo -e "Target : 2 $@"
	@echo -e "-----------------------"

	
%.d	: $(join $(PATH_TSRC),$(call changeSuffix,%.d,.c))
	@echo -e "-----------------------"
	@echo -e "Target : 3 $@"
	@echo -e $(join $(PATH_TSRC),$(call changeSuffix,$@,.c))
	@echo -e "-----------------------"
	
$(PATHB):
	mkdir $@

$(PATHOBJ):
	mkdir $@

$(PATHBIN):
	mkdir $@

$(PATHR):
	mkdir $@

clean :
	$(CLEANUP) $(PATHOBJ)*.o
	$(CLEANUP) $(PATHOBJ)*.d
	$(CLEANUP) $(PATHBIN)*.exe
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(LIBRARY)*/build/*.o
	
.PHONY: clean test	