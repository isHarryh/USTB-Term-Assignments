#include "iom16v.h"
#include <macros.h>
#include <AVR_HJ-2G.H>

#define PIR_DETECTED ((PIND & BIT(0)) != 0)

void main()
{
    LEDON();
    SEGOFF();

    DDRD &= ~BIT(0);
    PORTD &= ~BIT(0);

    DDRB |= BIT(7);
    PORTB |= BIT(7);

    while (1)
    {
        if (PIR_DETECTED)
            PORTB &= ~BIT(7);
        else
            PORTB |= BIT(7);
    }
}
