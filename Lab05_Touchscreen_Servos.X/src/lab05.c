#include "lab05.h"

#include <xc.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "types.h"
#include "lcd.h"
#include "led.h"

#define X 0
#define Y 1
#define x_Axis 0
#define y_Axis 1
#define Null_degree 0.9
#define Ninety_degree 1.5
#define HundredEighty_degree 2.1


/*
 * PWM code
 */


void printCurrentPosition_XY(){
	
    uint16_t x_pos;
    uint16_t y_pos;
    
    changeDimension_touchscreen(y_Axis);
    y_pos = currentBallPosition();
    
    changeDimension_touchscreen(x_Axis);
    x_pos = currentBallPosiion();
    
    lcd_locate(0, 5);
    lcd_printf("x/y %3d/%3d",x_pos,y_pos);

}

#define TCKPS_1   0x00
#define TCKPS_8   0x01
#define TCKPS_64  0x02
#define TCKPS_256 0x03

#define PWM_MIN_US 1000
#define PWM_MID_US 1500
#define PWM_MAX_US 2000
#define PWM_CYC_US 20000

/*
 * touch screen code
 */


/*
 * main loop
 */

void main_loop()
{
    // print assignment information
    lcd_printf("Lab05: Touchscreen &\r\n");
    lcd_printf("       Servos");
    lcd_locate(0, 2);
    lcd_printf("Group2: Boyang & Ron");
    
    // initialize touchscreen
    touchscreen_initialization();
	
    // initialize servos
    servo_initialization(SERVOx);
    servo_initialization(SERVOy);

    
    while(TRUE) {
		
        set_dutyCycle(X, Null_degree);
        set_dutyCycle(Y, Null_degree);
        __delay_ms(2000);
        printCurrentPosition_XY()
        __delay_ms(3000);
        
        set_dutyCycle(X , Null_degree);
        set_dutyCycle(Y , HundredEighty_degree);
        __delay_ms(2000);
        printCurrentPosition_XY()
        __delay_ms(3000);
        
        set_dutyCycle(X , HundredEighty_degree);
        set_dutyCycle(Y , HundredEighty_degree);
        __delay_ms(2000);
        printCurrentPosition_XY()
        __delay_ms(3000);
        
        set_dutyCycle(X , HundredEighty_degree);
        set_dutyCycle(Y , Null_degree);
        __delay_ms(2000);
        printCurrentPosition_XY()
        __delay_ms(3000);
    }
}