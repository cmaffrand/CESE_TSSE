#include "build/test/mocks/mock_errores.h"
#include "src/leds.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








static uint16_t puertoVirtual;



void setUp(void)

{

    LedsCreate(&puertoVirtual);

}





void test_todos_los_leds_inician_apagados(void)

{

    uint16_t puertoVirtual = 0xFFFF;

    LedsCreate(&puertoVirtual);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_un_led(void)

{

    LedsOn(3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 3 - 1)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_HEX16);

}





void test_apagar_un_led(void)

{

    LedsOn(10);

    LedsOff(10);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_leds(void)

{

    LedsOn(3);

    LedsOn(10);

    LedsOff(10);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 3 - 1)), (UNITY_INT)(UNITY_INT16)((puertoVirtual)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_HEX16);

}





void test_error_en_parametro (void)

{

    RegistrarMensaje_CMockExpect(59, 0, "Leds On", 0, "Numero de Led Invalido");

    RegistrarMensaje_CMockIgnoreArg_linea(60);

    LedsOn(17);

}
