/*
 * BramController.h
 *
 *  Created on: 26 Tem 2016
 *      Author: KaaN
 */

#ifndef BRAMCONTROLLER_H_
#define BRAMCONTROLLER_H_
#include "xbasic_types.h"
#include "../Utilities/Vector.h"
u8 brc_init();
u8 brc_saveStack(Vector* stack);
Vector* brc_getStack();
void brc_selfTestBramController();
#endif /* BRAMCONTROLLER_H_ */
