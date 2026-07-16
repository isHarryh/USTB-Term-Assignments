#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define LEFT_DETECTED ((PIND & BIT(0)) != 0)
#define RIGHT_DETECTED ((PIND & BIT(1)) != 0)

#define SERVO_LEFT_US 1000
#define SERVO_CENTER_US 1500
#define SERVO_RIGHT_US 2000
#define SERVO_STEP_US 10

#define SWEEP_LEFT 0
#define SWEEP_RIGHT 1

void motor_start(void);
void motor_stop(void);
void servo_write(uint pulse_us);

void main()
{
    uint servo_pulse = SERVO_CENTER_US;
    uchar sweep_direction = SWEEP_RIGHT;
    uchar left_detected;
    uchar right_detected;

    SEGOFF();
    LEDOFF();

    DDRB |= BIT(0) | BIT(1) | BIT(2);
    PORTB &= ~(BIT(0) | BIT(1) | BIT(2));

    DDRD &= ~(BIT(0) | BIT(1));
    PORTD &= ~(BIT(0) | BIT(1));

    while (1)
    {
        left_detected = LEFT_DETECTED;
        right_detected = RIGHT_DETECTED;

        if (!left_detected && !right_detected)
        {
            motor_stop();
        }
        else
        {
            motor_start();

            if (left_detected && !right_detected)
            {
                servo_pulse = SERVO_LEFT_US;
                sweep_direction = SWEEP_RIGHT;
            }
            else if (!left_detected && right_detected)
            {
                servo_pulse = SERVO_RIGHT_US;
                sweep_direction = SWEEP_LEFT;
            }
            else if (sweep_direction == SWEEP_RIGHT)
            {
                if (servo_pulse < SERVO_RIGHT_US)
                    servo_pulse += SERVO_STEP_US;
                else
                    sweep_direction = SWEEP_LEFT;
            }
            else
            {
                if (servo_pulse > SERVO_LEFT_US)
                    servo_pulse -= SERVO_STEP_US;
                else
                    sweep_direction = SWEEP_RIGHT;
            }
        }

        servo_write(servo_pulse);
    }
}

void motor_start(void)
{
    PORTB |= BIT(1);
    PORTB &= ~BIT(2);
}

void motor_stop(void)
{
    PORTB &= ~(BIT(1) | BIT(2));
}

void servo_write(uint pulse_us)
{
    PORTB |= BIT(0);
    Delayus(pulse_us);
    PORTB &= ~BIT(0);

    Delayms(18);
    Delayus(SERVO_RIGHT_US - pulse_us);
}
