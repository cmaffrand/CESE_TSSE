/*=============================================================================
 * Copyright (c) 2021, Carlos Maffrand <carlosmaffrand5@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2021/11/22
 * Version: v1.0
 * Descripcion: archivo de test para el TP3 de Testing de software en sistemas
 * embebidos
 *===========================================================================*/

#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

#define LEDON 3
#define LEDOFF 10
#define INVALID_LED_LOW 0
#define INVALID_LED_HIGH 17

static uint16_t puertoVirtual;

void setUp(void)
{
    LedsCreate(&puertoVirtual);
}

// Revision de que todos los leds deben quedar apagados.
void test_todos_los_leds_inician_apagados(void)
{
    uint16_t puertoVirtual = 0xFFFF;
    LedsCreate(&puertoVirtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

// Prender un led cualuiera
void test_prender_un_led(void)
{
    LedsOn(LEDON);
    TEST_ASSERT_EQUAL_HEX16(1 << LEDON - 1, puertoVirtual);
}

// Apagar un led cualquiera
void test_apagar_un_led(void)
{
    LedsOn(LEDOFF);
    LedsOff(LEDOFF);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

// Prender y apagar algunos leds
void test_prender_y_apagar_leds(void)
{
    LedsOn(LEDON);
    LedsOn(LEDOFF);
    LedsOff(LEDOFF);
    TEST_ASSERT_EQUAL_HEX16(1 << LEDON - 1, puertoVirtual);
}

// Probar valores invalidos para los parametros ledsOn
void test_error_en_parametro_ledsOn(void)
{
    RegistrarMensaje_Expect(0, "LedsOn", 0, "Numero de Led Invalido");
    RegistrarMensaje_IgnoreArg_linea();
    RegistrarMensaje_Expect(0, "LedsOn", 0, "Numero de Led Invalido");
    RegistrarMensaje_IgnoreArg_linea();
    for (uint8_t i = INVALID_LED_LOW; i <= INVALID_LED_HIGH; i++)
    {
        LedsOn(i);
    }
}

// Probar valores invalidos para los parametros ledsOff
void test_error_en_parametro_ledsOff(void)
{
    RegistrarMensaje_Expect(0, "LedsOff", 0, "Numero de Led Invalido");
    RegistrarMensaje_IgnoreArg_linea();
    RegistrarMensaje_Expect(0, "LedsOff", 0, "Numero de Led Invalido");
    RegistrarMensaje_IgnoreArg_linea();
    for (uint8_t i = INVALID_LED_LOW; i <= INVALID_LED_HIGH; i++)
    {
        LedsOff(i);
    }
}

//Prender todos los led juntos
void test_prender_todos_los_leds(void)
{
    allLedsOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puertoVirtual);
}

// Apagar todos los leds juntos
void test_apagar_todos_los_leds(void)
{
    allLedsOn();
    allLedsOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

// Consultar el estado de un led apagado
void test_consultar_estado_led_apagado(void)
{
    uint8_t ledStateValue = 0xFF;
    allLedsOn();
    LedsOff(LEDOFF);
    ledStateValue = LedsState(LEDOFF);
    TEST_ASSERT_EQUAL_HEX8(0x0, ledStateValue);
}

// Consultar el estado de un led encendido
void test_consultar_estado_led_encendido(void)
{
    uint8_t ledStateValue = 0x0;
    allLedsOff();
    LedsOn(LEDON);
    ledStateValue = LedsState(LEDON);
    TEST_ASSERT_EQUAL_HEX8(0x1, ledStateValue);
}
