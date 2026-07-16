#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define PIR_DETECTED ((PIND & BIT(0)) != 0)

void main()
{
    LEDON();
    SEGOFF();

    DDRB = 0xFF;
    PORTB = 0x00;
    Delayms(1000);
    PORTB = 0xFF;

    DDRD &= ~BIT(0);
    PORTD &= ~BIT(0);

    while (1)
    {
        if (PIR_DETECTED)
            PORTB &= ~BIT(7);
        else
            PORTB |= BIT(7);
    }
}
