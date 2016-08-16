/*
 * LcdDecoratorTest.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "../../src/DeviceControllers/LcdDecorator.h"
#include "../../../unity/src/unity.h"
#include <stdio.h>
LcdConfig config;
void setUp(){

	config.maxRows = 2;
	config.maxCols = 16;
	config.displayMode= DECIMAL;

}

void tearDown(){

}

void test_decodeData_ShouldReturnValidString(){
	u8 testData = 15;
	char*  testStr;

	lcd_decode(&config,&testData,testStr);
	printf("%s\n",testStr);

	//TEST_ASSERT_EQUAL_STRING("0xF",testStr);

}

int main(void){
//UNITY_BEGIN();
	test_decodeData_ShouldReturnValidString();
//RUN_TEST(test_decodeData_ShouldReturnValidString);

//return UNITY_END();
return 0;
}

