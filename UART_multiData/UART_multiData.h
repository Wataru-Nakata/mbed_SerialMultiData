#ifndef UART_multiData_H
#define UART_multiData_H
#include "mbed.h"


class UART_multiData {

public:
  UART_multiData(PinName rx,PinName tx,unsigned int c_Num,unsigned int f_Num);
  void SetCaddr(char cdata[]);

  void SetFaddr(float fdata[]);

  int PutData();

  int GetData();
private:
  Serial _serial_;
  unsigned int _cNum;
  unsigned int _fNum;
  char *_cdata;
  float *_fdata;
  char HEADER;
};
#endif
