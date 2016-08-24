#################################### MAKEFILE ##################################
################################################################################
## Configurations
################################################################################
TEST_SOURCES := $(foreach tSrc,$(shell ls src/*.c), $(notdir $(tSrc)))
LIB_INCLUDE:=lib/include/ lib/
SRC_INCLUDE:= $(shell ls -d ../src/*/ ../src/)
BSP_INCLUDE:=../../mBlaze_BSP/microblaze_0/include/
SRC_HEADERS:= $(shell ls ../src/*/*.h ../src/*.h)
INCLUDES:=  $(subst ../src, -I../src,$(SRC_INCLUDE)) \
			$(subst lib, -Ilib,$(LIB_INCLUDE)) -I$(BSP_INCLUDE)
V_SRC:=$(patsubst -I%, :%,$(SRC_INCLUDE))
V_LIB:=$(patsubst -I%, :%,$(LIB_INCLUDE))
VPATH=src/ build/ bin/ $(V_SRC) $(V_LIB)
OBJ_DIR:=build/
TESTOBJ := $(subst .c,.o,$(TEST_SOURCES))
TESTBIN := $(subst .c,.exe,$(TEST_SOURCES))
TEST_TXT:= $(subst .c,.txt,$(TEST_SOURCES))
REPORT_DIR:=report/
BIN_DIR:=bin/
################################################################################
## Commands
################################################################################
## Don't forget to add -L directories to runtime environment PATH variable.
## Execute this on msys console.
## export PATH=$PATH:/d/projects/mblazeapp/mblaze_dev/test/lib/bin
CFLAGS+= $(INCLUDES) -Llib/bin/ -lcmocka 
COMPILE=gcc -c -Wall
CLEANUP=rm -rf
DEPEND=gcc -MM -MG -MF

################################################################################
## Functions
################################################################################

LINK_DEPS= Test$(1).o $(1).o vector.o unity.o arraylist.o

################################################################################
## Rules
################################################################################
all : build test


# Dependency file detination
df = $(OBJ_DIR)$(*F)

# List of auto dependencies
AUTODEPS:= $(patsubst %.c,$(OBJ_DIR)%.d,$(TEST_SOURCES))

# Include auto dependencies
-include $(AUTODEPS)

%.d : %.c
	$(DEPEND) $(OBJ_DIR)$@ $<
#.... other rules

################################################################################
test : $(TEST_TXT) show
	@echo "TESTS COMPLETED!"



show : $(REPORT_DIR)Report.exe
	@cls
	@echo -e "-------- TEST RESULTS --------\n"
	@-./$(REPORT_DIR)Report.exe $(foreach txt,$(TEST_TXT), $(OBJ_DIR)$(txt))
	
%.txt : %.exe
	@-./$(BIN_DIR)$(patsubst %.txt,%.exe,$@) > $(OBJ_DIR)$@ 2>&1

build : $(TESTBIN)
	@echo -e "Binary build succesful!\n"
	


Test%.exe: $(call LINK_DEPS,%)
	@echo -e "----------------------" 
	@echo "$@ -- Link --> $+"
	@echo -e "----------------------"
	@gcc -o $(BIN_DIR)$@ $(foreach f,$^,$(OBJ_DIR)$(notdir $(f))) $(CFLAGS) 
	
$(REPORT_DIR)Report.exe: $(REPORT_DIR)Report.o
	@gcc -o $@ $< $(CFLAGS)

$(REPORT_DIR)Report.o : $(REPORT_DIR)Report.c
	@echo " Compile : " $< " => " $@
	@-$(COMPILE) $< $(CFLAGS) -o $@
	
%.o: %.c
	@# Build the dependency file
	@#gcc -MM -MP -MT $(df).o -MT $(df).d  $< > $(df).d 
	@-$(DEPEND) $(patsubst %.o,%.d,$(OBJ_DIR)$(@F)) $<
	@# Compile the object file
	@echo " Compile : " $< " => " $@
	@-$(COMPILE) $< $(CFLAGS) -o $(OBJ_DIR)$@


clean :
	@cls
	$(CLEANUP) $(OBJ_DIR)*.o
	$(CLEANUP) $(OBJ_DIR)*.d
	$(CLEANUP) *.d
	$(CLEANUP) $(OBJ_DIR)*.txt
	$(CLEANUP) $(BIN_DIR)*.exe

cleanTXT : 
	@cls
	@$(CLEANUP) $(OBJ_DIR)*.txt

param :
	 @echo "VPATH 		: $(VPATH)\n"
	 @echo "CFLAGS		: $(CFLAGS)\n"
	 @echo "INCLUDES 	: $(INCLUDES)\n"


.PHONY: clean test build link all cleanTXT show param

