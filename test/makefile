ifeq ($(OSTYPE),cygwin)
	CLEANUP=rm -f
	MKDIR=mkdir -p
	TARGET_EXTENSION=out
else ifeq ($(OS),Windows_NT)
	CLEANUP=rm -f
	MKDIR=mkdir
	TARGET_EXTENSION=exe
else
	CLEANUP=rm -f
	MKDIR=mkdir -p
	TARGET_EXTENSION=out
endif
#Include Directories
PATHT=src/
PATHSO=../Debug/src/DeviceControllers/
PATHOBJ=build/obj/
PATHBIN=build/bin/
PATHR=build/report/
#Includes
PATHU=../../unity/src/
PATHSC=../src/DeviceControllers/
PATH_BSP = ../../mBlaze_v1.3_bsp/microblaze_0/include/
#Commands
DEPEND=gcc -MM -MG -MF
LINK=gcc
CFLAGS= -I$(PATHU) -I$(PATHSC) -I$(PATH_BSP)
#Recipes

test : $(PATHR)TestLcdDecorator.txt
	@echo -e "-----------------------\nIGNORES:\n-----------------------"
	@echo -e `grep -s IGNORE $(PATHR)TestLcdDecorator.txt`
	@echo -e "-----------------------\nFAILURES:\n-----------------------"
	@echo -e `grep -s FAIL $(PATHR)TestLcdDecorator.txt`
	@echo -e "-----------------------"
	@echo -e "\nDONE"
	@echo -e "-----------------------"


$(PATHR)TestLcdDecorator.txt : $(PATHBIN)TestLcdDecorator.exe
	-./$< > $(PATHR)TestLcdDecorator.txt 2>&1

$(PATHBIN)TestLcdDecorator.exe : $(PATHOBJ)TestLcdDecorator.o $(PATHOBJ)LcdDecorator.o $(PATHU)unity.o
	@echo -e "-----------------------"
	@echo -e "Target : $@"  
	gcc   -o $(PATHBIN)TestLcdDecorator.exe  $^
	@echo -e "-----------------------"

$(PATHOBJ)TestLcdDecorator.o : $(PATHOBJ)TestLcdDecorator.d  $(PATHT)TestLcdDecorator.c 
	@echo -e "-----------------------"
	@echo -e "Target : $@"  
	gcc -c $(CFLAGS) $(PATHT)TestLcdDecorator.c  -o $@ 
	@echo -e "-----------------------"

$(PATHOBJ)TestLcdDecorator.d : $(PATHT)TestLcdDecorator.c 
	@echo -e "-----------------------"
	@echo -e "Target : $@"
	$(DEPEND) $@ $<
	@echo -e "-----------------------"
	

$(PATHOBJ)LcdDecorator.o : $(PATHSC)LcdDecorator.c
	@echo -e "-----------------------"
	@echo -e "Target : $@"
	gcc -c $(CFLAGS) $<  -o $@ 
	@echo -e "-----------------------"

clean :
	$(CLEANUP) $(PATHOBJ)*.o
	$(CLEANUP) $(PATHOBJ)*.d
	$(CLEANUP) $(PATHBIN)*.exe
	

	
