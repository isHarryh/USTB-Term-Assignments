#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define NOTE_MS 400
#define GAP_MS 50
#define LOOP_PAUSE_MS 1000

void beep_init(void);
void beep_stop(void);
void beep_play(uint note, uint duration_ms);
void beep_play_notes(const uint *notes, uchar count, uint note_ms, uint gap_ms);

#pragma interrupt_handler TIMER1_COMPA_ISR:7
void TIMER1_COMPA_ISR(void)
{
    PORTA ^= BIT(BEEP);
}

void main()
{
    static const uint scale[] = {
        DO, RE, MI, FA, SO, LA, TI, DO_H};

    SEGOFF();
    LEDOFF();
    beep_init();

    while (1)
    {
        beep_play_notes(scale, 8, NOTE_MS, GAP_MS);
        Delayms(LOOP_PAUSE_MS);
    }
}

void beep_init(void)
{
    DDRA |= BIT(BEEP);
    PORTA &= ~BIT(BEEP);

    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1 = 0;
    OCR1A = 0;
    TIFR |= BIT(OCF1A);
    TIMSK &= ~BIT(OCIE1A);
}

void beep_stop(void)
{
    TCCR1B = 0x00;
    TIMSK &= ~BIT(OCIE1A);
    TIFR |= BIT(OCF1A);
    PORTA &= ~BIT(BEEP);
}

void beep_play(uint note, uint duration_ms)
{
    uint half_ticks;

    if (note == ZERO)
    {
        beep_stop();
        Delayms(duration_ms);
        return;
    }

    half_ticks = 65536U - note;
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

void beep_play_notes(const uint *notes, uchar count, uint note_ms, uint gap_ms)
{
    uchar i;

    for (i = 0; i < count; i++)
    {
        beep_play(notes[i], note_ms);
        if (gap_ms != 0)
            Delayms(gap_ms);
    }
}
