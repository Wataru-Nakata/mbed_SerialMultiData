#include "UART_multiData.h"
#include "mbed.h"

union float2bytes
{
  float f;
  char b[sizeof(float)];
};

UART_multiData::UART_multiData(PinName rx,PinName tx,uint c_Num,uint f_Num): _serial(rx,tx)
{
  _cNum = c_Num;
  _fNum = f_Num;
}

UART_multiData::SetCaddr(char cdata[])
{
  _cdata =cdata;
}

UART_multiData::SetFaddr(float fdata[])
{
  _fdata = fdata;
}

UART_multiData::PutData()
{
  if ((_cdata == NULL) || (_fdata == NULL)) {
    return 1;
  }
  float2bytes putf[_fNum];
  for (int i = 0; i < f_Num; i++) {
    putf[i].f = _fdata[i]
  }
  _serial.write(HEADER);
  for (int i = 0; i < _cNum; i++) {
    _serial.write(_cdata[i])
  }
  for (int i = 0; i < f_Num; i++) {
    for (int j= 0; j < sizeof(float); j++) {
      _serial.write(putf[i].b[j])
    }
  }
  return 0;
}

UART_multiData::GetData()
{
  if ((_cdata == NULL) || (_fdata == NULL)) {
    return 1;
  }
  float2bytes getf[_fNum];
  for (int i = 0; i < f_Num; i++) {
    getf[i].f = *_fdata[i]
  }
  if ((_serial.getc() == HEADER) && _serial.readable()) {
    for (int i = 0; i < _cNum; i++) {
      _cdata[i] = _serial.getc()
    }
    for (int i = 0; i < _fNum; i++) {
      for (int j = 0; j < sizeof(float); j++) {
        getf[i].b[j] = _serial.getc()
      }
    }
    for (int i = 0; i < f_Num; i++) {
      _fdata[i] = getf[i].f;
    }
    return 0;
  }else{
    return 1;
  }
}
