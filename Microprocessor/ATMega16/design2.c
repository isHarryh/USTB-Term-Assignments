#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define LEN_1 1
#define LEN_2 2
#define LEN_4 4
#define LEN_8 8
#define LEN_16 16

#define DEFAULT_BPM 120

static uint g_bpm = DEFAULT_BPM;

void beep_init(void);
void beep_stop(void);
void beep_set_bpm(uint bpm);
uint beep_get_bpm(void);
uint beep_len_to_ms(uchar len);
void beep_play(uint pitch, uint duration_ms);
void beep_play_score_text(const char *score);

#pragma interrupt_handler TIMER1_COMPA_ISR:7
void TIMER1_COMPA_ISR(void)
{
    PORTA ^= BIT(BEEP);
}

static uint pitch_from_name(char name, uchar high_octave)
{
    uint pitch;

    switch (name)
    {
    case 'C':
        pitch = DO;
        break;
    case 'D':
        pitch = RE;
        break;
    case 'E':
        pitch = MI;
        break;
    case 'F':
        pitch = FA;
        break;
    case 'G':
        pitch = SO;
        break;
    case 'A':
        pitch = LA;
        break;
    case 'B':
        pitch = TI;
        break;
    default:
        return ZERO;
    }

    if (high_octave)
    {
        switch (name)
        {
        case 'C':
            return DO_H;
        case 'D':
            return RE_H;
        case 'E':
            return MI_H;
        case 'F':
            return FA_H;
        case 'G':
            return SO_H;
        case 'A':
            return LA_H;
        case 'B':
            return TI_H;
        }
    }

    return pitch;
}

void main()
{
    static const char score[] =
        "E8E8 ^E8^E4^E4E8E8E8 B8.A8.A4B8_8E8 ^E8^E4^E4E8E8E8 B8.A8.A4B8_8E8";

    SEGOFF();
    LEDOFF();
    beep_init();
    beep_set_bpm(DEFAULT_BPM);
    beep_play_score_text(score);

    while (1)
        ;
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

void beep_set_bpm(uint bpm)
{
    if (bpm == 0)
        bpm = 1;
    g_bpm = bpm;
}

uint beep_get_bpm(void)
{
    return g_bpm;
}

uint beep_len_to_ms(uchar len)
{
    if (len == 0)
        len = LEN_4;

    return (uint)(240000UL / g_bpm / len);
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

void beep_play_score_text(const char *score)
{
    const char *s = score;
    uchar high_octave;
    char name;
    uint pitch;
    uint len;
    uint duration_ms;
    uchar dotted;

    while (*s != '\0')
    {
        while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
            s++;

        if (*s == '\0')
            break;

        high_octave = 0;
        if (*s == '^')
        {
            high_octave = 1;
            s++;
        }

        if (*s == '_')
        {
            pitch = ZERO;
            s++;
        }
        else
        {
            name = *s;
            if (name >= 'a' && name <= 'z')
                name = (char)(name - 'a' + 'A');

            if (name < 'A' || name > 'G')
            {
                s++;
                continue;
            }

            pitch = pitch_from_name(name, high_octave);
            s++;
        }

        if (*s < '0' || *s > '9')
            continue;

        len = 0;
        while (*s >= '0' && *s <= '9')
        {
            len = len * 10 + (uint)(*s - '0');
            s++;
        }

        dotted = 0;
        if (*s == '.')
        {
            dotted = 1;
            s++;
        }

        duration_ms = beep_len_to_ms((uchar)len);
        if (dotted)
            duration_ms += duration_ms / 2;

        beep_play(pitch, duration_ms);
    }
}
