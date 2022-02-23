#ifdef TEST

#include "unity.h"
#include <stdbool.h>
#include "mainfsm.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// Test de inicializacion de FSM
void test_mainfsm_inicializacion_fsm(void)
{
    fsmInit();
    mainFsmStates_t state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
}

// Test Recibir un comnado Load Dynamic (LD)
void test_mainfsm_recibir_cmd_LD(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(WAITLS, state);
}

// Test Recibir un comnado Load Static (LS)
void test_mainfsm_recibir_cmd_LS(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(WAITLD, state);
}

// Test from init to unconfig via (LD,LS)
void test_mainfsm_to_unconfig_LD_LS(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LD);
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
}

// Test from init to unconfig via (LS,LD)
void test_mainfsm_to_unconfig_LS_LD(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
}

// Test from init to not unconfig via (LD,LD)
void test_mainfsm_to_not_unconfig_LD_LD(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LD);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(WAITLS, state);
}

// Test from init to not unconfig via (LS,LS)
void test_mainfsm_to_not_unconfig_LS_LS(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(WAITLD, state);
}

// Test from unconfig to armed via (CFG)
void test_mainfsm_to_armed_CFG(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
}

// Test from armed to report via (RUN)
void test_mainfsm_to_armed_RUN(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    state = getState();
    TEST_ASSERT_EQUAL(REPORT, state);
}

// Test from report to armed via (CFG)
void test_mainfsm_from_report_to_armed_CFG(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(CFG);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
}

// Test from report to end via (GR)
void test_mainfsm_from_report_to_end_GR(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    state = getState();
    TEST_ASSERT_EQUAL(END, state);
}

// Test from end to armed via (CFG)
void test_mainfsm_from_end_to_armed_CFG(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LD);
    fsmCmd(LS);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    fsmCmd(CFG);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
}

// Test from all states to inti via (RST)
void test_mainfsm_reset_RST(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LD);
    fsmCmd(RST);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(LD);
    fsmCmd(LS);
    fsmCmd(RST);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(LD);
    fsmCmd(LS);
    fsmCmd(CFG);
    fsmCmd(RST);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(LD);
    fsmCmd(LS);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(RST);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(LD);
    fsmCmd(LS);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    fsmCmd(RST);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
}

// Test de comandos incorrectos en INIT
void test_mainfsm_incorrect_cmd_init(void)
{
    fsmInit();
    mainFsmStates_t state;
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(CFG);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(RUN);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
    fsmCmd(GR);
    state = getState();
    TEST_ASSERT_EQUAL(INIT, state);
}

// Test de comandos incorrectos en UNCONFIG
void test_mainfsm_incorrect_cmd_unconfig(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
    fsmCmd(RUN);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
    fsmCmd(GR);
    state = getState();
    TEST_ASSERT_EQUAL(UNCONFIG, state);
}

// Test de comandos incorrectos en ARMED
void test_mainfsm_incorrect_cmd_armed(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
    fsmCmd(CFG);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
    fsmCmd(GR);
    state = getState();
    TEST_ASSERT_EQUAL(ARMED, state);
}

// Test de comandos incorrectos en REPORT
void test_mainfsm_incorrect_cmd_report(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    state = getState();
    TEST_ASSERT_EQUAL(REPORT, state);
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(REPORT, state);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(REPORT, state);
    fsmCmd(RUN);
    state = getState();
    TEST_ASSERT_EQUAL(REPORT, state);
}

// Test de comandos incorrectos en END
void test_mainfsm_incorrect_cmd_end(void)
{
    fsmInit();
    mainFsmStates_t state;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    state = getState();
    TEST_ASSERT_EQUAL(END, state);
    fsmCmd(LS);
    state = getState();
    TEST_ASSERT_EQUAL(END, state);
    fsmCmd(LD);
    state = getState();
    TEST_ASSERT_EQUAL(END, state);
    fsmCmd(RUN);
    state = getState();
    TEST_ASSERT_EQUAL(END, state);
}

// Test evento NONE en INIT
void test_mainfsm_generar_evento_NONE(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test evento Load Dynamic (LD)
void test_mainfsm_generar_evento_LD(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test evento Load Static (LS)
void test_mainfsm_generar_evento_LS(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test evento Reload Load Dynamic (LD-LD)
void test_mainfsm_generar_evento_LDLD(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test evento Reload Load Static (LS-LS)
void test_mainfsm_generar_evento_LSLS(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test no generacion de eventos en WAITLS
void test_mainfsm_no_generar_eventos_en_waitls(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LD);
    resetEvent();
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test no generacion de eventos en WAITLD
void test_mainfsm_no_generar_eventos_en_waitld(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    resetEvent();
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test de generacion de eventos en pasaje a UNCONFIG
void test_mainfsm_generar_evento_to_unconfig(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    fsmCmd(RST);
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test generacion de eventos en UNCONFIG
void test_mainfsm_generar_eventos_unconfig(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    resetEvent();
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    event = getEvent();
    resetEvent();
    fsmCmd(CFG);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_CFG, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test no generacion de eventos en unconfig
void test_mainfsm_no_generar_eventos_en_unconfig(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    resetEvent();
    fsmCmd(RUN);
    fsmCmd(GR);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test de generacion de eventos ARMED
void test_mainfsm_generar_evento_armed(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    resetEvent();
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(CFG);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_CFG, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(RUN);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_RUN, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test no generacion de eventos en armed
void test_mainfsm_no_generar_eventos_en_armed(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    resetEvent();
    fsmCmd(GR);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test de generacion de eventos REPORT
void test_mainfsm_generar_evento_report(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    resetEvent();
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(CFG);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_CFG, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    fsmCmd(RUN);
    resetEvent();
    fsmCmd(GR);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_GR, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test no generacion de eventos en report
void test_mainfsm_no_generar_eventos_en_report(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    resetEvent();
    fsmCmd(RUN);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test de generacion de eventos END
void test_mainfsm_generar_evento_end(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    resetEvent();
    fsmCmd(LS);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LS, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(LD);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_LD, event);
    TEST_ASSERT_EQUAL(true, newEvent);
    resetEvent();
    fsmCmd(CFG);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_CFG, event);
    TEST_ASSERT_EQUAL(true, newEvent);
}

// Test no generacion de eventos en end
void test_mainfsm_no_generar_eventos_en_end(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    resetEvent();
    fsmCmd(RUN);
    fsmCmd(GR);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

// Test Reset events in reset
void test_mainfsm_reset_eventos_rst(void)
{
    fsmInit();
    mainFsmStates_t event;
    bool newEvent;
    fsmCmd(LS);
    fsmCmd(LD);
    fsmCmd(CFG);
    fsmCmd(RUN);
    fsmCmd(GR);
    fsmCmd(RST);
    event = getEvent();
    newEvent = getNewEvent();
    TEST_ASSERT_EQUAL(EVENT_NONE, event);
    TEST_ASSERT_EQUAL(false, newEvent);
}

#endif // TEST
