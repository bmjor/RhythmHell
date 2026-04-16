/*
 * Switch.c
 *
 *  Created on: January 12, 2026
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
  IOMUX->SECCFG.PINCM[PB0INDEX] = 0x00040081; // player one button
  IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00040081; // player two button
  IOMUX->SECCFG.PINCM[PB2INDEX] = 0x00040081; // pause button
}
// return current state of switches
uint32_t Switch_In(void){
  return GPIOB->DIN31_0&(0x07); // replace this line
}
