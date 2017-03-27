/******************************************************************************

 @file  main.c

 @brief main entry of the BLE stack sample application.

 Group: WCS, BTS
 Target Device: CC2650, CC2640, CC1350

 ******************************************************************************

 Copyright (c) 2013-2016, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble_sdk_2_02_00_08
 Release Date: 2016-05-06 22:17:28
 *****************************************************************************/

/*******************************************************************************
 * INCLUDES
 */

#include <xdc/runtime/Error.h>

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

#include "icall.h"
#include "hal_assert.h"
#include "bcomdef.h"
#include "peripheral.h"
#include "project_zero.h"

#include "tipassword_service.h"

#include <ti/drivers/UART.h>
#include <uart_logs.h>

/* Header files required to enable instruction fetch cache */
#include <inc/hw_memmap.h>
#include <driverlib/vims.h>

#ifndef USE_DEFAULT_USER_CFG

#include "ble_user_config.h"

// BLE user defined configuration
bleUserCfg_t user0Cfg = BLE_USER_CFG;

#endif // USE_DEFAULT_USER_CFG

#include <ti/mw/display/Display.h>

/*******************************************************************************
 * MACROS
 */

/*******************************************************************************
 * CONSTANTS
 */
#define TASKSTACKSIZE   512

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */
Swi_Struct swi0Struct;
Swi_Handle swi0Handle;
Semaphore_Struct semStruct;
Semaphore_Handle semHandle;
Task_Struct task1Struct;
Char task1Stack[TASKSTACKSIZE];

PIN_Config button1PinTable[] = {
    Board_BUTTON0  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_BOTHEDGES,
    PIN_TERMINATE
};

PIN_Config button2PinTable[] = {
    Board_BUTTON1  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_BOTHEDGES,
    PIN_TERMINATE
};

Char passwords[10][20] = {
		"p01",
		"p02",
		"p03",
		"p04",
		"p05",
		"p06",
		"p07",
		"p08",
		"p09",
		"p10"
};

/*******************************************************************************
 * GLOBAL VARIABLES
 */
static PIN_Handle button1PinHandle;
static PIN_Handle button2PinHandle;
static PIN_State button1PinState;
static PIN_State button2PinState;

/*******************************************************************************
 * EXTERNS
 */


extern void AssertHandler(uint8 assertCause, uint8 assertSubcause);

extern Display_Handle dispHandle;


void button1CallbackFxn(PIN_Handle handle, PIN_Id pinId) {
	Swi_post(swi0Handle);
}


void button2CallbackFxn(PIN_Handle handle, PIN_Id pinId) {
	Swi_post(swi0Handle);
}

Void swi0Fxn(UArg arg0, UArg arg1)
{
	Semaphore_post(semHandle);
}

Void task1Fxn(UArg arg0, UArg arg1)
{
	int requestedPasswordId = 0;
	uint16_t len = 1;

	while(1)
	{
		Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

		TipasswordService_SetParameter(TS_USERNAME_ID, 8, "UserName");

		if(PIN_getInputValue(Board_BUTTON0) == 0)
		{
			TipasswordService_GetParameter(TS_PASSWORDID_ID, &len, &requestedPasswordId);
			TipasswordService_SetParameter(TS_PASSWORD_ID, 3, passwords[requestedPasswordId]);
		}
//		else
//		{
//			TipasswordService_SetParameter(TS_PASSWORD_ID, 1, " ");
//		}

        System_printf("Printing\n");
        System_flush();
	}
}


/*******************************************************************************
 * @fn          Main
 *
 * @brief       Application Main
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
int main()
{
//  Swi_Params swiParams;
//  Task_Params taskParams;
//  Semaphore_Params semParams;

  /* Register Application callback to trap asserts raised in the Stack */
  RegisterAssertCback(AssertHandler);

  PIN_init(BoardGpioInitTable);

//  Task_Params_init(&taskParams);
//  taskParams.stackSize = TASKSTACKSIZE;
//  taskParams.stack = &task1Stack;
//  taskParams.priority = 1;
//  Task_construct(&task1Struct, (Task_FuncPtr)task1Fxn, &taskParams, NULL);

//  Semaphore_Params_init(&semParams);
//  Semaphore_construct(&semStruct, 0, &semParams);

  /* Obtain instance handle */
//  semHandle = Semaphore_handle(&semStruct);

//  Swi_Params_init(&swiParams);
//  swiParams.arg0 = 1;
//  swiParams.arg1 = 0;
//  swiParams.priority = 0;
//  swiParams.trigger = 0;

//  Swi_construct(&swi0Struct, (Swi_FuncPtr)swi0Fxn, &swiParams, NULL);
//  swi0Handle = Swi_handle(&swi0Struct);

//  button2PinHandle = PIN_open(&button2PinState, button2PinTable);
//  if(!button2PinHandle) {
//      System_abort("Error initializing button pins\n");
//  }

//  if (PIN_registerIntCb(button2PinHandle, &button2CallbackFxn) != 0) {
//      System_abort("Error registering button callback function");
//  }

//  button1PinHandle = PIN_open(&button1PinState, button1PinTable);
//  if(!button1PinHandle) {
//      System_abort("Error initializing button pins\n");
//  }

//  if (PIN_registerIntCb(button1PinHandle, &button1CallbackFxn) != 0) {
//      System_abort("Error registering button callback function");
//  }


#ifndef POWER_SAVING
  /* Set constraints for Standby, powerdown and idle mode */
  Power_setConstraint(PowerCC26XX_SB_DISALLOW);
  Power_setConstraint(PowerCC26XX_IDLE_PD_DISALLOW);
#endif // POWER_SAVING

  /* Initialize the RTOS Log formatting and output to UART in Idle thread.
   * Note: Define xdc_runtime_Log_DISABLE_ALL to remove all impact of Log.
   * Note: NULL as Params gives 115200,8,N,1 and Blocking mode */
  UART_init();
  UartLog_init(UART_open(Board_UART, NULL));

  /* Initialize ICall module */
  ICall_init();

  /* Start tasks of external images - Priority 5 */
  ICall_createRemoteTasks();

  /* Kick off profile - Priority 3 */
  GAPRole_createTask();

  ProjectZero_createTask();

  /* enable interrupts and start SYS/BIOS */
  BIOS_start();

  return 0;
}


/*******************************************************************************
 * @fn          AssertHandler
 *
 * @brief       This is the Application's callback handler for asserts raised
 *              in the stack.
 *
 * input parameters
 *
 * @param       assertCause    - Assert cause as defined in hal_assert.h.
 * @param       assertSubcause - Optional assert subcause (see hal_assert.h).
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void AssertHandler(uint8 assertCause, uint8 assertSubcause)
{
  // Open the display if the app has not already done so
  if ( !dispHandle )
  {
    dispHandle = Display_open(Display_Type_LCD, NULL);
  }

  Display_print0(dispHandle, 0, 0, ">>>STACK ASSERT");

  // check the assert cause
  switch (assertCause)
  {
    case HAL_ASSERT_CAUSE_OUT_OF_MEMORY:
      Display_print0(dispHandle, 0, 0, "***ERROR***");
      Display_print0(dispHandle, 2, 0, ">> OUT OF MEMORY!");
      break;

    case HAL_ASSERT_CAUSE_INTERNAL_ERROR:
      // check the subcause
      if (assertSubcause == HAL_ASSERT_SUBCAUSE_FW_INERNAL_ERROR)
      {
        Display_print0(dispHandle, 0, 0, "***ERROR***");
        Display_print0(dispHandle, 2, 0, ">> INTERNAL FW ERROR!");
      }
      else
      {
        Display_print0(dispHandle, 0, 0, "***ERROR***");
        Display_print0(dispHandle, 2, 0, ">> INTERNAL ERROR!");
      }
      break;

    case HAL_ASSERT_CAUSE_ICALL_ABORT:
      Display_print0(dispHandle, 0, 0, "***ERROR***");
      Display_print0(dispHandle, 2, 0, ">> ICALL ABORT!");
      HAL_ASSERT_SPINLOCK;
      break;

    default:
      Display_print0(dispHandle, 0, 0, "***ERROR***");
      Display_print0(dispHandle, 2, 0, ">> DEFAULT SPINLOCK!");
      HAL_ASSERT_SPINLOCK;
  }

  return;
}


/*******************************************************************************
 * @fn          smallErrorHook
 *
 * @brief       Error handler to be hooked into TI-RTOS.
 *
 * input parameters
 *
 * @param       eb - Pointer to Error Block.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void smallErrorHook(Error_Block *eb)
{
  for (;;);
}


/*******************************************************************************
 */
