#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define LEN_1 1
#define LEN_2 2
#define LEN_4 4
#define LEN_8 8
#define LEN_16 16

/* sounding duration = score duration * NOTE_PLAY_NUM / NOTE_PLAY_DEN */
#define NOTE_PLAY_NUM 1
#define NOTE_PLAY_DEN 2

typedef struct
{
    const char *text;
    uint bpm;
} Score;

static const Score SCORE_OLD = {
    "E8E8 ^E8^E4^E4E8E8E8 B8.A8.A4B808E8 ^E8^E4^E4E8E8E8 B8.A8.A4B808E8",
    120};

static const Score SCORE_NEW = {
    "_A8E8E8E8 E4.D8 C8.D16C8_B8 _A2 A8A8A8A8 A4.G8 E8G8G8F#4 E2",
    80};

#define ACTIVE_SCORE SCORE_NEW

static uint g_bpm = 120;

void beep_init(void);
void beep_stop(void);
void beep_set_bpm(uint bpm);
uint beep_get_bpm(void);
uint beep_len_to_ms(uchar len);
void beep_play(uint pitch, uint duration_ms);
void beep_play_score(const Score *score);
void beep_play_score_text(const char *score);

#pragma interrupt_handler TIMER1_COMPA_ISR:7
void TIMER1_COMPA_ISR(void)
{
    PORTA ^= BIT(BEEP);
}

static uint pitch_from_semitone(uchar semi, uchar octave)
{
    static const uint table_low[12] = {
        DO_L, DOA_L, RE_L, REA_L, MI_L, FA_L,
        FAA_L, SO_L, SOA_L, LA_L, LAA_L, TI_L};
    static const uint table_mid[12] = {
        DO, DOA, RE, REA, MI, FA,
        FAA, SO, SOA, LA, LAA, TI};
    static const uint table_high[12] = {
        DO_H, DOA_H, RE_H, REA_H, MI_H, FA_H,
        FAA_H, SO_H, SOA_H, LA_H, LAA_H, TI_H};

    if (semi >= 12)
        return ZERO;

    if (octave == 0)
        return table_low[semi];
    if (octave == 2)
        return table_high[semi];
    return table_mid[semi];
}

static uchar name_to_semi(char name)
{
    switch (name)
    {
    case 'C':
        return 0;
    case 'D':
        return 2;
    case 'E':
        return 4;
    case 'F':
        return 5;
    case 'G':
        return 7;
    case 'A':
        return 9;
    case 'B':
        return 11;
    default:
        return 0xFF;
    }
}

void main()
{
    SEGOFF();
    LEDOFF();
    beep_init();
    beep_play_score(&ACTIVE_SCORE);

    while (1)
        ;
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

void beep_play_score(const Score *score)
{
    if (score == 0 || score->text == 0)
        return;

    beep_set_bpm(score->bpm);
    beep_play_score_text(score->text);
}

void beep_play_score_text(const char *score)
{
    const char *s = score;
    uchar octave;
    char name;
    uchar semi;
    int accidental;
    uint pitch;
    uint len;
    uint duration_ms;
    uint sound_ms;
    uchar dotted;

    while (*s != '\0')
    {
        while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
            s++;

        if (*s == '\0')
            break;

        if (*s == '0')
        {
            s++;
            pitch = ZERO;
        }
        else
        {
            octave = 1;
            if (*s == '^')
            {
                octave = 2;
                s++;
            }
            else if (*s == '_')
            {
                octave = 0;
                s++;
            }

            name = *s;
            if (name >= 'a' && name <= 'z')
                name = (char)(name - 'a' + 'A');

            semi = name_to_semi(name);
            if (semi == 0xFF)
            {
                s++;
                continue;
            }
            s++;

            accidental = 0;
            if (*s == '#')
            {
                accidental = 1;
                s++;
            }
            else if (*s == 'b')
            {
                accidental = -1;
                s++;
            }

            semi = (uchar)((semi + accidental + 12) % 12);
            pitch = pitch_from_semitone(semi, octave);
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

        if (pitch == ZERO)
        {
            beep_play(ZERO, duration_ms);
        }
        else
        {
            sound_ms = (uint)((unsigned long)duration_ms * NOTE_PLAY_NUM / NOTE_PLAY_DEN);
            if (sound_ms > duration_ms)
                sound_ms = duration_ms;

            beep_play(pitch, sound_ms);
            if (duration_ms > sound_ms)
                beep_play(ZERO, duration_ms - sound_ms);
        }
    }

    beep_stop();
}
