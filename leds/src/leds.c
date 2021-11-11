
#include "leds.h"
#include "errores.h"

#define LED_ALL_OFF 0x0000;

static uint16_t *puerto;

void LedsCreate(uint16_t *puertoVirtual)
{
    puerto = puertoVirtual;
    *puertoVirtual = LED_ALL_OFF;
}

void LedsOn(uint8_t led)
{
    *puerto |= 1 << led - 1;
}

void LedsOff(uint8_t led)
{
    *puerto &= ~(1 << led - 1);
}