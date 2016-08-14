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
/**
 * LCD display constraints. Must be defined in accordance with the
 * device being used.
 * DISPLAY_MATRIX_ROW is the amount of rows of the display.
 * DISPLAY_MATRIX_COL is the amount of columns of the display.
 */
#define DISPLAY_MATRIX_ROW  2
#define DISPLAY_MATRIX_COL  16




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
 * Changes the representation of the data, recalculates display vector.
 *
 * @param 	dispMode is the mode of representation. It can be one of the
 * values in DISPLAY_MODES enum.
 *
 * @return	- XST_SUCCESS
 * 			- XST_INVALID_PARAM if input display mode is not valid.
 * 			- XST_FAILURE if there is a error.
 */
u32 lcd_changeDisplayMode();

/**
 * Sets the display buffer. It represents the raw data to be displayed.
 *
 * @param 	bfVector is the raw input to be displayed. It can have u8 numbers.
 */
void lcd_setBuffer(Vector* bfVector);

#endif /* LCDCONTROLLER_H_ */
