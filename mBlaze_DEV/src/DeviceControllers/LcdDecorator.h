/*
 * LcdDecorator.h
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */

#ifndef LCDDECORATOR_H_
#define LCDDECORATOR_H_

#include <xil_types.h>
#include "../Utilities/Vector.h"
#include "../Utilities/StringArray.h"
/**
 * LCD display constraints. Must be defined in accordance with the
 * device being used.
 * DISPLAY_MATRIX_ROW is the amount of rows of the display.
 * DISPLAY_MATRIX_COL is the amount of columns of the display.
 */

#define DISPLAY_MATRIX_ROW_MAX  32
enum DISPLAY_MODES
        {
          HEX,
          DECIMAL,
          CHAR
        };

typedef struct LcdConfig {
	u16 maxRows;
	u16 maxCols;
	u16 displayMode;
}LcdConfig;

void construct();
void destruct();
char* getRow(int i);
LcdConfig* getLcdConfigPtr();
StringArray* getProcessedStrings();

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
 * Decodes the given data returns a string representation of it. Decoding
 * is performed according to the specifications defined in LcdConfig.
 *
 * @param	inputData is a u8 number.
 * @param	resultStr is the output of the method.
 *
 * @return 	void
 *
 * @note	Caller must initialize the LcdConfig beforehand.
 * 			Caller also malloc resultStr before passing.
 */			
void lcd_decode(u8 inputData, char* resultStr);



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
void changeDisplayMode(int dispMode);

#endif /* LCDDECORATOR_H_ */
