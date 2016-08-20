/*
 * TestLcdController.c
 *
 *  Created on: 17 08 2016
 *      Author: KaaN
 */
#include <stdio.h>
#include <stdlib.h>

#include "../lib/unity/unity.h"
#include <xuartlite.h>
#include "../src/DeviceControllers/LcdController.h"
#include "../src/Utilities/Vector.h"



void setUp(){


}



void tearDown(){

}

void test_constructLcdCtr(){
	XUartLite* mockUartPtr = (XUartLite*) malloc(sizeof(XUartLite));
	mockUartPtr->RegBaseAddress = 123;
	u32 mockDeviceId= 789;
	lcd_construct(mockUartPtr,mockDeviceId);
	LcdController* lcdCtrUnderTest = lcd_getController();

	TEST_ASSERT_EQUAL_UINT32( mockUartPtr->RegBaseAddress,(&lcdCtrUnderTest->uartDeviceCtr)->RegBaseAddress);
	TEST_ASSERT_EQUAL_UINT32( mockDeviceId,lcdCtrUnderTest->lcdUartDeviceId);
	TEST_ASSERT_NULL(lcdCtrUnderTest->stringDataTable);
	free(mockUartPtr);
}

void test_lcd_clearDisplay(){

	TEST_FAIL();
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


