/*
 * Util.h
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */

#ifndef UTIL_H_
#define UTIL_H_


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
