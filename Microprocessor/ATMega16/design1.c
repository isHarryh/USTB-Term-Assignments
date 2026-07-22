#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define LEFT_DETECTED ((PIND & BIT(1)) == 0)
#define RIGHT_DETECTED ((PIND & BIT(2)) == 0)
#define KEY_SPEED_DOWN ((PIND & BIT(3)) == 0)

#define SERVO_LEFT_US 1000
#define SERVO_CENTER_US 1500
#define SERVO_RIGHT_US 2000
#define SERVO_STEP_US 10

#define SWEEP_LEFT 0
#define SWEEP_RIGHT 1

#define SPEED_LOW 0
#define SPEED_MED 1
#define SPEED_HIGH 2

static volatile uchar g_speed = SPEED_HIGH;
static volatile uchar motor_on = 0;
static volatile uchar pwm_cycle = 0;

static const uchar speed_duty[] = {25, 60, 100};

void motor_start(void);
void motor_stop(void);
void servo_write(uint pulse_us);
void beep_init(void);
void beep_stop(void);
void beep_play(uint pitch, uint duration_ms);
void play_welcome(void);
void play_speed_beep(void);
void speed_init(void);

#pragma interrupt_handler TIMER1_COMPA_ISR:7
void TIMER1_COMPA_ISR(void)
{
    PORTA ^= BIT(BEEP);
}

#pragma interrupt_handler TIMER0_COMP_ISR:10
void TIMER0_COMP_ISR(void)
{
    if (motor_on)
    {
        if (pwm_cycle < speed_duty[g_speed])
            PORTB |= BIT(1);
        else
            PORTB &= ~BIT(1);

        pwm_cycle++;
        if (pwm_cycle >= 100)
            pwm_cycle = 0;
    }
    else
    {
        PORTB &= ~BIT(1);
    }
}

void main()
{
    uint servo_pulse = SERVO_CENTER_US;
    uchar sweep_direction = SWEEP_RIGHT;
    uchar left_detected;
    uchar right_detected;
    uchar key_prev = 1;

    SEGOFF();
    LEDOFF();

    DDRB |= BIT(0) | BIT(1) | BIT(2);
    PORTB &= ~(BIT(0) | BIT(1) | BIT(2));

    DDRD &= ~(BIT(0) | BIT(1) | BIT(3));
    PORTD &= ~(BIT(0) | BIT(1));
    PORTD |= BIT(3);

    beep_init();
    speed_init();
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

        if (KEY_SPEED_DOWN && key_prev)
        {
            Delayms(20);
            if (KEY_SPEED_DOWN)
            {
                while (KEY_SPEED_DOWN)
                    ;
                g_speed++;
                if (g_speed > SPEED_HIGH)
                    g_speed = SPEED_LOW;
                play_speed_beep();
            }
        }
        key_prev = KEY_SPEED_DOWN;

        servo_write(servo_pulse);
    }
}

void motor_start(void)
{
    PORTB &= ~BIT(2);
    motor_on = 1;
}

void motor_stop(void)
{
    motor_on = 0;
    PORTB &= ~(BIT(1) | BIT(2));
    pwm_cycle = 0;
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

void speed_init(void)
{
    TIFR |= BIT(OCF0) | BIT(TOV0);
    TIMSK |= BIT(OCIE0);
    SREG |= BIT(7);
    TCCR0 = (1 << WGM01) | (1 << CS01);
    OCR0 = 99;
}

void play_speed_beep(void)
{
    uint pitch;

    if (g_speed == SPEED_LOW)
        pitch = DO_L;
    else if (g_speed == SPEED_MED)
        pitch = DO;
    else
        pitch = DO_H;

    beep_play(pitch, 80);
}
