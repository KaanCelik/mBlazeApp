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
#Include Directories
PATHT=src/
PATHSO=../Debug/src/DeviceControllers/
PATHOBJ=build/obj/
PATHBIN=build/bin/
PATHR=build/report/
PATHB=build/
#Includes
LIBRARY=../lib/
PATHU=../lib/unity/
PATHSC=../src/DeviceControllers/
PATH_BSP = ../../mBlaze_v1.3_bsp/microblaze_0/include/
#Commands
DEPEND=gcc -MM -MG -MF
LINK=gcc

COMPILE=gcc -c
CFLAGS= -I$(PATHU) -I$(PATHSC) -I$(PATH_BSP) -I$(LIBRARY)


BUILD_PATHS= $(PATHB) $(PATHOBJ) $(PATHBIN) $(PATHR)
#Recipes

test : $(BUILD_PATHS) $(PATHBIN)TestLcdDecorator.exe
	@-./$(PATHBIN)TestLcdDecorator.exe > $(PATHR)TestLcdDecorator.txt 2>&1
	@echo -e "-----------------------\nSUMMARY\n------------------------"
	@echo -e `grep -s Tests $(PATHR)TestLcdDecorator.txt`
	@echo -e "-----------------------\nIGNORES:\n-----------------------"
	@echo -e `grep -s IGNORE $(PATHR)TestLcdDecorator.txt`
	@echo -e "-----------------------\nFAILURES:\n-----------------------"
	@echo -e `grep -s FAIL $(PATHR)TestLcdDecorator.txt`
	@echo -e "-----------------------"
	@echo -e "DONE"
	@echo -e "-----------------------"


$(PATHBIN)TestLcdDecorator.exe : $(PATHOBJ)TestLcdDecorator.o $(PATHOBJ)LcdDecorator.o $(PATHU)build/unity.o
	@echo -e "-----------------------"
	@echo -e "Target : $@"  
	@gcc   -o $(PATHBIN)TestLcdDecorator.exe  $^
	@echo -e "-----------------------"

$(PATHOBJ)TestLcdDecorator.o : $(PATHOBJ)TestLcdDecorator.d  $(PATHT)TestLcdDecorator.c 
	@echo -e "-----------------------"
	@echo -e "Target : $@"  
	@gcc -c $(CFLAGS) $(PATHT)TestLcdDecorator.c  -o $@ 
	@echo -e "-----------------------"

$(PATHOBJ)TestLcdDecorator.d : $(PATHT)TestLcdDecorator.c 
	@echo -e "-----------------------"
	@echo -e "Target : $@"
	@$(DEPEND) $@ $<
	@echo -e "-----------------------"
	

$(PATHOBJ)LcdDecorator.o : $(PATHSC)LcdDecorator.c
	@echo -e "-----------------------"
	@echo -e "Target : $@"
	@gcc -c $(CFLAGS) $<  -o $@ 
	@echo -e "-----------------------"

$(LIBRARY)unity/build/%.o : $(LIBRARY)unity/%.c
	@echo -e "-----------------------"
	@echo -e "Target : $@"
	@$(COMPILE) $< -o $@  
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

	
