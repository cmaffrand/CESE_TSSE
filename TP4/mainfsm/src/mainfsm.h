#ifndef MAINFSM_H
#define MAINFSM_H

typedef enum
{
    INIT,
    WAITLS,
    WAITLD,
    UNCONFIG,
    ARMED,
    REPORT,
    END
} mainFsmStates_t;

typedef enum
{
    LD,
    LS,
    CFG,
    RUN,
    GR,
    RST
} mainFsmCmd_t;

typedef enum
{
    EVENT_NONE,
    EVENT_LD,
    EVENT_LS,
    EVENT_CFG,
    EVENT_RUN,
    EVENT_GR,
    EVENT_RST
} event_t;

void fsmInit(void);
mainFsmStates_t getState(void);
void fsmCmd(mainFsmCmd_t cmd);
event_t getEvent(void);
bool getNewEvent(void);
void resetEvent(void);

#endif // MAINFSM_H
