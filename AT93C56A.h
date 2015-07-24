#ifndef MBED_AT93C56_H
#define MBED_AT93C56_H
 
#include "mbed.h"
 
#define EE_READ  0x400   // 10 XXXXXXXXX(A8-A0)
#define EE_WRITE 0x200   // 01 XXXXXXXXX(A8-A0)
#define EE_EWEN  0x1FF   // 00 11XXXXXXX(X is DONT CARE)
#define EE_EWDS  0x000   // 00 00XXXXXXX(X is DONT CARE)
#define EE_ERASE 0x600   // 11 XXXXXXXXX(A8-A0)

class AT93C56A {
    public:
    AT93C56A(PinName eecs,PinName eeck,PinName eedi,PinName eedo);
 
    void vSend(unsigned short usCommand);
    unsigned char ucRead(unsigned short usAddr);
    void vWriteEnable(void);
    void vWriteDisable(void);
    void vErase(unsigned short usAddr);
    void vWrite(unsigned short usAddr, unsigned char ucData);
    
    private:
    DigitalOut _eecs; //CS ,
    DigitalOut _eeck; //CLK,
    DigitalOut _eedi; //Data Input
    DigitalIn  _eedo; //Data Output
};
#endif
