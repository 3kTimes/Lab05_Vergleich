#include "lab05_servo.h"

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

void servo_initialize(uint8_t servoNr)
{
    //setup timer 2
    CLEARBIT(T2CONbits.TON); // Disable Timer
    CLEARBIT(T2CONbits.TCS); // Select internal instruction cycle clock
    CLEARBIT(T2CONbits.TGATE); // Disable Gated Timer mode
    TMR2 = 0x00; // Clear timer register
    T2CONbits.TCKPS = 0b10; // Select 1:64 Prescaler
    CLEARBIT(IFS0bits.T2IF); // Clear Timer2 interrupt status flag
    CLEARBIT(IEC0bits.T2IE); // Disable Timer2 interrupt enable control bit
    PR2 = 4000; // Set timer period 20ms:
    // 4000= 20*10^-3 * 12.8*10^6 * 1/64
    if(servoNr == SERVOx){
        //setup OC8
        CLEARBIT(TRISDbits.TRISD7); /* Set OC8 as output */
        OC8R = 300; /* Set the initial duty cycle to 5ms*/
        OC8RS = 300; /* Load OCRS: next pwm duty cycle */
        OC8CON = 0x0006; /* Set OC8: PWM, no fault check, Timer2 because the 4th bit is 0(1for timer3)*/
        
    }else if(servoNr == SERVOy){
        //setup OC7
        CLEARBIT(TRISDbits.TRISD6); /* Set OC7 as output, */
        OC7R = 300; /* Set the initial duty cycle to 5ms*/
        OC7RS = 300; /* Load OCRS: next pwm duty cycle */
        OC7CON = 0x0006; /* Set OC8: PWM, no fault check, Timer2 because the 4th bit is 0(1for timer3)*/
    }
    
    SETBIT(T2CONbits.TON); /* Turn Timer 2 on */
}

void set_duty_servo(uint8_t servoNr, float duty_mili){

    if(servoNr == SERVOx){
        //setup OC8
        OC8RS = (uint16_t)(4000-duty_mili*200); /* Load OCRS: next pwm duty cycle , 4000-XX because of inversion*/
          
    }else if(servoNr == SERVOy){
        //setup OC7
        OC7RS = (uint16_t)(4000-duty_mili*200); /* Load OCRS: next pwm duty cycle */
    }

}
