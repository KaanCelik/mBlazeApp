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

test : build link run $(PATHR)TestLcdDecorator.txt
	tail -10 $(PATHR)TestLcdDecorator.txt


run : $(PATHBIN)TestLcdDecorator.exe
	-./$< > $(PATHR)TestLcdDecorator.txt 2>&1

build : $(PATHOBJ)TestLcdDecorator.d $(PATHOBJ)TestLcdDecorator.o $(PATHOBJ)LcdDecorator.o
	@echo $(PATHOBJ)TestLcdDecorator.d created.
	@echo $(PATHOBJ)TestLcdDecorator.o created. 
	@echo $(PATHOBJ)LcdDecorator.o created. 

$(PATHOBJ)TestLcdDecorator.d :: $(PATHT)TestLcdDecorator.c 
	$(DEPEND) $@ $<
	@echo \n
	
$(PATHOBJ)TestLcdDecorator.o : $(PATHT)TestLcdDecorator.c  
	gcc -c $(CFLAGS) $(PATHT)TestLcdDecorator.c  -o $@ 
	@echo \n

$(PATHOBJ)LcdDecorator.o : $(PATHSC)LcdDecorator.c
	gcc -c $(CFLAGS) $<  -o $@ 


link : $(PATHOBJ)TestLcdDecorator.o $(PATHOBJ)LcdDecorator.o $(PATHU)unity.o  
	gcc   -o $(PATHBIN)TestLcdDecorator.exe  $^
	

clean :
	$(CLEANUP) $(PATHOBJ)*.o
	$(CLEANUP) $(PATHOBJ)*.d
	$(CLEANUP) $(PATHBIN)*.exe
	

	
