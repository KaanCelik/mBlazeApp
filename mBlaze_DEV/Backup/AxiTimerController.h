/*
 * AxiTimerController.h
 *
 *  Created on: 06 May 2016
 *      Author: KaaN
 */

#ifndef AXITIMERCONTROLLER_H_
#define AXITIMERCONTROLLER_H_


#endif /* AXITIMERCONTROLLER_H_ */

int initAxiTimer();
void Timer_InterruptHandler(void *CallBackRef, u8 tmrCtrId);
void killTimer();
void printTimerSettings();
