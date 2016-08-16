/*
 * LcdDecorator.h
 *
 *  Created on: 14 Aðu 2016
 *      Author: KaaN
 */

#ifndef LCDDECORATOR_H_
#define LCDDECORATOR_H_

#include <xil_types.h>

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


/**
 * Decodes the given data returns a string representation of it. Decoding
 * is performed according to the specifications defined in LcdConfig.
 *
 * @param	configPtr is a pointer to the configuration struct.
 * @param	inputData is a u8 number.
 *
 * @return 	A string value of the given data.
 * @note	Caller must initialize the LcdConfig before passing the pointer.
 */
void lcd_decode(LcdConfig* configPtr, u8* inputData, char* dest);

#endif /* LCDDECORATOR_H_ */
