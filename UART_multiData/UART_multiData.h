#ifndef UART_multiData_H
#define UART_multiData_H

#include "mbed.h"


class UART_multiData {

public:
  UART_multiData(PinName rx,PinName tx,uint size);

  void PutData();
}
