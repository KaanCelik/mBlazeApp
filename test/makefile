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
