/*
 * IntrController.h
 *
 *  Created on: 06 May 2016
 *      Author: KaaN
 *
 *      Usage Remarks:
 *      Starting sequence for the device is as follows
 *      1-init
 *      2-connect
 *      3-start
 *      4-enable
 */

#ifndef INTRCONTROLLER_H_
#define INTRCONTROLLER_H_
#include "xintc.h"
#include "xintc_l.h"
#include "xuartlite.h"
#include "xil_exception.h"
#include "../Utilities/Util.h"

int initInterruptSystem();
int connectInterrupts(XUartLite* uartCtr);
int startIntrController();
void enableIntrController();
void printIntcProperties();

#endif /* INTRCONTROLLER_H_ */
