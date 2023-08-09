#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <Arduino.h>
#include <string>
#include "esp_log.h"
#include "configs.h"
#include "globals.h"
#include <ArduinoJson.h>
#include <NTPClient.h>

#define ERROR_DATA_CREATE_STRINGDATA_FAILED 0x91
struct sensorData
{
    float temperature;
    float humidity;
    float pressure_u32;
    uint32_t pm1_u32;
    uint32_t pm25_u32;
    uint32_t pm10_u32;
    uint32_t co_2_u32;
    double voltage;
    double current;
    double power;
    double energy;
    double freq;
    double pf;

    sensorData()
    {
        this->temperature = 0;
        this->humidity = 0;
        this->pressure_u32 = 0;
        this->pm1_u32 = 0;
        this->pm25_u32 = 0;
        this->pm10_u32 = 0;
        this->co_2_u32 = 0;
        this->voltage = 0;
        this->current = 0;
        this->power = 0;
        this->energy = 0;
        this->freq = 0;
        this->pf = 0;
    };
    sensorData operator=(const sensorData _sensorData_temp)
    {
        this->temperature = _sensorData_temp.temperature;
        this->humidity = _sensorData_temp.humidity;
        this->pressure_u32 = _sensorData_temp.pressure_u32;
        this->pm1_u32 = _sensorData_temp.pm10_u32;
        this->pm25_u32 = _sensorData_temp.pm25_u32;
        this->pm10_u32 = _sensorData_temp.pm10_u32;
        this->co_2_u32 = _sensorData_temp.co_2_u32;
        this->voltage = _sensorData_temp.voltage;
        this->current = _sensorData_temp.current;
        this->power = _sensorData_temp.power;
        this->energy = _sensorData_temp.energy;
        this->freq = _sensorData_temp.freq;
        this->pf = _sensorData_temp.pf;

        return _sensorData_temp;
    }
};

/**
 * @brief Create a string
 *
 * @param[out] _dataString: pointer char*, use to store string
 * @param[in]  _sensorData: struct sensor Data
 * @return ERROR_CODE
 */
ERROR_CODE createSensorDataString(char *_sensorDataString,
                                  const char *_espID, uint32_t _timetamp, sensorData _sensorData_st);

/**
 * @brief Create a MQTT string
 *
 * @param[out] _dataString: pointer char*, use to store string
 * @param[in]  _sensorData: struct calibdata
 * @return ERROR_CODE
 */
ERROR_CODE createMessageMQTTString(String &messageMQTTString, const char *_espID, uint32_t _timestamp, sensorData _sensorData_st);

#endif