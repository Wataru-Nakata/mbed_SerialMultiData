#include "mbed.h"
#include "UART_multiData.h"
DigitalOut myled(LED1);
UART_multiData serial(USBTX,USBRX,2,2);
int main() {
  char c[2] = {'A','B'};
  float f[2] = {0.001,0.002};
  serial.SetCaddr(c);
  serial.SetFaddr(f);
    while(1) {
      serial.PutData();
    }
}
