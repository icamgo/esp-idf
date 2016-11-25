// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <esp_types.h>
#include "esp_intr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/xtensa_api.h"
#include "soc/dport_reg.h"
#include "driver/periph_ctrl.h"

static portMUX_TYPE periph_spinlock = portMUX_INITIALIZER_UNLOCKED;

void periph_module_enable(periph_module_t periph)
{
    portENTER_CRITICAL(&periph_spinlock);
    switch(periph) {
        case PERIPH_RMT_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_RMT_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_RMT_RST);
            break;
        case PERIPH_LEDC_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_LEDC_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_LEDC_RST);
            break;
        case PERIPH_UART0_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UART_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UART_RST);
            break;
        case PERIPH_UART1_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UART1_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UART1_RST);
            break;
        case PERIPH_UART2_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UART2_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UART2_RST);
            break;
        case PERIPH_I2C0_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2C_EXT0_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2C_EXT0_RST);
            break;
        case PERIPH_I2C1_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2C_EXT1_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2C_EXT1_RST);
            break;
        case PERIPH_I2S0_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2S0_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2S0_RST);
            break;
        case PERIPH_I2S1_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2S1_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2S1_RST);
            break;
        case PERIPH_TIMG0_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_TIMERGROUP_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_TIMERGROUP_RST);
            break;
        case PERIPH_TIMG1_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_TIMERGROUP1_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_TIMERGROUP1_RST);
            break;
        case PERIPH_PWM0_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM0_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM0_RST);
            break;
        case PERIPH_PWM1_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM1_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM1_RST);
            break;
        case PERIPH_PWM2_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM2_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM2_RST);
            break;
        case PERIPH_PWM3_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM3_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM3_RST);
            break;
        case PERIPH_UHCI0_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UHCI0_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UHCI0_RST);
            break;
        case PERIPH_UHCI1_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UHCI1_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UHCI1_RST);
            break;
        case PERIPH_PCNT_MODULE:
            SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PCNT_CLK_EN);
            CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PCNT_RST);
            break;
        default:
            break;
    }
    portEXIT_CRITICAL(&periph_spinlock);
}

void periph_module_disable(periph_module_t periph)
{
    portENTER_CRITICAL(&periph_spinlock);
    switch(periph) {
        case PERIPH_RMT_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_RMT_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_RMT_RST);
            break;
        case PERIPH_LEDC_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_LEDC_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_LEDC_RST);
            break;
        case PERIPH_UART0_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UART_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UART_RST);
            break;
        case PERIPH_UART1_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UART1_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UART1_RST);
            break;
        case PERIPH_UART2_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UART2_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UART2_RST);
            break;
        case PERIPH_I2C0_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2C_EXT0_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2C_EXT0_RST);
            break;
        case PERIPH_I2C1_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2C_EXT0_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2C_EXT1_RST);
            break;
        case PERIPH_I2S0_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2S0_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2S0_RST);
            break;
        case PERIPH_I2S1_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_I2S1_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_I2S1_RST);
            break;
        case PERIPH_TIMG0_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_TIMERGROUP_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_TIMERGROUP_RST);
            break;
        case PERIPH_TIMG1_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_TIMERGROUP1_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_TIMERGROUP1_RST);
            break;
        case PERIPH_PWM0_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM0_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM0_RST);
            break;
        case PERIPH_PWM1_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM1_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM1_RST);
            break;
        case PERIPH_PWM2_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM2_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM2_RST);
            break;
        case PERIPH_PWM3_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM3_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM3_RST);
            break;
        case PERIPH_UHCI0_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UHCI0_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UHCI0_RST);
            break;
        case PERIPH_UHCI1_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_UHCI1_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_UHCI1_RST);
            break;
        case PERIPH_PCNT_MODULE:
            CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PCNT_CLK_EN);
            SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PCNT_RST);
            break;
        default:
            break;
    }
    portEXIT_CRITICAL(&periph_spinlock);
}
