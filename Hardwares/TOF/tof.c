//
// Created by yekai on 2021/7/27.
//

#include "tof.h"
#include "main.h"
#include "usart.h"

BW_TypeDef TF_Mini_S = {0};

uint8_t BW_UartByte;

void BW_Task() {
    uint8_t command[] = {0x5A, 0x04, 0x04, 0x62};
    HAL_UART_Transmit(&huart2, command, 4, 0xff);
    HAL_UART_Receive_IT(&huart2, &BW_UartByte, 1);
}

void BW_UartHandler() {
    static uint8_t state = 0;
    static uint8_t temp;
    switch (state) {
        case 0:
            if (BW_UartByte == 0x59) {
                state++;
            }
            break;
        case 1:
            if (BW_UartByte == 0x59) {
                state++;
            } else {
                state = 0;
            }
            break;
        case 2:
            temp = BW_UartByte;
            state++;
            break;
        case 3:
            TF_Mini_S.dist = (BW_UartByte << 8) + temp;
            state++;
            break;
        case 4:
            temp = BW_UartByte;
            state++;
            break;
        case 5:
            TF_Mini_S.strength = (BW_UartByte << 8) + temp;
            state++;
            break;
        case 6:
            temp = BW_UartByte;
            state++;
            break;
        case 7:
            TF_Mini_S.temperature = (BW_UartByte << 8) + temp;
            state = 0;
            return;
        default:
            state = 0;
            break;
    }
    HAL_UART_Receive_IT(&huart2, &BW_UartByte, 1);
}
