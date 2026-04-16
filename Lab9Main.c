// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: January 12, 2026

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "Chinese.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"

Chinese_t ChineseChars[] ={
  ying1, zhong, wen, kai, shi1, zan, ting, hui, fu, dan, shuan, ren, mo, shi1, ni, ying2, shu, le, wan, jia, yi, er, null
};
Chinese_t EnglishSel[] = {ying1, wen, slash, null}; //slash between en and zh
Chinese_t ChineseSel[] = {zhong, wen,null};
Chinese_t Start[] = {kai, shi1,null};
Chinese_t Pause[] = {zan, ting,null};
Chinese_t Resume[] = {hui, fu,null};
Chinese_t ManualMode[] = {dan, ren, mo, shi2,null};
Chinese_t MultiplayerMode[] = {shuan, ren, mo, shi2,null};
Chinese_t WinManual[] = {ni, ying2,le, ex, null}; //add an exclamation
Chinese_t LoseManual[] = {ni, shu, le, ex, null};//add exclamation
Chinese_t Player1Wins[] = {wan, jia, yi, ying2, le, ex, null}; //add exclamation
Chinese_t Player2Wins[] = {wan, jia, er, ying2, le,ex, null};//add exclamation

//********ST7735_OutStringLanguage*****************
// Print a string of characters to the ST7735 LCD in either English or Mandarin Chinese
// Position determined by ST7735_SetCursor command
// Color set by ST7735_SetTextColor
// The string will not automatically wrap.
// inputs: ptr  pointer to NULL-terminated ASCII string
//         lang 8-bit integer: 0 for English, 1 for chinese
//         newX New cursor position
// outputs: none
void ST7735_OutStringLanguage(char *ptr, uint8_t lang, uint32_t newX, uint32_t newY) {
  if (!lang) {
    ST7735_SetCursor(newX, newY);
    ST7735_OutString(ptr);
  }
  else {
    Chinese_SetCursor(newX, newY);
    //Chinese_OutString(Chinese_t *ptr)
  }
}


// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

Arabic_t ArabicAlphabet[]={
alif,ayh,baa,daad,daal,dhaa,dhaal,faa,ghayh,haa,ha,jeem,kaaf,khaa,laam,meem,noon,qaaf,raa,saad,seen,sheen,ta,thaa,twe,waaw,yaa,zaa,space,dot,null1
};

Arabic_t Hello[]={alif,baa,ha,raa,meem,null1}; // hello
Arabic_t WeAreHonoredByYourPresence[]={alif,noon,waaw,ta,faa,raa,sheen,null}; // we are honored by your presence
int main0(void){ // main 0, demonstrate Arabic output
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_WHITE);
  Arabic_SetCursor(0,15);
  Arabic_OutString(Hello);
  Arabic_SetCursor(0,31);
  Arabic_OutString(WeAreHonoredByYourPresence);
  Arabic_SetCursor(0,63);
  Arabic_OutString(ArabicAlphabet);
  while(1){
  }
}



//Chinese_t GameStrings[][] = {{EnglishSel, ChineseSel, Start, Pause, Resume, ManualMode, MultiplayerMode, WinManual, LoseManual, Player1Wins, Player2Wins},
   //                         {}};

int main0cn(void){ // main 0mod but for chiense
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_WHITE);
  ST7735_SetRotation(1);
  
  Chinese_SetCursor(0,8);
  Chinese_OutString(EnglishSel);
  // ST7735_SetCursor(16,8);
  // ST7735_OutString("/");
  Chinese_SetCursor(17,8);
  Chinese_OutString(ChineseSel);
  Chinese_SetCursor(33,8);
  Chinese_OutString(Start);
  Chinese_SetCursor(49,8);
  Chinese_OutString(Pause);
  Chinese_SetCursor(65,8);
  Chinese_OutString(Resume);
  Chinese_SetCursor(81,8);
  Chinese_OutString(ManualMode);
  Chinese_SetCursor(64, 16);
  Chinese_OutString( MultiplayerMode);
  Chinese_SetCursor(0,24 );
  Chinese_OutString( WinManual);
  // ST7735_SetCursor(24, 24);
  // ST7735_OutString("!");
  Chinese_SetCursor(25, 24);
  Chinese_OutString( LoseManual);
  ST7735_SetCursor( 49,24 );
  ST7735_OutString("!");
  Chinese_SetCursor(50,24 );
  Chinese_OutString( Player1Wins);
  // ST7735_SetCursor( 80,24 );
  // ST7735_OutString("!");
  Chinese_SetCursor( 81,24 );
  Chinese_OutString( Player2Wins);
  // ST7735_SetCursor( 112,32 );
  // ST7735_OutString("!");


  Chinese_SetCursor(0,40);
  Chinese_OutString(ChineseChars);
  while(1){
  }
}


uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}


// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(0x0000);            // set screen to black
  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<= French; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_WHITE);
  ST7735_SetRotation(1);
  int xPos = 25;
  ST7735_DrawFastVLine(25, 80, 2, ST7735_GREEN);
  //ST7735_DrawBitmap(53, 151, r2, 75,55);
  // ST7735_DrawBitmap(42, 159, r2, 75,55); // player ship bottom
  // ST7735_DrawBitmap(62, 159, r2, 18,8); // player ship bottom
  // ST7735_DrawBitmap(82, 159, r2, 18,8); // player ship bottom
  // ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  // ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  // ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  // ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  // ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  // for(uint32_t t=500;t>0;t=t-5){
  //   SmallFont_OutVertical(t,104,6); // top left
  //   Clock_Delay1ms(50);              // delay 50 msec
  // }
  // ST7735_FillScreen(0x0000);   // set screen to black
  // ST7735_SetCursor(1, 1);
  // ST7735_OutString("GAME OVER");
  // ST7735_SetCursor(1, 2);
  // ST7735_OutString("Nice try,");
  // ST7735_SetCursor(1, 3);
  // ST7735_OutString("Earthling!");
  // ST7735_SetCursor(2, 4);
  // ST7735_OutUDec(1234);
  while(1){
    ST7735_DrawBitmap(xPos, 100, Cow1, 45,29); // player ship bottom
    ST7735_DrawBitmap(80, 100, bevo1, 65, 43);
    //xPos ++;
    //Clock_Delay1ms(50);  
    Clock_Delay1ms(200);  
    ST7735_DrawBitmap(xPos, 100, Cow2, 45,29); // player ship bottom
    ST7735_DrawBitmap(80, 100, bevo2, 65, 43);
    Clock_Delay1ms(200);  
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}
