/*
 * TestLcdController.c
 *
 *  Created on: 17 08 2016
 *      Author: KaaN
 */
#include <stdio.h>
#include <stdlib.h>

#include "../lib/unity/unity.h"

#include "../src/DeviceControllers/LcdController.h"
#include "../src/Utilities/Vector.h"



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
	RUN_TEST(test_lcd_init);
	RUN_TEST(test_lcd_clearDisplay);
	RUN_TEST(test_lcd_displayNext);
	RUN_TEST(test_lcd_displayPrevious);
	RUN_TEST(test_lcd_setBuffer);
	RUN_TEST(test_displayRows);

	return UNITY_END();

}


