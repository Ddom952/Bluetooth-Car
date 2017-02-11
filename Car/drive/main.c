/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "drive.h"
#include "uart.h"
#include "my_string.h"
#include "command_decoder.h"

extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

int main(void) {
  char cMsg[RECEIVER_SIZE];
/* now without transmission */
//  char cTransmitterBuffer[TRANSMITER_SIZE];

  BOARD_InitPins(); 
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();
  DriveInit();
  BLE_COM_UART_Init();

  for(;;) { /* Infinite loop to avoid leaving the main function */
	  	if ( eReceiver_GetStatus() == READY )
		{
			Receiver_GetStringCopy( cMsg );
			DecodeMsg(cMsg);

			if (( ucTokenNr != 0) && ((asToken[0].eType) == KEYWORD) )
			{

				switch(asToken[0].uValue.eKeyword)
				{
					case	DIR_L:
						if ((ucTokenNr = 2) && ((asToken[1].eType) == KEYWORD)) {
						switch(asToken[1].uValue.eKeyword){
							case FRW:
								DriveChangeWheelDirection(WHEEL_LEFT, FORWARD);
								break;
							case BK:
								DriveChangeWheelDirection(WHEEL_LEFT, BACK);
								break;
							default:
								break;
							}
						}
						break;
					case	DIR_R:
						if ((ucTokenNr = 2) && ((asToken[1].eType) == KEYWORD)) {
						switch(asToken[1].uValue.eKeyword){
							case FRW:
								DriveChangeWheelDirection(WHEEL_RIGHT, FORWARD);
								break;
							case BK:
								DriveChangeWheelDirection(WHEEL_RIGHT, BACK);
								break;
							default:
								break;
							}
						}
						break;
					case	BK:
						DriveChangeWheelDirection(WHEEL_LEFT, BACK);
						DriveChangeWheelDirection(WHEEL_RIGHT, BACK);

						DriveChangeWheelSpeed(WHEEL_LEFT, 40U);
						DriveChangeWheelSpeed(WHEEL_RIGHT, 40U);
						break;
					case	FRW:
						DriveChangeWheelDirection(WHEEL_LEFT, FORWARD);
						DriveChangeWheelDirection(WHEEL_RIGHT, FORWARD);

						DriveChangeWheelSpeed(WHEEL_LEFT, 40U);
						DriveChangeWheelSpeed(WHEEL_RIGHT, 40U);
						break;
					case	SP_L:
						if ((ucTokenNr = 2) && ((asToken[1].eType) == NUMBER))
						DriveChangeWheelSpeed(WHEEL_LEFT, asToken[1].uValue.uiNumber);
						break;
					case	SP_R:
						if ((ucTokenNr = 2) && ((asToken[1].eType) == NUMBER))
						DriveChangeWheelSpeed(WHEEL_RIGHT, asToken[1].uValue.uiNumber);
						break;
					case	LEFT:
						DriveChangeWheelDirection(WHEEL_LEFT, BACK);
						DriveChangeWheelDirection(WHEEL_RIGHT, FORWARD);

						DriveChangeWheelSpeed(WHEEL_LEFT, 16U);
						DriveChangeWheelSpeed(WHEEL_RIGHT, 16U);
						break;
					case	RIGHT:
						DriveChangeWheelDirection(WHEEL_LEFT, FORWARD);
						DriveChangeWheelDirection(WHEEL_RIGHT, BACK);

						DriveChangeWheelSpeed(WHEEL_LEFT, 16U);
						DriveChangeWheelSpeed(WHEEL_RIGHT, 16U);
						break;
					case	STOP:
						DriveChangeWheelSpeed(WHEEL_LEFT, 0U);
						DriveChangeWheelSpeed(WHEEL_RIGHT, 0U);
						break;
					case	STOP_L:
						DriveChangeWheelSpeed(WHEEL_LEFT, 0U);
						break;
					case	STOP_R:
						DriveChangeWheelSpeed(WHEEL_RIGHT, 0U);
						break;
					default:
						break;
				}
			}
		}
	  	else if ( eReceiver_GetStatus() == OVERFLOW )
	  	{
	  		Receiver_GetStringCopy( cMsg );
	  	}
  }
}
