/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * ГАЛИЧИНА F405 12S v4 — 603700 (https://www.603700fpv.com.ua)
 *
 * Pin map taken from the vendor's Betaflight 4.5.1 target and cross-checked
 * against their INAV 8.0.0 target.h and ArduPilot 4.6.0 hwdef.dat.
 */

#pragma once

#define FC_TARGET_MCU     STM32F405

#define BOARD_NAME        GALYCHYNAF405
#define MANUFACTURER_ID   CUST

#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_BARO
#define USE_BARO_DPS310
#define USE_MAX7456
#define USE_SDCARD
#define USE_SDCARD_SPI

#define BEEPER_PIN           PC15
#define MOTOR1_PIN           PB6
#define MOTOR2_PIN           PB7
#define MOTOR3_PIN           PB0
#define MOTOR4_PIN           PB1
#define MOTOR5_PIN           PC8
#define MOTOR6_PIN           PC9
#define SERVO1_PIN           PB15
#define SERVO2_PIN           PB11
#define SERVO3_PIN           PB10
#define UART1_TX_PIN         PA9
#define UART2_TX_PIN         PA2
#define UART3_TX_PIN         PC10
#define UART4_TX_PIN         PA0
#define UART6_TX_PIN         PC6
#define UART1_RX_PIN         PA10
#define UART2_RX_PIN         PA3
#define UART3_RX_PIN         PC11
#define UART4_RX_PIN         PA1
#define UART5_RX_PIN         PD2
#define UART6_RX_PIN         PC7
#define I2C1_SCL_PIN         PB8
#define I2C1_SDA_PIN         PB9
#define LED0_PIN             PC13
#define SPI1_SCK_PIN         PA5
#define SPI2_SCK_PIN         PB13
#define SPI3_SCK_PIN         PB3
#define SPI1_SDI_PIN         PA6
#define SPI2_SDI_PIN         PC2
#define SPI3_SDI_PIN         PB4
#define SPI1_SDO_PIN         PA7
#define SPI2_SDO_PIN         PC3
#define SPI3_SDO_PIN         PB5
#define ADC_VBAT_PIN         PC0
#define ADC_CURR_PIN         PC1
#define ADC_RSSI_PIN         PC5
#define SDCARD_SPI_CS_PIN    PC14
#define PINIO1_PIN           PB14
#define PINIO2_PIN           PA8
#define MAX7456_SPI_CS_PIN   PB12
#define GYRO_1_EXTI_PIN      PC4
#define GYRO_1_CS_PIN        PA4

// UART5 TX (PC12) is not broken out on this board; RX5 carries the inverted
// SBus input and ESC telemetry.

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN, 1, 0) \
    TIMER_PIN_MAP( 1, MOTOR2_PIN, 1, 0) \
    TIMER_PIN_MAP( 2, MOTOR3_PIN, 2, 0) \
    TIMER_PIN_MAP( 3, MOTOR4_PIN, 2, 0) \
    TIMER_PIN_MAP( 4, MOTOR5_PIN, 2, 0) \
    TIMER_PIN_MAP( 5, MOTOR6_PIN, 2, 0) \
    TIMER_PIN_MAP( 6, SERVO1_PIN, 1, 0) \
    TIMER_PIN_MAP( 7, SERVO2_PIN, 1, 0) \
    TIMER_PIN_MAP( 8, SERVO3_PIN, 1, 0)

#define SPI2_TX_DMA_OPT      0
#define ADC1_DMA_OPT         0

#define MAG_I2C_INSTANCE     I2CDEV_1
#define BARO_I2C_INSTANCE    I2CDEV_1
#define DASHBOARD_I2C_INSTANCE I2CDEV_1

#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_SDCARD
#define DEFAULT_DSHOT_BURST          DSHOT_DMAR_ON
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE  263
#define DEFAULT_VOLTAGE_METER_SCALE  209

#define BEEPER_INVERTED
#define SDCARD_SPI_INSTANCE  SPI3
#define SYSTEM_HSE_MHZ       8
#define MAX7456_SPI_INSTANCE SPI2

// PINIO1 switches between the two camera inputs, PINIO2 enables the
// adjustable BEC2 rail. Both are active-low push-pull (0x80 | 0x01).
#define PINIO1_CONFIG        129
#define PINIO2_CONFIG        129
#define PINIO1_BOX           40
#define PINIO2_BOX           41

#define GYRO_1_SPI_INSTANCE  SPI1
#define GYRO_1_ALIGN         CW270_DEG

#define SERIALRX_UART        SERIAL_PORT_USART1
#define DEFAULT_RX_FEATURE   FEATURE_RX_SERIAL
#define VTX_SMARTAUDIO_UART  SERIAL_PORT_USART6
