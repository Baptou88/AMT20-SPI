class for interact with AMT20 Devices from Cuidevices with SPI

[>AMT 20 datasheet](https://www.cuidevices.com/product/resource/amt20.pdf)

ROTARY ENCODER ABS 4096PPR/12BIT

| |Arduino Uno Pin Connections    | AMT20 Pin Connections
|-------------------|---------|----------
|* SPI Clock (SCK): |Pin 13   |Pin 5
|* SPI MOSI:        |Pin 11   |Pin 7
|* SPI MISO:        |Pin 12   |PIN 3
|* SPI Chip Select: |Pin 10   |Pin 2
|* Vdd (5V):        |Pin 6
|* GND:             |Pin 4


Work with:
-Arduino Uno
-Heltec wifi lora v2 (take care to not take the default cs pins (18)-> reserved for LoRa)