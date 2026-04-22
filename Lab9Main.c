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
#include "../inc/DAC.h"
//#include "../inc/Arabic.h"
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
/*
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


*/
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

struct sprite {
  int32_t x;      // x coordinate
  int32_t y;      // y coordinate
  const unsigned short *images[3];
  uint8_t state; // index to the images
  uint16_t health;   //65535     
  int32_t w; // width
  int32_t h; // height
  uint8_t needDraw; // true if need to draw
};
typedef struct sprite sprite_t;


// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_WHITE);
  ST7735_SetRotation(1);
  int xPos = 25;
  ST7735_DrawFastHLine(25, 30, 135, ST7735_BLACK);
  // sprite_t cow1;
  // sprite_t cow2;
  // cow1.x = 25
  // cow1.y = 100;
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
  ST7735_DrawBitmap(15, 160, box_charcoal, 60,60);
  ST7735_DrawBitmap(90, 160, box_orange, 60,60);
  while(1){
    ST7735_DrawBitmap(xPos, 100, Cow1N, 45,29); // player ship bottom
    ST7735_DrawBitmap(80, 100, bevoN, 65, 43);
    //xPos ++;
    //Clock_Delay1ms(50);  
    Clock_Delay1ms(200);  
    ST7735_DrawBitmap(xPos, 100, Cow1S, 45,29); // player ship bottom
    ST7735_DrawBitmap(80, 100, bevoS, 65, 43);
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
  Sound_Init(); // 
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_ORANGE);
  ST7735_SetRotation(1);
  uint32_t last=0,now;
  __enable_irq();
  while(1){
    now = Switch_In();
    // write code to test switches and LEDs
   if (Switch_In() == 1){
    ST7735_DrawBitmap(80, 100, bevoS, 65, 43);
    Sound_Cow2();

   }
   else if (Switch_In() == 2) {
    ST7735_DrawBitmap(80, 100, bevoS, 65, 43);
    Sound_Cow2();
   }
   else if (Switch_In() == 4) {
    ST7735_DrawBitmap(25, 100, Cow1S, 45,29); // player ship bottom
    Sound_Beat();
   } 
   else {
    ST7735_DrawBitmap(25, 100, Cow1N, 45,29); // player ship bottom
    ST7735_DrawBitmap(80, 100, bevoN, 65, 43);
   }
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
      Sound_Cow1(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Cow2(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Beat(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}


sprite_t cow1;
sprite_t cow2;
sprite_t bevo;
uint8_t semaphore; 
uint8_t gameMode; // 1 for 1 player mode, 2 for 2 player mode
uint8_t gameRound; // index for 2D array of rounds
uint8_t gameState; // 0 for when not accepting input, 1 for copying rhythm, 2 for creating rhythm
uint8_t paused; // indicates whether game is paused or not
uint8_t currentPlayer = 1; 
uint32_t globalcountr;
uint8_t currNote = 0;
uint32_t window = 50;//flexible
uint32_t pbwindow = 25;//half of window. used for gamestate 0
uint32_t noteArrayLen = 19; //max length - 1
uint32_t noteArray[15][20];// todo: initialize 
uint32_t watchrr = 0;

int main(void) {
  uint8_t gmtest = 1; //0 -> single player, 1 -> multiplayer. use for testing
  uint8_t lastwatch = 0;
  //
  __disable_irq();
  ADCinit();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  //Sound_Init(); // 
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_ORANGE);
  ST7735_SetRotation(1);
  noteArray[0][0] = 100;
  noteArray[0][1] = 200;
  noteArray[0][2] = 300;
  noteArray[0][3] = 400;
  noteArray[0][4] = 500;
  noteArray[0][5] = 600;
  noteArray[0][6] = 700;
  noteArray[0][7] = 800;
  noteArray[0][8] = 900;
  noteArray[0][9] = -1;
  globalcountr  = 0;
  currNote = 0;
  cow1 = (sprite_t){.x = 25, .y = 100, .w = 45, .h = 29, .health = 10000, .images = {Cow1N, Cow1S, 0}, .state = 0};
  bevo = (sprite_t){.x = 80, .y = 100, .w = 65, .h = 43, .health = 10000, .images = {bevoN, bevoS, 0}, .state = 0};

  TimerG0_IntArm(40000, 4, 1); // 500hz
  TimerG12_IntArm(1600000,2); // 50hz -> 80MHZ/50HZ = 1600000
  if (gmtest==0){
  gameRound = 0;
  gameMode = 1; //testing single player
  gameState = 0; //init @ gs0
  currentPlayer = 1; //needed for single player
  }
  else if (gmtest==1){
    gameRound = 0;
    gameMode = 2;
    gameState = 2; //init @gs2
    currentPlayer = 1;
  }
  __enable_irq();
  while(1){
    ST7735_DrawBitmap(25, 100, cow1.images[cow1.state], 45, 29);
    ST7735_DrawBitmap(80, 100, bevo.images[bevo.state], 65, 43);
    if(lastwatch!=watchrr){
    ST7735_OutUDec(watchrr);
    }
    lastwatch = watchrr;
  }
}



// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_BLACKTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_ORANGE);
  ST7735_SetRotation(1);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(1600000,2); // 50hz -> 80MHZ/50HZ = 1600000
  TimerG0_IntArm(40000, 4, 1); // 500hz

  while(1){
    if (paused) {
      __disable_irq();
      uint8_t tempGameMode = gameMode;
      // draw pause screen

      // JUSTIN: make pause screen, and indicate to user somehow that rehitting pause button will resume, and any other button will return to main menu/start screen  
      // ST7735_DrawBitmap();
      ST7735_FillScreen(ST7735_BLUE); // temp, remove 

      // Pause screen logic(Already done)
      while (Switch_In() == 0) {
      }
      uint32_t press = Switch_In();
      if (press == 4) {
        gameMode = tempGameMode;
      }
      else {
        gameMode = 0; // if return to home is pressed, set gameMode = 0
      }
      while (Switch_In() != 0) {}
      // logic
      paused = 0;
      __enable_irq();
    }
    else if (gameMode == 0) {
      __disable_irq();
      // start screen
      cow1 = (sprite_t){.x = 25, .y = 100, .w = 45, .h = 29, .health = 65535, .needDraw = 1, .images = {Cow1N, Cow1S, 0}, .state = 0}; // p1 cow
      bevo = (sprite_t){.x = 80, .y = 100, .w = 65, .h = 43, .health = 65535, .needDraw = 1, .images = {bevoN, bevoS, 0}, .state = 0};  // bevo
      
      // JUSTIN: Ditto for the start screen.
      // ST7735_DrawBitmap();
      
      ST7735_FillScreen(ST7735_WHITE); // temp, remove

        //wait for player input to choose mode
      while (Switch_In() == 0 || Switch_In() == 4) {
      }
      gameMode = Switch_In();
      while (Switch_In() != 0) {}
      //draw background
      ST7735_FillScreen(ST7735_WHITE);
      ST7735_DrawBitmap(15, 160, box_charcoal, 60,60);
      ST7735_DrawBitmap(90, 160, box_orange, 60,60);

      __enable_irq();
    }
    
    else if (gameMode == 1) {
      // one player mode
      if (semaphore) {
        //update display
        ST7735_DrawBitmap(cow1.x, cow1.y, cow1.images[cow1.state], cow1.w,cow1.h);
        ST7735_DrawBitmap(bevo.x, bevo.y, bevo.images[bevo.state], bevo.w,bevo.h);
        semaphore = 0;
      }
    }
    else if (gameMode == 2) {
      // two player mode
      if (semaphore) {
        //update display
        ST7735_DrawBitmap(cow1.x, cow1.y, cow1.images[cow1.state], cow1.w,cow1.h);
        // ST7735_DrawBitmap(bevo.x, bevo.y, bevo.images[bevo.state], 60,60);
        semaphore = 0;
      }
    }

    if ((gameRound >= 15 && gameMode == 1) || cow1.health == 0 || bevo.health == 0) { // edit to be number of rounds
      // win/lose screen
      if (cow1.health == 0) {
        if (gameMode == 1){
          ST7735_OutString("You Lose!");
        }
        else {
          ST7735_OutString("P2 Wins!");
        }
      }
      else if (bevo.health == 0) {
        ST7735_OutString("P1 Wins!");
      }
      else if (gameRound >= 15 && gameMode == 1) {
        ST7735_OutString("You Win!");
      }

      while (Switch_In() == 0) {
      }
      gameMode = 0; 
      
      while (Switch_In() != 0) {}
    }
    
  }
}

// games  engine runs at 50Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  static uint8_t numBeats = 0;
  static uint32_t buffer = 0;
  static uint32_t counter = 30;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    if (numBeats >= 4) {

      globalcountr = 0;
      currNote = 0;
      if (gameMode == 1) {
        if (gameState == 0) {
          // reset global variables for new round
          gameState = 1;
        }
        else{
          gameRound++;
          gameState = 0;
        }

      }
      else if (gameMode == 2){
        if (gameState == 2) {
          gameState = 1;
          currentPlayer^=0x3;
        }
        else {
          gameRound++;
          gameState = 2;
        }
      }
      numBeats = 0; //reset number of beats
      
    }
    else {
      buffer = ADCin();
      if (counter == 0) {
        //counter = 30; //change to buffer
        counter = buffer;
        numBeats++;
        cow1.y += 1;
        Sound_Beat();
      }
      else {
        counter--;
      }
    }
    semaphore = 1;
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore

    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}


// switches run at 500hz
void TIMG0_IRQHandler(void) {
//todo: testcases for main, other sprite stuff
  static uint8_t laststate = 0;
  static uint8_t laststateforotherplayer = 0; 
  static uint8_t valid = 0;

  if((TIMG0->CPU_INT.IIDX) == 1){ 
if(Switch_In()&0x4){
  paused = 1;
}
else{
  paused = 0;
}
  globalcountr++; 
  //for when other player inputs
  if((Switch_In()&(currentPlayer^0x03))){
    if (currentPlayer==2){
      cow1.state = 1;
      if(!laststateforotherplayer){
          Sound_Cow1();
        }
    }
    else{
      bevo.state = 1;
      if(!laststateforotherplayer){
        Sound_Cow2();
      }
    }
  laststateforotherplayer = 1;
}
else{
  laststateforotherplayer=0;
    if (currentPlayer==2){
      cow1.state = 0;
    }
    else{
      bevo.state = 0;
    }

}
uint32_t IndexOnce = noteArray[gameRound][currNote];
watchrr = IndexOnce;
//gs2 -> 2nd player inputting
  if (gameState ==2){
   // GlobalcurrArray = GlobalcurrArray%2; //0/1 i dont update the gameround 
    //add stuff later for storing rhythm from othe rplayer// addded 

    if(Switch_In() & currentPlayer){
        if (currentPlayer==1){
          cow1.state = 1;
          Sound_Cow1();

          if((!laststate)&&(currNote!=noteArrayLen)&&(globalcountr>window)){
            noteArray[gameRound][currNote] = globalcountr;
            currNote++;
          }
        }
        else{
          bevo.state = 1;
          Sound_Cow2();
          if((!laststate)&&(currNote!=noteArrayLen)&&(globalcountr>window)){
            noteArray[gameRound][currNote] = globalcountr;
            currNote++;
            
          }
        }
        
        laststate=1;
      }
      else{
      laststate =0;
        if (currentPlayer==1){
          cow1.state =0;
        }
        else{
          bevo.state = 0;
        }
      //setup main testcase and debug after 
    }
    } 

    //p1 hitting notes
  else if (gameState ==1){ 
    
    if(globalcountr==(IndexOnce - window)){ //enterring hitwindow
      valid = 1;
      
    }
    else if ((globalcountr ==(IndexOnce+window))&&(IndexOnce!=-1)){//exiting hitwindow
      valid = 0;
      if (currentPlayer ==1){
          cow1.health--;
          cow1.state = 2;
//          Sound_Cow1Hurt(); MISSED NOTE COW 1 DUMMY FUNC
      }
      else{
        bevo.health--;
        bevo.state = 2;
//          Sound_Cow2Hurt(); MISSED NOTE COW 1 DUMMY FUNC
      }
      currNote ++;
    }//detecting inputs
    if((Switch_In() & currentPlayer)){ //p1 = binary 01, p2 = binary 10
      if(!laststate){  
        if (valid){
          valid = 0;
          currNote++;
          if(currentPlayer ==1)  {
            cow1.state = 1;
            Sound_Cow1();
          }
          else{
            bevo.state =1;
            Sound_Cow2();
          }
                }
        else{
          if(currentPlayer ==1){
            cow1.health--;
            cow1.state = 2;
//          Sound_Cow1Hurt(); MISSED NOTE COW 1 DUMMY FUNC
                    }
          else{
            bevo.health--;
            bevo.state = 2;
//          Sound_Cow2Hurt(); MISSED NOTE COW 2 DUMMY FUNC
          }

        }
    laststate = 1;
    }
    else{
      laststate=0;
    }
    }
    else{
      if (currentPlayer==2){
      bevo.state = 0;
      }
      else 
      {
      cow1.state = 0;
      }
  }
}

  else if (gameState ==0){
    if(IndexOnce!=-1){
        //playback has playback cap dependent on window; might use a seperate var for this, tbd
      if((globalcountr>=IndexOnce-pbwindow/2)&&(globalcountr<=IndexOnce+window)){//playing notes doesnt need to account for which player b/c only accessible from 1p
        bevo.state = 1;
        if (globalcountr==IndexOnce){
        Sound_Cow2();

        }
        else if(globalcountr==IndexOnce+window){
        currNote++;
        }
      }
      else{
        bevo.state = 0;
      }
    }
  }


  }
}
