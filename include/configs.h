#ifndef CONFIGS_H
#define CONFIGS_H
#include "WiFi.h"

#define SERIAL_DEBUG_BAUDRATE (9600)
#define DEVICE_DATA_SAVE_INTERVAL_TIME (2000UL)
#define DEVICE_PRE_GET_DATE_TIME (10000UL)
#define ERROR_CODE int
#define ERROR_NONE (0x00)

enum status_et
{
    DISCONNECTED,
    CONNECTED,
    CONNECTION_LOST,
    SCANNING,
    SENDING_DATA,
    READING_DATA,
    WRITING_DATA
};

struct connectionStatus
{
    status_et wifiStatus;
    status_et mqttConnection;
    status_et ds3231Module;
    status_et sdCardStatus;
};

//========================== DEFINE FOR WIFI ========================

#define USING_WIFI_CONFIG
#define WIFI_CONNECT_INTERVAL 30000
#define WIFI_MAX_CONNECT_TRIAL 50
const char ssid[] = "ActiveLearn";
const char pass[] = "DeepLearning";

//========================== DEFINE FOR LOGGING ========================

#define USING_MQTT
#define USING_RTC
#define USING_SDCARD

#define PIN_SDA_GPIO 26
#define PIN_SCL_GPIO 27
#define I2C_CLOCK_SPEED 100000U
#define RTC_I2C_ADDRESS (0x68)

//========================== DEFINE SPI  ========================

#define PIN_NUM_MISO (21)
#define PIN_NUM_MOSI (19)
#define PIN_NUM_CLK (18)
#define PIN_CS_SD_CARD (5)

//======================= DEFINE UART PZEM  =====================

#define RX_PIN 4
#define TX_PIN 2

#endif