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
void beep_init(void);
void beep_stop(void);
void beep_play(uint pitch, uint duration_ms);
void play_welcome(void);

#pragma interrupt_handler TIMER1_COMPA_ISR:7
void TIMER1_COMPA_ISR(void)
{
    PORTA ^= BIT(BEEP);
}

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

    beep_init();
    play_welcome();

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

void beep_init(void)
{
    DDRA |= BIT(BEEP);
    PORTA |= BIT(BEEP);

    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1 = 0;
    OCR1A = 0;
    TIFR |= BIT(OCF1A);
    TIMSK &= ~BIT(OCIE1A);
}

void beep_stop(void)
{
    uchar sreg;

    sreg = SREG;
    SREG &= ~BIT(7);
    TIMSK &= ~BIT(OCIE1A);
    TCCR1B = 0x00;
    TIFR |= BIT(OCF1A);
    PORTA |= BIT(BEEP);
    SREG = sreg;
}

void beep_play(uint pitch, uint duration_ms)
{
    uint half_ticks;

    if (duration_ms == 0)
        return;

    if (pitch == ZERO)
    {
        beep_stop();
        Delayms(duration_ms);
        return;
    }

    half_ticks = 65536U - pitch;
    if (half_ticks == 0)
        half_ticks = 1;

    beep_stop();

    TCNT1 = 0;
    OCR1A = half_ticks - 1;
    TIFR |= BIT(OCF1A);
    TIMSK |= BIT(OCIE1A);
    SREG |= BIT(7);
    TCCR1B = (1 << WGM12) | (1 << CS11);

    Delayms(duration_ms);
    beep_stop();
}

void play_welcome(void)
{
    beep_play(DO, 250);
    beep_play(MI, 250);
    beep_play(SO, 250);
    beep_play(DO_H, 250);
    beep_stop();
}
