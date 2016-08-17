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





u32 lcd_init(u32 deviceId);

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
 * Sets the display buffer. It represents the raw data to be displayed.
 *
 * @param 	byteVector is the raw input to be displayed. It can have u8 numbers.
 */
void lcd_setBuffer(Vector* byteVector);


/**
 * Displays the selected rows by sending the proper commands via
 * uart to the device.By default it moves the cursor to the beginning
 * and then puts the rows to display.Caller must call calculateDisplayMatrix()
 * method prior to this method.
 *
 *
 * @param 	rowIndexes is a array of integers. Specifies which exact rows
 * 			must be displayed.
 * @param 	len is the length of rowIndexes. Caller must specify it.
 * 			This parameter cannot exceed DISPLAY_MATRIX_ROW.
 *
 * @return	- XST_SUCCESS
 * 			- XST_FAILURE
 */
u32 displayRows(u16* rowIndexes, int len)
#endif /* LCDCONTROLLER_H_ */
