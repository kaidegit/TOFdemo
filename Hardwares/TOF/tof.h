//
// Created by yekai on 2021/7/27.
//

#ifndef TESTTOF_TOF_H
#define TESTTOF_TOF_H

#include "stdint.h"

typedef struct {
    uint16_t dist;
    uint16_t strength;
    uint16_t temperature;
} BW_TypeDef;

void BW_Task();

void BW_UartHandler();

extern BW_TypeDef TF_Mini_S;

#endif //TESTTOF_TOF_H
