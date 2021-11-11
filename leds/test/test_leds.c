/*
 * Prender todos los led juntos
 * Apagar todos los leds juntos
 * Consultar el estado de un led apagado
 * Consultar el estado de un led encendido
 * Revisar los valores limites de los parametros
 * Probar valores invalidos para los parametros
*/

#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

#define LEDON 3
#define LEDOFF 10

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

// Probar valores invalidos para los parametros
void test_error_en_parametro (void)
{
    RegistrarMensaje_Expect(0, "Leds On", 0, "Numero de Led Invalido");
    RegistrarMensaje_IgnoreArg_linea();
    LedsOn(17);
}