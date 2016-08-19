<<<<<<< HEAD
# this is a comment
CC=gcc

##########################################################################
## Includes +
##########################################################################
LIB_INCLUDE:= $(shell  ls -d ../lib/*/ ../lib/)
SRC_INCLUDE:= $(shell  ls -d ../src/*/ ../src/)
BSP_INCLUDE:= ../../mBlaze_v1.3_bsp/microblaze_0/include/
INCLUDES= $(subst lib,-Ilib,$(LIB_INCLUDE)) $(subst src,-Isrc,$(SRC_INCLUDE)) -I$(BSP_INCLUDE) 
##########################################################################
## Commands +
##########################################################################
DEPEND:=gcc -MM -MG -MF

##########################################################################
## Functions
##########################################################################

##########################################################################
## Variables
##########################################################################
#MAINSRC := $(shell ls src/*.c src/*/*.c)
#MAINOBJ := $(foreach dir,$(MAINSRC),$(subst .c,.o,test/build/obj/$(shell basename $(dir))))
#TESTSRC := $(shell ls test/src/*.c)
#TEMPOBJ := $(subst test/src/, test/build/obj/, $(TESTSRC))
#TESTOBJ := $(subst .c,.o ,$(TEMPOBJ))
#TESTDEP := $(subst .c,.d ,$(TEMPOBJ))
#TEMPBIN := $(subst test/src/, test/build/bin/, $(TESTSRC))
TESTBIN := $(subst .c,.exe ,$(wildcard *.c))
#LIBSRC := $(-shell ls lib/*.c lib/*/*.c)
##########################################################################
#@echo -e $(join $(PATHOBJ),$(call changeSuffix,test/build/bin/TestLcdController.exe,.o))
PATHOBJ:= test/build/obj/
PATH_BIN:= test/build/bin/
PATH_TSRC:=test/src/
BUILDPATH:=build/
VPATH=$(BUILDPATH)


kaan : $(TESTBIN) unity.o
	@echo -e "-----------------------"
	@echo -e "Target : 1 $^"
	@echo -e "-----------------------"

Test%.exe : Test%.o 
	gcc -c $(INCLUDES) $^ -o $@  

unity.o : ../lib/unity/unity.c
	$(CC) $(INCLUDES) -o $@ $^

Test%.o : Test%.c unity.o Test%.d
	adsadas
	$(CC) $(INCLUDES) -o $@ $^

%.d : %.c
	$(DEPEND) $@ $<
	
	

clean :
	$(CLEANUP) *.o
	$(CLEANUP) *.d



.PHONY: kaan
	
.PHONY: clean
.PHONY: test
=======
#################################### MAKEFILE ##################################
################################################################################
## Configurations
################################################################################
C_SOURCES := $(shell ls *.c)
LIB_INCLUDE:= $(shell ls -d ../lib/*/ ../lib/)
SRC_INCLUDE:= $(shell ls -d ../src/*/ ../src/)
SRC_HEADERS:= $(shell ls ../src/*/*.h ../src/*.h)
INCLUDES:=  $(subst ../src, -I../src,$(SRC_INCLUDE)) $(subst ../lib, -I../lib,$(LIB_INCLUDE)) 
V_SRC:=$(patsubst -I%, :%,$(SRC_INCLUDE))
V_LIB:=$(patsubst -I%, :%,$(LIB_INCLUDE))
VPATH=build/ $(V_SRC) $(V_LIB)
OBJ_DIR:=build/
TESTOBJ := $(subst .c,.o,$(C_SOURCES))
TESTBIN := $(subst .c,.exe,$(C_SOURCES))
################################################################################
## Commands
################################################################################
CFLAGS+= $(INCLUDES)
COMPILE=gcc -c -Wall
CLEANUP=rm -rf
DEPEND=gcc -MM -MG -MF
################################################################################
## Test Configurations
################################################################################

TEST_SOURCES= $(wildcard *.c)
GET_DEPENDENCY= $(patsubst Test%.c,%.d,$(1))
GET_BUNDLE= $(1) $(call GET_DEPENDENCY,$(1))


################################################################################

# destination path macro we'll use below
df = $(OBJ_DIR)$(*F)

# create a list of auto dependencies
AUTODEPS:= $(patsubst %.c,$(OBJ_DIR)%.d,$(C_SOURCES))

# include by auto dependencies
-include $(AUTODEPS)



%.d : %.c
	$(DEPEND) $(OBJ_DIR)$@ $<
#.... other rules
build : clean link


link : $(TESTBIN)
	@echo "Target $@"

%.exe: $(patsubst %.c,%.o,$(wildcard *.c)) $(patsubst Test%.c,%.o,$(wildcard *.c)) vector.o unity.o
	@echo "$@ --> $+"
	@echo -e "----------------------\n"
	@#gcc $(INCLUDES) -o $@ $^
	gcc $(INCLUDES) -o $@ $(foreach f,$^,$(OBJ_DIR)$(f)) 


# and last but not least my generic compiler rule
%.o: %.c
	@# Build the dependency file
	@#gcc -MM -MP -MT $(df).o -MT $(df).d  $< > $(df).d 
	@# Compile the object file
	@echo " GCC : " $< " => " $@
	@$(COMPILE) $< $(CFLAGS) -o $(OBJ_DIR)$@


clean :
	@cls
	$(CLEANUP) $(OBJ_DIR)*.o
	$(CLEANUP) $(OBJ_DIR)*.d

.PHONY: clean test build link
>>>>>>> origin/trunk
