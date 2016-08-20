#################################### MAKEFILE ##################################
################################################################################
## Configurations
################################################################################
C_SOURCES := $(shell ls *.c)
LIB_INCLUDE:= $(shell ls -d ../lib/*/)
SRC_INCLUDE:= $(shell ls -d ../src/*/ ../src/)
BSP_INCLUDE:=../../mBlaze_BSP/microblaze_0/include/
SRC_HEADERS:= $(shell ls ../src/*/*.h ../src/*.h)
INCLUDES:=  $(subst ../src, -I../src,$(SRC_INCLUDE)) \
			$(subst ../lib, -I../lib,$(LIB_INCLUDE)) -I$(BSP_INCLUDE)
V_SRC:=$(patsubst -I%, :%,$(SRC_INCLUDE))
V_LIB:=$(patsubst -I%, :%,$(LIB_INCLUDE))
VPATH=build/ $(V_SRC) $(V_LIB)
OBJ_DIR:=build/
TESTOBJ := $(subst .c,.o,$(C_SOURCES))
TESTBIN := $(subst .c,.exe,$(C_SOURCES))
TEST_TXT:= $(subst .c,.txt,$(C_SOURCES))
################################################################################
## Commands
################################################################################

CFLAGS+= $(INCLUDES)
COMPILE=gcc -c -Wall
CLEANUP=rm -rf
DEPEND=gcc -MM -MG -MF

################################################################################
## Functions
################################################################################

LINK_DEPS= Test$(1).o $(1).o vector.o unity.o

################################################################################
## Rules
################################################################################
all : build


# Dependency file detination
df = $(OBJ_DIR)$(*F)

# List of auto dependencies
AUTODEPS:= $(patsubst %.c,$(OBJ_DIR)%.d,$(C_SOURCES))

# Include auto dependencies
-include $(AUTODEPS)

%.d : %.c
	$(DEPEND) $(OBJ_DIR)$@ $<
#.... other rules

################################################################################

test : cleanTXT $(TEST_TXT)
	@echo "TESTS COMPLETED!"	

%.txt : %.exe
	@-./$(patsubst %.txt,%.exe,$@) > $(OBJ_DIR)$@ 2>&1
	@echo -e "-----------------------\nSUMMARY\n------------------------"
	@echo -e `grep -s Tests $(OBJ_DIR)$@`
	@echo -e "-----------------------\nIGNORES:\n-----------------------"
	@echo -e `grep -s IGNORE $(OBJ_DIR)$@`
	@echo -e "-----------------------\nFAILURES:\n-----------------------"
	@echo -e `grep -s FAIL $(OBJ_DIR)$@`
	@echo -e "-----------------------"
	@echo -e "DONE"
	@echo -e "-----------------------"

build : $(TESTBIN)
	@echo "Binary build succesful!"

Test%.exe: $(call LINK_DEPS,%)
	@echo -e "----------------------" 
	@echo "$@ -- Link --> $+"
	@echo -e "----------------------"
	@gcc -o $@ $(foreach f,$^,$(OBJ_DIR)$(notdir $(f))) $(CFLAGS) 
	
	
%.o: %.c
	@# Build the dependency file
	@#gcc -MM -MP -MT $(df).o -MT $(df).d  $< > $(df).d 
	@-$(DEPEND) $(patsubst %.o,%.d,$(OBJ_DIR)$(@F)) $<
	@# Compile the object file
	@echo " GCC : " $< " => " $@
	@-$(COMPILE) $< $(CFLAGS) -o $(OBJ_DIR)$@


clean :
	@cls
	$(CLEANUP) $(OBJ_DIR)*.o
	$(CLEANUP) $(OBJ_DIR)*.d
	$(CLEANUP) *.exe
	$(CLEANUP) *.d
	$(CLEANUP) $(OBJ_DIR)*.txt

cleanTXT : 
	@cls
	@$(CLEANUP) $(OBJ_DIR)*.txt
.PHONY: clean test build link all cleanTXT

