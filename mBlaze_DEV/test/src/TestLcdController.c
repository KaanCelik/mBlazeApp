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

//const char escSeq[3] = {0x1B,'[', '\0'};

extern void lcd_clearDisplay();
extern u32 lcd_displayRow(u16 rowIndex);

/***** Mock Functions *********************************/
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

	//populating availRows...
	arraylist_push(&(lcdCtrUnderTest->availRows), "This is a test #1");
	arraylist_push(&(lcdCtrUnderTest->availRows), "This is a test #2");
	arraylist_push(&(lcdCtrUnderTest->availRows), "This is a test #3"); 
	arraylist_push(&(lcdCtrUnderTest->availRows), "This is a test #4"); 
	
	
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
	int i = 0;
	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i);
	}
	assert_memory_equal(&lcdCtrUnderTest->uartDeviceCtr , mockUartPtr, sizeof(XUartLite));
	assert_int_equal(lcdCtrUnderTest->uartDeviceCtr.RegBaseAddress,123);
	assert_int_equal((int)lcdCtrUnderTest->availRows.max,32);
}

static void test_lcd_clearDisplay(){
	
	char * lcdStreamBuffer;
	lcdStreamBuffer = malloc(sizeof(char)*16); 
	char escSeq[3] = {0x1B,'[', '\0'};
	strcpy(lcdStreamBuffer,(char*)escSeq);
	strcat(lcdStreamBuffer,"j");

	expect_string(sendString,data,lcdStreamBuffer);
	expect_any(sendString,uartPtr);
	will_return(sendString,0);

	lcd_clearDisplay();
	 
}

void test_lcd_displayRow(){

	expect_string(sendString,data,"This is a test #1");
	expect_any(sendString,uartPtr);
	will_return(sendString,0);

	//Display the row with the index 0.
	lcd_displayRow(0);
	
}

void test_lcd_displayNext(){
	int i = 0;
	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i);
	}

	expect_string(sendString,data,"This is a test #2");
	expect_string(sendString,data,"This is a test #3");
	expect_any_count(sendString,uartPtr,2);
	will_return_count(sendString,0,2);
	

	lcd_displayNext();

	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i+1);
	}

}
void test_lcd_displayPrevious(){

	lcd_setViewToDefault();
	int i = 0;
	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i);
		lcdCtrUnderTest->currentViewRows[i]+=2;
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i+2);
	}

	expect_string(sendString,data,"This is a test #2");
	expect_string(sendString,data,"This is a test #3");
	expect_any_count(sendString,uartPtr,2);
	will_return_count(sendString,0,2);
	

	lcd_displayPrevious();

	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i+1);
	}

}

void test_lcd_displayRows(){

	expect_string(sendString,data,"This is a test #1");
	expect_string(sendString,data,"This is a test #2");
	expect_any_count(sendString,uartPtr,2);
	will_return_count(sendString,0,2);
	
	int status = lcd_displayRows();

	assert_int_equal(status,0);

}
void test_lcd_display(){

	expect_string(sendString,data,"This is a test #1");
	expect_string(sendString,data,"This is a test #2");
	expect_any_count(sendString,uartPtr,2);
	will_return_count(sendString,0,2);
	

	lcd_display();
	int i;
	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i);
	}
}

void test_lcd_setViewToDefault(){
	int i = 0;
	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		lcdCtrUnderTest->currentViewRows[i]=i+100;
	}
	lcd_setViewToDefault();

	for (i=0;i<DISPLAY_MATRIX_ROW;i++){
		assert_int_equal(lcdCtrUnderTest->currentViewRows[i],i);
	}
}

void test_lcd_changeDisplayMode(){
	DISPLAY_MODES dispModeHex = HEX;
	DISPLAY_MODES dispModeDec = DECIMAL;
	DISPLAY_MODES dispModeChar = CHAR;
	DISPLAY_MODES dispModeIllegal = 77;

	lcd_changeDisplayMode(dispModeIllegal);
	assert_int_equal((int)dispModeHex,(int) lcdCtrUnderTest->displayMode);

	lcd_changeDisplayMode(dispModeDec);
	assert_int_equal(dispModeDec, lcdCtrUnderTest->displayMode);
	lcd_changeDisplayMode(dispModeChar);
	assert_int_equal(dispModeChar, lcdCtrUnderTest->displayMode);
	lcd_changeDisplayMode(dispModeHex);
	assert_int_equal(dispModeHex, lcdCtrUnderTest->displayMode);

}
void test_lcd_byteToString(){

	u8 testByte = 15;

	char* result = malloc(sizeof(char)*4);
	lcd_byteToString(testByte,result);
	assert_string_equal("0xF",result);

	lcd_changeDisplayMode(DECIMAL);
	lcd_byteToString(testByte,result);
	assert_string_equal("15",result);

	testByte = 65;

	lcd_changeDisplayMode(HEX);
	lcd_byteToString(testByte,result);
	assert_string_equal("0x41",result);

	lcd_changeDisplayMode(DECIMAL);
	lcd_byteToString(testByte,result);
	assert_string_equal("65",result);

	lcd_changeDisplayMode(CHAR);
	lcd_byteToString(testByte,result);
	assert_string_equal("A",result);

	free(result);
}

void test_lcd_generateRows(){
	
	arraylist_free(&lcdCtrUnderTest->availRows);
	
	arraylist_new(&lcdCtrUnderTest->availRows,10);

	Vector testBytes;
	vector_init(&testBytes);

	int i = 0;
	for (i=0;i<200;i++){
		vector_push(&testBytes,65+i);
	}

	lcd_setByteVector(&testBytes);
	assert_int_equal(lcdCtrUnderTest->availRows.len, 0);
	lcd_changeDisplayMode(CHAR);
	lcd_generateRows();

	assert_string_equal(lcdCtrUnderTest->availRows.items[0], "0   : A");
	
	/*printf("--- Available Rows ---\n");
	for (i =0; i<lcdCtrUnderTest->availRows.len;i++){
		printf("%s\n",(char*) lcdCtrUnderTest->availRows.items[i]);
	}*/

}


int main(void){

	

    const struct CMUnitTest LcdControllerTests[] = {
        cmocka_unit_test(test_constructLcdCtr),
        cmocka_unit_test(test_lcd_clearDisplay),
        cmocka_unit_test(test_lcd_displayRow),
        cmocka_unit_test(test_lcd_displayRows),
        cmocka_unit_test(test_lcd_displayNext),
        cmocka_unit_test(test_lcd_displayPrevious),
        cmocka_unit_test(test_lcd_display),
        cmocka_unit_test(test_lcd_setViewToDefault),
        cmocka_unit_test(test_lcd_changeDisplayMode),
        cmocka_unit_test(test_lcd_byteToString),
        cmocka_unit_test(test_lcd_generateRows)
    };

	return cmocka_run_group_tests(LcdControllerTests, group_setUp, group_tearDown);

	
}


