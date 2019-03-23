

#include <stdint.h>
#include <stdio.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define  PRESET (80000000 / 256) / 10
#if PRESET > 0xffff
#error "TimerPeriodIsTooBig"
#endif


int mytime = 0x5957;
int count = 0;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */

void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* portE = (volatile int*) 0xbf886100;
  *portE = *portE & 0xff00;

  TRISDSET = ~ 0x0fe0;

  T2CON = 0x70;
  PR2 = (80000000 / 256) / 10;
  TMR2 = 0x0;
  T2CONSET = 0x8000;
  IEC(0) = IEC(0) | 0x0100;
  return;
}

int timeoutcount;
int ticks = 0;
/* This function is called repetitively from the main program */
void labwork( void )
{

  int btns = getbtns();
  int sw = getsw();

  if(btns & 1){
    mytime = (mytime & 0xff0f) | (sw << 4);
  }
  if(btns & 2){
    mytime = (mytime & 0xf0ff) | (sw << 8);
  }
  if(btns & 4){
    mytime = (mytime & 0x0fff) | (sw << 12);
  }

  if(IFS(0) & 0x100){
    IFSCLR(0) = 0x100;
    timeoutcount++;

    if(timeoutcount == 10){
    //time2string( textstring, mytime );
    //display_string( 0, textstring );
    display_update();
    //tick( &mytime );
    //display_image(0, dino);
    ticks++;
    volatile int* porte = (volatile int*) 0xbf886110;
    *porte = ticks;
    timeoutcount = 0;
    }
  }
}
