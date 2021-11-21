/*=============================================================================
 * Copyright (c) 2021, Carlos Maffrand <carlosmaffrand5@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2021/11/22
 * Version: v1.0
 * Descripcion: archivo bajo prueba TP3 de Testing de software en sistemas 
 * embebidos
 *===========================================================================*/

#include "leds.h"
#include "errores.h"

#define LED_ALL_OFF 0x0000
#define LED_ALL_ON 0xFFFF
#define VALID_LED_LOW 1
#define VALID_LED_HIGH 16
#define NULL ((void *)0)
#define SHIFT_VALUE 1
#define MASK_VALUE 1
#define LED_ON 1
#define LED_OFF 0

static uint16_t *puerto;

void LedsCreate(uint16_t *puertoVirtual)
{
    puerto = puertoVirtual;
    *puertoVirtual = LED_ALL_OFF;
}

void LedsOn(uint8_t led)
{
    if (led <= VALID_LED_HIGH && led >= VALID_LED_LOW)
    {
        *puerto |= MASK_VALUE << led - SHIFT_VALUE;
    }
    else
    {
        RegistrarMensaje(0, __FUNCTION__, __LINE__, "Numero de Led Invalido");
    }
}

void LedsOff(uint8_t led)
{
    if (led <= VALID_LED_HIGH && led >= VALID_LED_LOW)
    {
        *puerto &= ~(MASK_VALUE << led - SHIFT_VALUE);
    }
    else
    {
        RegistrarMensaje(0, __FUNCTION__, __LINE__, "Numero de Led Invalido");
    }
}

void allLedsOn(void)
{
    *puerto = LED_ALL_ON;
}

void allLedsOff(void)
{
    *puerto = LED_ALL_OFF;
}

uint8_t LedsState(uint8_t led)
{
    if ((*puerto & MASK_VALUE << led - SHIFT_VALUE) == 0)
    {
        return LED_OFF;
    }
    else
    {
        return LED_ON;
    }
}