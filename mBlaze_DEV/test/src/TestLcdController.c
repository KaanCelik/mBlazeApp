/*
 * TestLcdController.c
 *
 *  Created on: 17 08 2016
 *      Author: KaaN
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "../lib/include/cmocka.h"
#include "unity.h"
#include <xuartlite.h>
#include "../src/DeviceControllers/LcdController.h"
#include "../src/Utilities/Vector.h"


LcdController* lcdCtrUnderTest;
XUartLite* mockUartPtr;
char * lcdStreamBuffer;
//const char escSeq[3] = {0x1B,'[', '\0'};
/***** Mock Functions *********************************/
extern void lcd_clearDisplay();

u16 sendString(u8* data, XUartLite* uartPtr){
	//printf("Uart sending : %s\r\n",(char*)data);
	check_expected_ptr(data);
	check_expected_ptr(uartPtr);
	return ((u16) (size_t)mock());
}

/******************************************************/

static int group_setUp(){
	mockUartPtr = (XUartLite*) malloc(sizeof(XUartLite));
	mockUartPtr->RegBaseAddress = 123;
	u32 mockDeviceId= 789;
	lcd_construct(mockUartPtr,mockDeviceId);

	lcdCtrUnderTest = lcd_getController();

	//strcat throws EXCEPTION_ACCESS_VIOLATION without this malloc.
	lcdStreamBuffer = malloc(sizeof(char)*16); 

	return 0;
}



static int group_tearDown(){
	free(mockUartPtr);	
	return 0;
}




static void test_constructLcdCtr(){


	LcdController* lcdCtrUnderTest = lcd_getController();

	assert_int_equal( mockUartPtr->RegBaseAddress,(&lcdCtrUnderTest->uartDeviceCtr)->RegBaseAddress);
	assert_int_equal( 789,lcdCtrUnderTest->lcdUartDeviceId);
	assert_non_null( &(lcdCtrUnderTest->availRows));
	assert_non_null( lcdCtrUnderTest->currentViewRows);
	assert_int_equal(lcdCtrUnderTest->currentViewRows[0],0);
	assert_int_equal(lcdCtrUnderTest->currentViewRows[1],1);
	assert_int_equal((int)lcdCtrUnderTest->availRows.max,32);
}

static void test_lcd_clearDisplay(){
	

	char escSeq[3] = {0x1B,'[', '\0'};
	strcpy(lcdStreamBuffer,(char*)escSeq);
	strcat(lcdStreamBuffer,"j");

	expect_string(sendString,data,lcdStreamBuffer);
	expect_any(sendString,uartPtr);
	will_return(sendString,0);

	lcd_clearDisplay();
	 
}
void test_lcd_displayNext(){
	assert_int_equal(lcdCtrUnderTest->currentViewRows[0],0);
	assert_int_equal(lcdCtrUnderTest->currentViewRows[1],1);
	lcd_displayNext();
	assert_int_equal(lcdCtrUnderTest->currentViewRows[0],1);
	assert_int_equal(lcdCtrUnderTest->currentViewRows[1],2);

}
void test_lcd_displayPrevious(){

	//TEST_FAIL();
}

void test_lcd_setBuffer(){
	//TEST_FAIL();
}

void test_displayRows(){
	//TEST_FAIL();
}

int main(void){
	/*
	UNITY_BEGIN();

	RUN_TEST(test_constructLcdCtr);
	RUN_TEST(test_lcd_clearDisplay);
	RUN_TEST(test_lcd_displayNext);
	RUN_TEST(test_lcd_displayPrevious);
	RUN_TEST(test_lcd_setBuffer);
	RUN_TEST(test_displayRows);

	return UNITY_END();
	*/
    const struct CMUnitTest LcdControllerTests[] = {
        cmocka_unit_test(test_constructLcdCtr),
        cmocka_unit_test(test_lcd_clearDisplay),
        cmocka_unit_test(test_lcd_displayNext)
    };


	return cmocka_run_group_tests(LcdControllerTests, group_setUp, group_tearDown);

	
}


