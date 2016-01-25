#include "UART_multiData.h"
#include "mbed.h"

union float2bytes
{
  float f;
  char b[sizeof(float)];
};

UART_multiData::UART_multiData(PinName rx,PinName tx,uint c_Num,uint f_Num): _serial(rx,tx)
{
  _cNum = cNum;
  _fNum = fNum;
}

UART_multiData::SetCaddr(char *cdata)
{
  _cdata =cdata;
}
UART_multiData::SetFaddr(float *fdata)
{
  _fdata = fdata;
}
