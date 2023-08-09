#include "DataStructure.h"

ERROR_CODE createSensorDataString(char *_sensorDataString,
                                  const char *_espID, uint32_t _timestamp, struct sensorData _sensorData_st)
{
    strcpy(_sensorDataString, "");
    sprintf(_sensorDataString, "%s,%d,%.1f,%.1f,%f,%u,%u,%u,%.1f,%.3f,%.1f,%.3f,%.1f,%.2f,",
                                _espID,
                                _timestamp,
                                _sensorData_st.temperature,
                                _sensorData_st.humidity,
                                _sensorData_st.pressure_u32,
                                _sensorData_st.pm1_u32,
                                _sensorData_st.pm25_u32,
                                _sensorData_st.pm10_u32,
                                _sensorData_st.co_2_u32,
                                _sensorData_st.voltage,
                                _sensorData_st.current,
                                _sensorData_st.power,
                                _sensorData_st.energy,
                                _sensorData_st.freq,
                                _sensorData_st.pf);

    if (_sensorDataString[0] == '\0')
    {
        log_e("Create string failed!");
        return ERROR_DATA_CREATE_STRINGDATA_FAILED;
    }
    else
    {

        log_e("%s", _sensorDataString);
        log_i("Create string complete!");
        return ERROR_NONE;
    }
}

ERROR_CODE createMessageMQTTString(String &messageMQTTString, const char *_espID, uint32_t _timestamp, struct sensorData _sensorData_st)
{

    StaticJsonDocument<200> doc;

    doc["station_id"] = _espID;
    doc["Time"] = _timestamp;

    doc["Air_Quality"]["Temperature"] = _sensorData_st.temperature;
    doc["Air_Quality"]["Humidity"] = _sensorData_st.humidity;
    doc["Air_Quality"]["Pressure"] = _sensorData_st.pressure_u32;
    doc["Air_Quality"]["PM1"] = _sensorData_st.pm1_u32;
    doc["Air_Quality"]["PM2p5"] = _sensorData_st.pm25_u32;
    doc["Air_Quality"]["PM10"] = _sensorData_st.pm10_u32;
    doc["Air_Quality"]["CO2_PPM"] = _sensorData_st.co_2_u32;

    doc["Meter"]["Voltage"] = _sensorData_st.voltage;
    doc["Meter"]["Current"] = _sensorData_st.current;
    doc["Meter"]["Power"] = _sensorData_st.power;
    doc["Meter"]["Energy"] = _sensorData_st.energy;
    doc["Meter"]["Frequency"] = _sensorData_st.freq;
    doc["Meter"]["Power_Factor"] = _sensorData_st.pf;

    String output;
    serializeJson(doc, output);
    messageMQTTString = output;
    log_i("%s", messageMQTTString);
    return ERROR_NONE;
}