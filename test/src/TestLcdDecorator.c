/*
 * LcdDecoratorTest.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "../../src/DeviceControllers/LcdDecorator.h"
#include "../../../unity/src/unity.h"
LcdConfig config;
void setUp(){

	config.maxRows = 2;
	config.maxCols = 16;
	config.displayMode= HEX;

}

void tearDown(){

}

void test_decodeData_ShouldReturnValidString(){
	u8 testData = 15;
	char * testStr = lcd_decode(&config,testData );
	TEST_ASSERT_EQUAL_STRING("0x0F",testStr);

}

int main(void){
UNITY_BEGIN();
RUN_TEST(test_decodeData_ShouldReturnValidString);

return UNITY_END();
}

