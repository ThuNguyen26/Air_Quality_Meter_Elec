#ifndef __PZEM__
#define __PZEM__
#include <stdint.h>
#include <HardwareSerial.h>
#include "configs.h"

#define PZEM_GET_DATA_FAIL 0xe5
struct Pzem
{
  double voltage;
  double current;
  double power;
  double energy;
  double freq;
  double pf;
  uint8_t _addr;
  uint64_t _lastRead;
  bool _isConnected;
  bool _isSoft;
  Stream *_serial;
  uint8_t* resp;
};
void Pzem_Init(Pzem *p, HardwareSerial *port, uint8_t rx_pin, uint8_t tx_pin, uint8_t addr = 0xF8);
uint16_t CRC16(const uint8_t *data, uint16_t len);
void setCRC(uint8_t *buf, uint16_t len);
bool checkCRC(const uint8_t *buf, uint16_t len);
uint16_t receive(Pzem *p, uint8_t *resp, uint16_t len);
bool sendCmd8(Pzem *p, uint8_t cmd, uint16_t rAddr, uint16_t val, bool check = false, uint16_t slave_addr = 0xFFFF);
ERROR_CODE updateValues(Pzem *p);
float getVoltage(Pzem *p);
float getCurrent(Pzem *p);
float getPower(Pzem *p);
float getEnergy(Pzem *p);
float getFrequency(Pzem *p);
float getPF(Pzem *p);
#endif