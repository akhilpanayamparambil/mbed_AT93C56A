#include "AT93C56A.h"
#include "mbed.h"

AT93C56A::AT93C56A(PinName eecs,PinName eeck,PinName eedi,PinName eedo): _eecs(eecs),_eeck(eeck),_eedi(eedi),_eedo(eedo){
    _eecs=0;  // Active High State
    _eeck=0;
};
 
void AT93C56A::vSend(unsigned short usCommand)
{
    signed char i=10;
    _eedi=1;        //SB
    _eecs=1;        // Chip Select High
    wait_us(1);  // SB Clock Generation
    _eeck=1;
    wait_us(1);
    _eeck=0;
    while(i>=0)
    {
        _eedi = (usCommand>>i)&0x01;
        i--;
        wait_us(1);
        _eeck=1;
        wait_us(1);
        _eeck=0;
    }
}
void AT93C56A::vWriteEnable()
{
    vSend(EE_EWEN);
    wait_us(1);
    _eecs=0;  //Chip Select Low
}
void AT93C56A::vWriteDisable()
{
    vSend(EE_EWDS);
    wait_us(1);
    _eecs=0;  //Chip Select Low
}
void AT93C56A::vErase(unsigned short usAddr)
{
    vSend(EE_ERASE|usAddr);
    wait_us(1);
    _eecs=0;
/** wait busy flag clear */
    wait_us(1);     // tcs > 250ns @2.7V
    _eecs=1;
    wait_us(1);     // tsv < 250ns @2.7V
    while(_eedo==0); // 0.1ms < twp < 10ms 
    _eecs=0;
}
void AT93C56A::vWrite(unsigned short usAddr, unsigned char ucData)
{
    signed char i=7;
    vSend(EE_WRITE|usAddr);
    for(i=7;i>=0;i--)
    {
        _eedi = (int)( (ucData>>i)&0x0001 );
        wait_us(1);
        _eeck=1;
        wait_us(1);
        _eeck=0;
    }
    _eecs=0;
/** wait busy flag clear */
    wait_us(1);     // tcs > 250ns @2.7V
    _eecs=1;
    wait_us(1);     // tsv < 250ns @2.7V
    while(_eedo==0); // 0.1ms < twp < 10ms 
    _eecs=0;
}
unsigned char AT93C56A::ucRead(unsigned short usAddr)
{
    unsigned char data=0;
    signed char i=7;
    
    vSend(EE_READ|usAddr);
    wait_us(1);
    
    for(i=7;i>=0;i--)
    {
        _eeck=1;
        wait_us(1);
        _eeck=0;
        data = data | (_eedo<<i);
        wait_us(1);
    }
    _eecs=0;
    
    return data;
}