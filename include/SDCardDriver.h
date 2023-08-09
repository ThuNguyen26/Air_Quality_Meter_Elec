#ifndef SDCARDDRIVER_H
#define SDCARDDRIVER_H

#include "esp_log.h"
#include <stdarg.h>
#include "globals.h"
#include "configs.h"
#include <SD.h>

#define ERROR_SD_CARD_INIT_FAILED (0x31)
#define ERROR_SD_CARD_READ_FILE_FAILED (0x32)
#define ERROR_SD_CARD_WRITE_FILE_FAILED (0x33)
#define ERROR_SD_CARD_FILE_NOT_FOUND (0x34)

/**
 * @brief Initialize SD Card
 *
 * @param[in] _pinSCK:  SCK pin
 * @param[in] _pinMISO: MISO pin
 * @param[in] _pinMOSI: MOSI pin
 * @param[in] _pinCS:   ChipSelect pin
 * @param[in] _connecctionStatus: pointer to struct status connection
 * @return ERROR_CODE
 */
ERROR_CODE SDcard_init(uint8_t _pinSCK,
					   uint8_t _pinMISO,
					   uint8_t _pinMOSI,
					   uint8_t _pinCS,
					   struct connectionStatus *_connectionStatus);

/**
 * @brief Save sensor data to SDcard
 *
 * @param[in] fileContent_string: string save to file
 * @param[in] _connecctionStatus: pointer to struct store all connection status
 * @return ERROR_CODE
 */
ERROR_CODE SDcard_saveStringDataToFile(struct connectionStatus *_connectStatus,
									   const char *fileContent_string);

#endif