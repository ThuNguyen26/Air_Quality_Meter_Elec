/**
 * @file main.c
 * @author Nguyen Van Thu ( @ThuNguyen26 )
 * @brief Main file of Air Quality and Smart Electric
 * @version 0.1
 * @date 09-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

/*------------------------------------ INCLUDE LIBRARY ------------------------------------ */
#include "main.h"

/*--------------------------------------- FUNCTION ---------------------------------------- */
void device_getData()
{
  struct sensorData sensorDataTemp_st;
  if (pms_getdata(sensorDataTemp_st.pm1_u32, sensorDataTemp_st.pm25_u32, sensorDataTemp_st.pm10_u32) == ERROR_NONE)
  {
    sensorData_st.pm1_u32 = sensorDataTemp_st.pm1_u32;
    sensorData_st.pm25_u32 = sensorDataTemp_st.pm25_u32;
    sensorData_st.pm10_u32 = sensorDataTemp_st.pm10_u32;
  }
  if (bme_readData(sensorDataTemp_st.temperature, sensorDataTemp_st.humidity, sensorDataTemp_st.pressure_u32) == ERROR_NONE)
  {
    sensorData_st.temperature = sensorDataTemp_st.temperature;
    sensorData_st.humidity = sensorDataTemp_st.humidity;
    sensorData_st.pressure_u32 = sensorDataTemp_st.pressure_u32;
  }
  if (mhz_getdata(sensorDataTemp_st.co_2_u32) == ERROR_NONE)
  {
    sensorData_st.co_2_u32 = sensorDataTemp_st.co_2_u32;
  }
  if (updateValues(&p) == ERROR_NONE)
  {
    sensorData_st.voltage = p.voltage;
    sensorData_st.current = p.current;
    sensorData_st.power = p.power;
    sensorData_st.energy = p.energy;
    sensorData_st.freq = p.freq;
    sensorData_st.pf = p.pf;
  }
}
void device_dataManagement()
{
  struct sensorData sensorDataTemp_st;
  sensorDataTemp_st = sensorData_st;
  uint32_t timestamp = realTime.now().unixtime();
  createSensorDataString(sensorDataString, (const char *)espID, timestamp, sensorDataTemp_st);
  DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_DATE, nameFileSaveData);
  SDcard_saveStringDataToFile(&connectionStatus_st, sensorDataString);
  createMessageMQTTString(messageData, (const char *)espID, timestamp, sensorDataTemp_st);
  MQTT_postData(messageData.c_str(), &connectionStatus_st, mqttClient);
}

void setup()
{
  Serial.begin(SERIAL_DEBUG_BAUDRATE);
  log_e("Booting...");

  WIFI_init();
  MQTT_initClient(topic, espID, mqttClient, &connectionStatus_st);
  timeClient.begin();
  Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
  mhz_init();
  bme_initialize(Wire);
  pms_init();
  Pzem_Init(&p, &Serial1, RX_PIN, TX_PIN);
  DS3231_init(realTime, timeClient, Wire, connectionStatus_st);
  SDcard_init(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD, &connectionStatus_st);
  log_e("Init Done");
}
unsigned long device_previousDataControl = 0;
unsigned long device_previousWifiReconnect = 0;
unsigned long update_time = 0;
void loop()
{
  if (millis() - device_previousDataControl > DEVICE_DATA_SAVE_INTERVAL_TIME)
  {
    device_getData();
    device_dataManagement();
    device_previousDataControl = millis();
    if (millis() - update_time >= 300000)
    {
      uint32_t time_now = realTime.now().unixtime();
      uint32_t epochTime_u32 = timeClient.getEpochTime();
      if (time_now != epochTime_u32)
      {
        realTime.adjust(DateTime(epochTime_u32));
      }
      update_time = millis();
    }
  }
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (millis() - device_previousWifiReconnect >= WIFI_CONNECT_INTERVAL))
  {
    log_e("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    device_previousWifiReconnect = millis();
  }
}