/*
 * LcdController.h
 *
 *  Created on: 13 Aðu 2016
 *      Author: KaaN
 */

#ifndef LCDCONTROLLER_H_
#define LCDCONTROLLER_H_
#include "UartController.h"
#include "../Utilities/Vector.h"
#include "../Utilities/arraylist.h"
#define DISPLAY_MATRIX_ROW  2
#define DISPLAY_MATRIX_COL  16


typedef enum DISPLAY_MODES
        {
          HEX,
          DECIMAL,
          CHAR
        }DISPLAY_MODES;


typedef struct LcdController {
	XUartLite uartDeviceCtr;
	u32 lcdUartDeviceId;
	arraylist_t availRows;
	char lcdSendBuffer[16];
	u16* currentViewRows;
	DISPLAY_MODES displayMode;
	Vector byteVector;
} LcdController;


/**
 * Initializes a static LcdController struct. Assigns a uart controller
 * to it and also sets data pointer to NULL as a initial value.
 *
 * @param	uartCtr is a pointer to initialized XuartLite struct.
 * @param	deviceId is the device id of the device which uartCtr
 * 			corresponds to.
 *
 * @return	void
 */
void lcd_construct(XUartLite* uartCtr, u32 deviceId);


/**
 * Getter method for LcdController struct.
 *
 * @return	A pointer to LcdController struct
 */
LcdController* lcd_getController();


/**
 * Clears the LCD display area. Sets cursor to the beginning.
 */
void lcd_clearDisplay();

/**
 * Displays the data stored in buffer. If amount of data exceeds
 * raises a flag.
 *
 * @return	- XST_SUCCESS if everything works correctly.
 * 			- XST_FAILURE if there is an error.
 * 			- XST_NO_DATA if buffer is empty.
 */
u32 lcd_display();

/**
 * Display the next available data fragment in the buffer.
 *
 * @return	- XST_SUCCESS if everything works correctly.
 * 			- XST_NO_DATA if no more data available.
 */
u32 lcd_displayNext();

/**
 * Display the last available data fragment in the buffer.
 *
 * @return	- XST_SUCCESS if everything works correctly.
 * 			- XST_NO_DATA if no more data available.
 */
u32 lcd_displayPrevious();



/**
 * Sets the byteVector of LcdController. It represents the unprocessed data to be displayed.
 *
 * @param 	bytes is the raw input to be displayed. It can have u8 numbers.
 */
void lcd_setByteVector(Vector* bytes);


/**
 * Displays the selected row by sending the proper commands via
 * uart to the LCD device.By default it moves the cursor to the beginning
 * and then puts the rows to display.Caller must call calculateDisplayMatrix()
 * method prior to this method.
 *
 *
 * @param 	rowIndex is the position of the selected row within availRows. Specifies which exact row
 * 			must be displayed.
 *
 * @return	- XST_SUCCESS
 * 			- XST_FAILURE
 */
u32 lcd_displayRow(u16 rowIndex);

/**
 * Displays the rows specified at LcdController struct.
 *
 * @return		- XST_SUCCESS
 * 				- XST_FAILURE


 */
u32 lcd_displayRows();

/**
 * Sets the currentViewRows in LcdController struct to default. 
 * Default rows are 0,1, ... , (DISPLAY_MATRIX_ROW-1)
 *
 * @return		void
 */
void lcd_setViewToDefault();



/**
 *	Calculates the displayable char arrays. Max length of each row is defined by DISPLAY_MATRIX_COL.
 *	Each byte from input vector is transformed to a string representation and
 *  inserted into the display matrix.
 *
 *	@param byteVector is the input of the method. Must consist u8 numbers as data. 
 * 	
 *	@return void
 */
void calculateDisplayMatrix(Vector* byteVector);

/**
 * Performs byte to string conversion. Decoding is performed
 * according to the specifications defined in LcdController struct..
 *
 * @param	byte is a u8 number.
 * @param	resultStr is the output of the method.
 *
 * @return 	void
 *
 * @note	Caller must initialize the LcdConfig beforehand.
 * 			Caller also malloc resultStr before passing.
 */			
void lcd_byteToString(u8 byte, char* resultStr);



/**
 * Changes the representation of the data, recalculates display vector.
 *
 * @param 	dispMode is the mode of representation. It can be one of the
 * values in DISPLAY_MODES enum.
 *
 * @return	- XST_SUCCESS
 * 			- XST_INVALID_PARAM if input display mode is not valid.
 * 			- XST_FAILURE if there is a error.
 */
void lcd_changeDisplayMode(int dispMode);


void lcd_generateRows();

#endif /* LCDCONTROLLER_H_ */
