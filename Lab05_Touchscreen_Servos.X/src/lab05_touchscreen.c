#include "lab05_touchscreen.h"

#include <xc.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "types.h"
#include "lcd.h"

#define SERVOx 0
#define SERVOy 1
#define READx 0
#define READy 1
#define Standby 2

uint8_t global_axis=0;

void touchscreen_initialize(){
    //set up the I/O pins E1, E2, E3 to be output pins
    CLEARBIT(TRISEbits.TRISE1); //I/O pin set to output
    CLEARBIT(TRISEbits.TRISE2); //I/O pin set to output
    CLEARBIT(TRISEbits.TRISE3); //I/O pin set to output
    
    SETBIT(PORTEbits.RE1);
    SETBIT(PORTEbits.RE2);
    CLEARBIT(PORTEbits.RE3);
    
    //init ADC
    //disable ADC1
    CLEARBIT(AD1CON1bits.ADON);
    //initialize PIN
    SETBIT(TRISBbits.TRISB15); //set TRISE RB15 to input, X-AXIS
    SETBIT(TRISBbits.TRISB9); //set TRISE RB9 to input, Y-AXIS
    CLEARBIT(AD1PCFGLbits.PCFG15); //set AD1 AN15 input pin as analog
    CLEARBIT(AD1PCFGLbits.PCFG9); //set AD1 AN9 input pin as analog
    //Configure AD1CON1
    CLEARBIT(AD1CON1bits.AD12B); //set 10b Operation Mode 1 CHANNEL
    AD1CON1bits.FORM = 0; //set integer output
    AD1CON1bits.SSRC = 0x7; //set automatic conversion
    //Configure AD1CON2
    AD1CON2 = 0; //not using scanning sampling
    //Configure AD1CON3
    CLEARBIT(AD1CON3bits.ADRC); //internal clock source
    AD1CON3bits.SAMC = 0x1F; //sample-to-conversion clock = 31Tad
    AD1CON3bits.ADCS = 0x2; //Tad = 3Tcy (Time cycles)
    //Leave AD1CON4 at its default value
    //enable ADC
    SETBIT(AD1CON1bits.ADON);
}


void change_dimention(uint8_t axis){
    if(axis == READx){
        CLEARBIT(PORTEbits.RE1);
        Nop();
        SETBIT(PORTEbits.RE2);
        Nop();
        SETBIT(PORTEbits.RE3);
        __delay_ms(10);
        //global_axis = READx;
        AD1CHS0bits.CH0SA = 15; //set ADC to Sample AN15 pin
        
        
    }else if(axis == READy){
        SETBIT(PORTEbits.RE1);
        Nop();
        CLEARBIT(PORTEbits.RE2);
        Nop();
        CLEARBIT(PORTEbits.RE3);
        __delay_ms(10);
        //global_axis = READy;
        AD1CHS0bits.CH0SA = 0x009; //set ADC to Sample AN9 pin
        
    }else if(axis == Standby){
        SETBIT(PORTEbits.RE1);
        Nop();
        SETBIT(PORTEbits.RE2);
        Nop();
        CLEARBIT(PORTEbits.RE3);
        Nop();
    }
    
        /*if(global_axis == READx){
        AD1CHS0bits.CH0SA = 15; //set ADC to Sample AN15 pin
    }else if(global_axis == READy){
        AD1CHS0bits.CH0SA = 9; //set ADC to Sample AN9 pin
    }*/
}

uint16_t read_position(){

    
    SETBIT(AD1CON1bits.SAMP); //start to sample
    while(!AD1CON1bits.DONE); //wait for conversion to finish
    CLEARBIT(AD1CON1bits.DONE); //MUST HAVE! clear conversion done bit
    return ADC1BUF0; //return sample

}
