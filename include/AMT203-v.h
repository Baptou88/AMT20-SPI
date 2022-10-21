#ifndef __AMT203V_H__ 
#define __AMT203V_H__ 

#include <Arduino.h>
#include <SPI.h>

// SPI commands used by the AMT20
#define nop 0x00            // no operation
#define rd_pos 0x10         // read position
#define set_zero_point 0x70 // set zero point


class AMT203V
{
private:
    int m_sck=-1;
    int m_miso=-1;
    int m_mosi=-1;
    int m_cs=-1;
    int m_timeoutLimit = 50;

    // We will use this function to handle transmitting SPI commands in order to keep our code clear and concise.
    // It will return the byte received from SPI.transfer()
    uint8_t SPIWrite(uint8_t sendByte);
public:
    AMT203V(int sck,int miso, int mosi, int cs);
    ~AMT203V();

    bool begin();
    void stop(void);
    bool reset(void);

    // send the rd_pos command to have the AMT20 begin obtaining the current position
    // @return -1 if error
    int16_t getPos(void);

    void setTimeoutLimit(int timeoutLimit);
};



#endif // __AMT203V_H__