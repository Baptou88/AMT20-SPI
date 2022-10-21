#include <AMT203-v.h>
#include <SPI.h>

AMT203V::AMT203V(int sck,int miso, int mosi, int cs)
{
    m_sck = sck;
    m_mosi = mosi;
    m_miso = miso;
    m_cs = cs;

}

AMT203V::~AMT203V()
{
}

bool AMT203V::begin()
{
    


    if (m_cs == -1 || m_mosi == -1 || m_miso == -1 || m_sck == -1)
    {
        return false;
    }
    
    pinMode(m_sck, OUTPUT);
    pinMode(m_mosi, OUTPUT);
    pinMode(m_miso, INPUT);
    pinMode(m_cs, OUTPUT);

    // Initialize SPI using the SPISettings(speedMaxium, dataOrder, dataAMode) function
    // For our settings we will use a clock rate of 500kHz, and the standard SPI settings
    // of MSB First and SPI Mode 0
    //SPI.beginTransaction(SPISettings(250000, MSBFIRST, SPI_MODE0));
    //SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
    //SPI.beginTransaction(SPISettings(1E6, MSBFIRST, SPI_MODE0));
    SPI.begin();
    // Using SPI.beginTransaction seems to require explicitly setting the beginning state
    // of the CS pin as opposed to the SPI.begin() function that does this for us.
    digitalWrite(m_cs, HIGH);
    return true;
}

void AMT203V::stop(void)
{
    SPI.endTransaction();
}

bool AMT203V::reset(void)
{
    stop();
    delayMicroseconds(100);
    return begin();
}

int16_t AMT203V::getPos(void)
{
    uint8_t data;               // this will hold our returned data from the AMT20
    uint8_t timeoutCounter=0;     // our timeout incrementer
    uint16_t currentPosition;   // this 16 bit variable will hold our 12-bit position
    data = SPIWrite(rd_pos);

    // we need to send nop commands while the encoder processes the current position. We
    // will keep sending them until the AMT20 echos the rd_pos command, or our timeout is reached.
    while (data != rd_pos && timeoutCounter++ < m_timeoutLimit) {
        data = SPIWrite(nop);
    }
    if (timeoutCounter < m_timeoutLimit) { // rd_pos echo received
        // We received the rd_pos echo which means the next two bytes are the current encoder position.
        // Since the AMT20 is a 12 bit encoder we will throw away the upper 4 bits by masking.

        // Obtain the upper position byte. Mask it since we only need it's lower 4 bits, and then
        // shift it left 8 bits to make room for the lower byte.
        Serial.println("after : " + (String) timeoutCounter);
        currentPosition = (SPIWrite(nop)& 0x0F) << 8;

        // OR the next byte with the current position
        currentPosition |= SPIWrite(nop);
        return currentPosition;
    } else {
        // timeout reached
        // This means we had a problem with the encoder, most likely a lost connection. For our
        // purposes we will alert the user via the serial connection, and then stay here forever.
        Serial.write("Error obtaining position.\n");
        Serial.write("Reset Arduino to restart program.\n");
        return -1;
    }
}

void AMT203V::setTimeoutLimit(int timeoutLimit)
{
    m_timeoutLimit = timeoutLimit;
}

uint8_t AMT203V::SPIWrite(uint8_t sendByte)
{
    // holder for the received over SPI
  uint8_t data;
  

  // the AMT20 requires the release of the CS line after each byte
  digitalWrite(m_cs, LOW);
  data = SPI.transfer(sendByte);
  digitalWrite(m_cs, HIGH);

  // we will delay here to prevent the AMT20 from having to prioritize SPI over obtaining our position
  delayMicroseconds(20);
  return data;
}
