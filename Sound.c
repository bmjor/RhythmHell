// Sound.c
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// your name
// your data 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/Timer.h"
#include "../inc/DAC.h" 

//#include "../inc/FIFO1.h"
//#include "FIFO2.h"

#define BEATLEN 8996
#define COW1LEN 10632
#define COW2LEN 10632
//#define COW2LEN 9450
#define ONELEN 3686
#define TWOLEN 2621
#define THREELEN 1966
#define GOLEN 2675

static uint32_t beatIndex;
static uint32_t cow1Index;
static uint32_t cow2Index;
static uint32_t oneIndex;
static uint32_t twoIndex;
static uint32_t threeIndex;
static uint32_t goIndex;


void SysTick_IntArm(uint32_t period, uint32_t priority){
  SysTick->CTRL = 0x00;
  SysTick->LOAD = period-1;

  SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|priority << 30;

  SysTick->VAL = 0; // Clear count
  SysTick->CTRL = 0x07; 
  // write this
}
// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5-bit DAC
void Sound_Init(void){
// write this
  DAC_Init();
  SysTick_IntArm(7256, 0); // (80MHz/11KHz) - 1
  beatIndex = BEATLEN;
  cow1Index = COW1LEN;
  cow2Index = COW2LEN;
  oneIndex = ONELEN;
  twoIndex = TWOLEN;
  threeIndex = THREELEN;
  goIndex = GOLEN;
}
void SysTick_Handler(void){ // called at 11 kHz
  uint32_t sum = 0;
  uint32_t stream1 = 0, stream2 = 0, stream3 = 0;
  uint8_t active_streams = 0;
  if (beatIndex < BEATLEN) {
    stream1 = metronome[beatIndex]; // change later
    beatIndex++;
    active_streams++;
  }
  if (cow1Index < COW1LEN) {
    stream2 = cow_high[cow1Index];
    cow1Index++;
    active_streams++;
  }
  if (cow2Index < COW2LEN) {
    stream3 = cow_high[cow2Index];
    cow2Index++;
    active_streams++;
  }
  if (oneIndex < ONELEN) {
    stream3 = one[oneIndex];
    oneIndex++;
    active_streams++;
  }
  if (twoIndex < TWOLEN) {
    stream3 = two[twoIndex];
    twoIndex++;
    active_streams++;
  }
  if (threeIndex < THREELEN) {
    stream3 = three[threeIndex];
    threeIndex++;
    active_streams++;
  }
  if (goIndex < GOLEN) {
    stream3 = go[goIndex];
    goIndex++;
    active_streams++;
  }


  sum = stream1 + stream2 + stream3;
  if (active_streams > 0){
    DAC_Out(sum/active_streams); // to prevent peaking
    //DAC_Out(sum/4);
  }
  else {
    DAC_Out(0);
  }
}

// //******* Sound_Start ************
// // This function does not output to the DAC. 
// // Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// // It starts the sound, and the SysTick ISR does the output
// // feel free to change the parameters
// // Sound should play once and stop
// // Input: pt is a pointer to an array of DAC outputs
// //        count is the length of the array
// //        channel is either 0 or 1
// // Output: none
// // special cases: as you wish to implement
// void Sound_Start(const uint32_t *pt, uint32_t count){
// // write this
  
// }
void Sound_Cow1(void){
// write this
  cow1Index = 0;
}
void Sound_Cow2(void){
// write this
  cow2Index = 0;
}
void Sound_Beat(void){
// write this
  beatIndex = 0;
}
void Sound_Count(uint8_t index) {
  if (index == 0)  threeIndex = 0;
  else if (index == 1) twoIndex = 0;
  else if (index == 2) oneIndex = 0;
  else if (index == 3) goIndex = 0;
}
