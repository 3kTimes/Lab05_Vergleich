#include "lab05.h"

#include <xc.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "types.h"
#include "lcd.h"
#include "led.h"

#define SERVOx 0
#define SERVOy 1
#define READx 0
#define READy 1
#define Standby 2

/*
 * PWM code
 */


void print_position(){
    uint16_t x_pos;
    uint16_t y_pos;
    
    
    change_dimention(READy);
    //__delay_ms(100);
    y_pos = read_position();
    
    change_dimention(READx);
    x_pos = read_position();
    
    lcd_locate(0, 4);
    lcd_printf("x: %d ; y: %d       ",x_pos,y_pos);

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
    touchscreen_initialize();
    // initialize servos
    servo_initialize(SERVOx);
    servo_initialize(SERVOy);

    
    while(TRUE) {
        set_duty_servo(SERVOx, 0.9);
        set_duty_servo(SERVOy, 0.9);
        __delay_ms(2000);
        print_position();
        __delay_ms(3000);
        
        set_duty_servo(SERVOx, 0.9);
        set_duty_servo(SERVOy, 2.1);
        __delay_ms(2000);
        print_position();
        __delay_ms(3000);
        
        set_duty_servo(SERVOx, 2.1);
        set_duty_servo(SERVOy, 2.1);
        __delay_ms(2000);
        print_position();
        __delay_ms(3000);
        
        set_duty_servo(SERVOx, 2.1);
        set_duty_servo(SERVOy, 0.9);
        __delay_ms(2000);
        print_position();
        __delay_ms(3000);
    }
}