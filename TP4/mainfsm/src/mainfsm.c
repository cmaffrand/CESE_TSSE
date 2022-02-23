#include <stdbool.h>
#include "mainfsm.h"

mainFsmStates_t state;
event_t event;
bool newEvent;

void fsmInit(void)
{
    state = INIT;
    newEvent = false;
    event = EVENT_NONE;
    return;
}

mainFsmStates_t getState(void)
{
    return state;
}

event_t getEvent(void)
{
    return event;
}

bool getNewEvent(void)
{
    return newEvent;
}

void resetEvent(void)
{
    newEvent = false;
    event = EVENT_NONE;
    return;
}

void fsmCmd(mainFsmCmd_t cmd)
{
    switch (state)
    {
    case INIT:
        if (cmd == LD)
            state = WAITLS;
        else if (cmd == LS)
            state = WAITLD;
        break;
    case WAITLS:
        if (cmd == LS)
            state = UNCONFIG;
        break;
    case WAITLD:
        if (cmd == LD)
            state = UNCONFIG;
        break;
    case UNCONFIG:
        if (cmd == CFG)
        {
            state = ARMED;
            newEvent = true;
            event = EVENT_CFG;
        }
        break;
    case ARMED:
        if (cmd == RUN)
        {
            state = REPORT;
            newEvent = true;
            event = EVENT_RUN;
        }
        else if (cmd == CFG)
        {
            newEvent = true;
            event = EVENT_CFG;
        }
        break;
    case REPORT:
        if (cmd == CFG)
        {
            state = ARMED;
            newEvent = true;
            event = EVENT_CFG;
        }
        else if (cmd == GR)
        {
            state = END;
            newEvent = true;
            event = EVENT_GR;
        }
        else if (cmd == RUN)
        {
            newEvent = true;
            event = EVENT_RUN;
        }
        break;
    case END:
        if (cmd == CFG)
        {
            state = ARMED;
            newEvent = true;
            event = EVENT_CFG;
        }
        else if (cmd == RUN)
        {
            state = REPORT;
            newEvent = true;
            event = EVENT_RUN;
        }
        break;
    default:
        break;
    }

    if (cmd == RST)
    {
        state = INIT;
        resetEvent();
    }
    else if (cmd == LS)
    {
        newEvent = true;
        event = EVENT_LS;
    }
    else if (cmd == LD)
    {
        newEvent = true;
        event = EVENT_LD;
    }

    return;
}