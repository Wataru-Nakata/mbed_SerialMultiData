#include "UART_multiData.h"
#include "mbed.h"

union float2bytes
{
  float f;
  char b[sizeof(float)];
};

UART_multiData::UART_multiData(PinName rx,PinName tx,unsigned int c_Num,unsigned int f_Num): _serial_(rx,tx)
{
  _cNum = c_Num;
  _fNum = f_Num;
  _cdata = NULL;
  _fdata = NULL;
  HEADER = 255;
}
void UART_multiData::SetCaddr(char cdata[])
{
  _cdata =cdata;
}

void UART_multiData::SetFaddr(float fdata[])
{
  _fdata = fdata;
}

int UART_multiData::PutData()
{
  if ((_cdata == NULL) || (_fdata == NULL) ||(_serial_.writeable())) {
    return 1;
  }
  float2bytes putf[_fNum];
  for (unsigned int i = 0; i < _fNum; i++) {
    putf[i].f = _fdata[i];
  }
  _serial_.putc(HEADER);
  for (unsigned int i = 0; i < _cNum; i++) {
    _serial_.putc(_cdata[i]);
  }
  for (unsigned int i = 0; i < _fNum; i++) {
    for (unsigned int j= 0; j < sizeof(float); j++) {
      _serial_.putc(putf[i].b[j]);
    }
  }
  return 0;
}

int UART_multiData::GetData()
{
  if ((_cdata == NULL) || (_fdata == NULL)) {
    return 1;
  }
  float2bytes getf[_fNum];
  for (unsigned int i = 0; i < _fNum; i++) {
    getf[i].f = _fdata[i];
  }
  if ((_serial_.getc() == HEADER) && _serial_.readable()) {
    for (unsigned int i = 0; i < _cNum; i++) {
      _cdata[i] = _serial_.getc();
    }
    for (unsigned int i = 0; i < _fNum; i++) {
      for (unsigned int j = 0; j < sizeof(float); j++) {
        getf[i].b[j] = _serial_.getc();
      }
    }
    for (unsigned int i = 0; i < _fNum; i++) {
      _fdata[i] = getf[i].f;
    }
    return 0;
  }else{
    return 1;
  }
}

void UART_multiData::SetHeader(unsigned char header)
{
  HEADER = header;
}

void UART_multiData::SetBaudrate(unsigned int baud)
{
  _serial_.baud(baud);
}
