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
#include "../lib/cmocka/cmocka.h"
#include "../lib/unity/unity.h"
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
	check_expected_ptr(data);
	check_expected_ptr(uartPtr);
	return ((u16) (size_t)mock());
}

/******************************************************/


void setUp(){
	mockUartPtr = (XUartLite*) malloc(sizeof(XUartLite));
	mockUartPtr->RegBaseAddress = 123;
	u32 mockDeviceId= 789;
	lcd_construct(mockUartPtr,mockDeviceId);

	lcdCtrUnderTest = lcd_getController();

}



void tearDown(){

}



void test_constructLcdCtr(){


	LcdController* lcdCtrUnderTest = lcd_getController();

	TEST_ASSERT_EQUAL_UINT32( mockUartPtr->RegBaseAddress,(&lcdCtrUnderTest->uartDeviceCtr)->RegBaseAddress);
	TEST_ASSERT_EQUAL_UINT32( 789,lcdCtrUnderTest->lcdUartDeviceId);
	TEST_ASSERT_NULL(lcdCtrUnderTest->stringDataTable);
	free(mockUartPtr);
}

void test_lcd_clearDisplay(){
	char escSeq[3] = {0x1B,'[', '\0'};
	strcpy(lcdStreamBuffer,(char*)escSeq);
	strcat(lcdStreamBuffer,"j");

	expect_string(sendString,data,lcdStreamBuffer);
	expect_any(sendString,uartPtr);
	will_return(sendString,0);

	lcd_clearDisplay();
	//TEST_PASS();
	/*
	 * Cmocka must be linked with the library.
	 * Compiler says undefined reference.
	 */

}
void test_lcd_displayNext(){

	TEST_FAIL();
}
void test_lcd_displayPrevious(){

	TEST_FAIL();
}

void test_lcd_setBuffer(){
	TEST_FAIL();
}

void test_displayRows(){
	TEST_FAIL();
}

int main(void){

	UNITY_BEGIN();
	RUN_TEST(test_constructLcdCtr);
	RUN_TEST(test_lcd_clearDisplay);
	RUN_TEST(test_lcd_displayNext);
	RUN_TEST(test_lcd_displayPrevious);
	RUN_TEST(test_lcd_setBuffer);
	RUN_TEST(test_displayRows);

	return UNITY_END();

}


