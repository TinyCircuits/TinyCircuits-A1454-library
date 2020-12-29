# A1454 library

Used for the TinyCircuits Hall-Effect Sensor **[Analog Hall-Effect Sensor Wireling](https://tinycircuits.com/products/analog-digital-hall-sensor-wireling?variant=30110882431060)**. 

*Support this library by buying products from **[TinyCircuits](https://tinycircuits.com/)***


## A1454 Class

* **void begin(void)** Begin I2C Communications, access and wake sensor
* **int16_t readMag(void)** Read magnetometer value
* **int16_t readTemp(void)** Read temperature value
* **void sleep(void)** Put sensor into sleep mode
* **void wake(void)** Wake sensor up from sleep mode
* **uint8_t readMode(void)** Check for wake/sleep mode
* **void access(void)** Allow user to write to sensor registers