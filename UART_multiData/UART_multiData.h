#ifndef UART_multiData_H
#define UART_multiData_H

#include "mbed.h"


class UART_multiData {

public:
  UART_multiData(PinName rx,PinName tx,uint c_Num,uint f_Num);
  void SetCaddr(char *cdata);

  void SetFaddr(float *fdata);

  void PutData();

  void GetData();
protected:
  Serial _serial;
  uint _cNum;
  uint _fNum;
  char *_cdata;
  float *_fdata;
}
