/*
 * TestLcdController.c
 *
 *  Created on: 17 08 2016
 *      Author: KaaN
 */
#include "../../src/DeviceControllers/LcdController.h"
#include "../../lib/unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../src/Utilities/Vector.h"



void setUp(){


}


void tearDown(){

}

void test_lcd_init(){
	TEST_FAIL();
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
	RUNTEST(test_lcd_init);
	RUNTEST(test_lcd_clearDisplay);
	RUNTEST(test_lcd_displayNext);
	RUNTEST(test_lcd_displayPrevious);
	RUNTEST(test_lcd_setBuffer);
	RUNTEST(test_displayRows);

	return UNITY_END();

}

