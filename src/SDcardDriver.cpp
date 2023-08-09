#include "SDCardDriver.h"

ERROR_CODE SDcard_init(uint8_t _pinSCK,
					   uint8_t _pinMISO,
					   uint8_t _pinMOSI,
					   uint8_t _pinCS,
					   struct connectionStatus *_connectionStatus)
{
#ifdef USING_SDCARD

	SPI.begin(_pinSCK, _pinMISO, _pinMOSI, _pinCS);
	pinMode(SS, OUTPUT);

	if (SD.begin(_pinCS))
	{
		_connectionStatus->sdCardStatus = status_et::CONNECTED;
		log_e("SD init success.");
		return ERROR_NONE;
	}
	else
	{
		_connectionStatus->sdCardStatus = status_et::DISCONNECTED;
		log_e("SD init false.");
		return ERROR_SD_CARD_INIT_FAILED;
	}
#elif
	return ERROR_NONE;
#endif
}

ERROR_CODE SDcard_saveStringDataToFile(struct connectionStatus *_connectStatus,
									   const char *fileContent_string)
{
	if (_connectStatus->sdCardStatus == status_et::CONNECTED)
	{
		File writeFile;
		char locationFileSaveData[30] = "/";
		strcat(locationFileSaveData, nameFileSaveData);
		strcat(locationFileSaveData, ".txt");
		writeFile = SD.open(locationFileSaveData, FILE_APPEND); // mo file de ghi du lieu
		if (writeFile)											// kiem tra trang thai mo file co thanh cong
		{
			_connectStatus->sdCardStatus = status_et::WRITING_DATA;
			writeFile.println(fileContent_string); // ghi chuoi ki tu chua du lieu vao file
			writeFile.close();					   // dong file
			_connectStatus->sdCardStatus = status_et::CONNECTED;
			log_i("%s", fileContent_string);
			log_i("SD card write sensor data to file successfully!");
			return ERROR_NONE;
		}
		else
		{
			log_e("Can't open file to write!");
			log_e("SD card write sensor data to file failed!");
			return ERROR_SD_CARD_FILE_NOT_FOUND;
		}
	}
	else
	{
		log_e("SD card disconnected!");
		log_e("SD card write data failed!");
		return ERROR_SD_CARD_READ_FILE_FAILED;
	}
}