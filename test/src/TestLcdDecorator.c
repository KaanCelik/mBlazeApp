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
#include "../../src/Utilities/Vector.h"

LcdConfig* configPtr;

void setUp(){

	configPtr = getLcdConfigPtr();

	configPtr->maxRows = 2;
	configPtr->maxCols = 16;
	configPtr->displayMode= HEX;
}


void tearDown(){

}

void test_getLcdConfigPtr(){
	LcdConfig* cPtr = getLcdConfigPtr();
	TEST_ASSERT_NOT_NULL(cPtr);

}


void test_decodeData_ShouldReturnValidString(){
	u8 testData = 15;
	char * result = (char*) malloc(10*sizeof(char));
	lcd_decode(testData,result);
	TEST_ASSERT_EQUAL_STRING("0xF",result);
	free(result);

}

void test_calculateDisplayMatrix(){
	Vector* v = (Vector*) malloc (sizeof(Vector));
	vector_init(v);
	u8 i;
	for(i=0 ; i < 7 ; i++){
		vector_push(v,i);	
	}

	//calculateDisplayMatrix(v);

	

	//TEST_ASSERT_EQUAL_INT_MESSAGE(14,strlen(getRow(0)),(char*) getRow(0));
	//TEST_ASSERT_EQUAL_INT_MESSAGE(3 , strlen((char*) ((&dispMatrix)[1])),(char*) ((&dispMatrix)[1]));

}

void test_getRow(){
	char** dispMatrix = getDisplayMatrixPtr();
	char* r = "aaaa";
	char* r2 = "bbbb";
	dispMatrix[0] = r;
	dispMatrix[1] = r2;
	char* resultRow1 = getRow(0);
	char* resultRow2 = getRow(1);
	TEST_ASSERT_EQUAL_STRING(r,resultRow1);
	TEST_ASSERT_EQUAL_STRING(r2,resultRow2);
}

int main(void){

	UNITY_BEGIN();

	RUN_TEST(test_getLcdConfigPtr);
	RUN_TEST(test_decodeData_ShouldReturnValidString);
	//RUN_TEST(test_calculateDisplayMatrix);
	RUN_TEST(test_getRow);

	return UNITY_END();
	return 0;
}

