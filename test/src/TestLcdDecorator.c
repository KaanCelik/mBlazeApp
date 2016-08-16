/*
 * LcdDecoratorTest.c
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */
#include "../../src/DeviceControllers/LcdDecorator.h"
#include "../../lib/unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
LcdConfig config;
void setUp(){

	config.maxRows = 2;
	config.maxCols = 16;
	config.displayMode= HEX;

}


void tearDown(){

}

void test_decodeData_ShouldReturnValidString(){
	//config.maxRows = 2;
	//config.maxCols = 16;
	//config.displayMode= DECIMAL;
	
	u8 testData = 15;

	char * result = (char*) malloc(10*sizeof(char));
	
	lcd_decode(&config,testData,result);
	
	
	TEST_ASSERT_EQUAL_STRING("0xF",result);
	free(result);

}

int main(void){
UNITY_BEGIN();
//test_decodeData_ShouldReturnValidString();
RUN_TEST(test_decodeData_ShouldReturnValidString);

return UNITY_END();
return 0;
}

