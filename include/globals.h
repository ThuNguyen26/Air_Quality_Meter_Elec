#ifndef GLOBALS_H
#define GLOBALS_H
/*------------------------------------ INCLUDE LIBRARY ------------------------------------ */
#include "string.h"
#include "esp_log.h"
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <RTClib.h>
#include "Pzem004T.h"

/*------------------------------------ GLOBAL VARIABLE ------------------------------------ */
extern struct connectionStatus connectionStatus_st;
extern char topic[32];
extern char espID[20];
extern WiFiUDP ntpUDP;
extern WiFiClient espClient;
extern PubSubClient mqttClient;
extern NTPClient timeClient;
extern Pzem p;
extern const char *remote_host_string;
extern RTC_DS3231 realTime;
extern char dateTime_string[25];
extern char sensorDataString[100];
extern char nameFileSaveData[12];
extern String messageData;

#endif