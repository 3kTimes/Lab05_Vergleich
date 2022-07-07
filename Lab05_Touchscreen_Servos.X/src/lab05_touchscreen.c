#include "lab05_touchscreen.h"

#include <xc.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "types.h"
#include "lcd.h"

#define X 0
#define Y 1
#define x_Axis 0
#define y_Axis 1


/*
 * Function to initilaize ADC1
 */

void ADC1_initialziation(){

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
	
/*
 * Function to initialize touchscreen inclusive the call to initialize_ADC1()
 */	
	

void touchscreen_initialize(){
    //set up the I/O pins E1, E2, E3 to be output pins
    CLEARBIT(TRISEbits.TRISE1); //I/O pin set to output
    CLEARBIT(TRISEbits.TRISE2); //I/O pin set to output
    CLEARBIT(TRISEbits.TRISE3); //I/O pin set to output
    
    SETBIT(PORTEbits.RE1);
    SETBIT(PORTEbits.RE2);
    CLEARBIT(PORTEbits.RE3);
    
    ADC1_initialziation();
}

/*
 * Function to change the dimension (x- or y-Axis) of touchscreen
 * 
 * input: dimension x or y
 */

void changeDimension_touchscreen(uint8_t dimension){
	
    if(dimension == x_Axis){
        CLEARBIT(PORTEbits.RE1);
        Nop();
        SETBIT(PORTEbits.RE2);
        Nop();
        SETBIT(PORTEbits.RE3);
        __delay_ms(10);
        AD1CHS0bits.CH0SA = 0x0F; //set ADC to Sample AN15 pin
        
        
    }else if(dimension == y_Axis){
        SETBIT(PORTEbits.RE1);
        Nop();
        CLEARBIT(PORTEbits.RE2);
        Nop();
        CLEARBIT(PORTEbits.RE3);
        __delay_ms(10);
        AD1CHS0bits.CH0SA = 0x09; //set ADC to Sample AN9 pin
        
    } 
	
	/*
CH0SA<4:0>: Channel 0 Positive Input Select for Sample A bits
11111 = Channel 0 positive input is AN31
11110 = Channel 0 positive input is AN30
•
•
•
00010 = Channel 0 positive input is AN2
00001 = Channel 0 positive input is AN1
00000 = Channel 0 positive input is AN0
 
*/
}


/*
 * Function to get the current coordinate of x- or y-Axis
 * 
 * return value of coordinate
 */

uint16_t currentBallPosition(){

    SETBIT(AD1CON1bits.SAMP); //start to sample
    while(!AD1CON1bits.DONE); //wait for conversion to finish
    CLEARBIT(AD1CON1bits.DONE); //MUST HAVE! clear conversion done bit
    return ADC1BUF0; //return sample

}
