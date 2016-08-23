/*
 * Util.h
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <xil_types.h>
#include <stdio.h>

#define checkStatus(status) if (status != XST_SUCCESS){xil_printf("Fail!\r\n");return XST_FAILURE;}
#define assertStatus(status, exp) if (status != XST_SUCCESS){xil_printf("Fail! %s \r\n", exp);return XST_FAILURE;}

#define checkSendSuccess(status)if (status != XST_SUCCESS) {xil_printf("Send Fail!\r\n");return XST_FAILURE;}
#define logVariable(var,exp){xil_printf("%s : %d 0x%X\r\n", exp,var,var);}

void printBuffer(u8* buffer, char* exp);
void printStatus(char* message, int status);

#endif /* UTIL_H_ */

/*****************************************************************************
*
* MACRO:
*
* STATUS_CHECK
*
* DESCRIPTION:
*
* This macro checks the status for functions called. It performs a return
* if the status was not success.  The purpose of this macro is to allow
* centralized status checking.
*
* ARGUMENTS:
*
* Status contains any status from a Xilinx driver.
*
* RETURN VALUE:
*
* None.
*
* NOTES:
*
* Signature: void STATUS_CHECK(XStatus Status)
*
******************************************************************************/
#define STATUS_CHECK(Status)            \
    {                                   \
        if (Status != XST_SUCCESS)      \
        {                               \
            return Status;              \
        }                               \
    }
