#ifndef _MAIN_H_
#define _MAIN_H_
/*------------------------------------ INCLUDE LIBRARY ------------------------------------ */
#include <Arduino.h>
#include <HardwareSerial.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ArduinoJson.h>
#include "configs.h"
#include "WiFi_Manager.h"
#include "MQTTConnection.h"
#include "Pzem004T.h"
#include "DS3231Driver.h"
#include "DataStructure.h"
#include "SDCardDriver.h"
#include "MHZ19BSensor.h"
#include "BMESensor.h"
#include "PMS7003Sensor.h"

/*------------------------------------ GLOBAL VARIABLE ------------------------------------ */
struct sensorData sensorData_st;
struct connectionStatus connectionStatus_st;
WiFiUDP ntpUDP;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 0, 0);
Pzem p;
const char *remote_host_string = "www.google.com";
RTC_DS3231 realTime;
char dateTime_string[25];
char sensorDataString[100];
char nameFileSaveData[12];
String messageData;
char espID[20];
char topic[32];

#endif