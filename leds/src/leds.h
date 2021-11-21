/*=============================================================================
 * Copyright (c) 2021, Carlos Maffrand <carlosmaffrand5@gmail.com>
 * All rights reserved.
 * License: Free
 * Date: 2021/11/22
 * Version: v1.0
 * Descripcion: libreria del TP3 de Testing de software en sistemas embebidos
 *===========================================================================*/

#include "inttypes.h"

void LedsCreate(uint16_t *puertoVirtual);
void LedsOn(uint8_t led);
void LedsOff(uint8_t led);
void allLedsOn(void);
void allLedsOff(void);
uint8_t LedsState(uint8_t led);