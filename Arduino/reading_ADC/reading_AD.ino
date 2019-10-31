#include <LT_I2C.h>

#include<Wire.h>
#include <util/delay.h>
#define Adr 0x45
//#define Adr 0x14 //LOW LOW LOW 
#define LTC24XX_MULTI_CH_CH0            0xB0
#define LTC24XX_MULTI_CH_CH1            0xB8
#define LTC24XX_MULTI_CH_CH2            0xB1
#define LTC24XX_MULTI_CH_CH3            0xB9
#define LTC24XX_MULTI_CH_CH4            0xB2
#define LTC24XX_MULTI_CH_CH5            0xBA
#define LTC24XX_MULTI_CH_CH6            0xB3
#define LTC24XX_MULTI_CH_CH7            0xBB
#define LTC24XX_MULTI_CH_CH8            0xB4
#define LTC24XX_MULTI_CH_CH9            0xBC
#define LTC24XX_MULTI_CH_CH10           0xB5
#define LTC24XX_MULTI_CH_CH11           0xBD
#define LTC24XX_MULTI_CH_CH12           0xB6
#define LTC24XX_MULTI_CH_CH13           0xBE
#define LTC24XX_MULTI_CH_CH14           0xB7
#define LTC24XX_MULTI_CH_CH15           0xBF

union LT_union_int32_4bytes
{
  int32_t LT_int32;       //!< 32-bit signed integer to be converted to four bytes
  uint32_t LT_uint32;     //!< 32-bit unsigned integer to be converted to four bytes
  uint8_t LT_byte[4];     //!< 4 bytes (unsigned 8-bit integers) to be converted to a 32-bit signed or unsigned integer
};

const uint8_t CHANNELS_SE[16] = {LTC24XX_MULTI_CH_CH0, LTC24XX_MULTI_CH_CH1, LTC24XX_MULTI_CH_CH2, LTC24XX_MULTI_CH_CH3,
    LTC24XX_MULTI_CH_CH4, LTC24XX_MULTI_CH_CH5, LTC24XX_MULTI_CH_CH6, LTC24XX_MULTI_CH_CH7,
    LTC24XX_MULTI_CH_CH8, LTC24XX_MULTI_CH_CH9, LTC24XX_MULTI_CH_CH10, LTC24XX_MULTI_CH_CH11,
    LTC24XX_MULTI_CH_CH12, LTC24XX_MULTI_CH_CH13, LTC24XX_MULTI_CH_CH14, LTC24XX_MULTI_CH_CH15};

uint8_t adc_command = LTC24XX_MULTI_CH_CH0;
uint32_t c;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Serial.println(adc_command);
  
}
float code_to_voltage(int32_t adc_code, float vref)
{
  float voltage;

//#ifndef SKIP_EZDRIVE_2X_ZERO_CHECK
//  if (adc_code == 0x00000000)
//  {
//    adc_code = 0x20000000;
//  }
//#endif

//  adc_code -= 0x20000000;             //! 1) Converts offset binary to binary
  voltage=(float) adc_code;
  voltage = voltage / 65535.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
  voltage = voltage * vref;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
  return(voltage);
}

void read_ADC_voltage(uint8_t adc_ch){
  int32_t x;
  Wire.beginTransmission(Adr); // transmit to device 0x32
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(adc_ch);      // sets register pointer to the command register (0x00)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();
  delay(400);                   // datasheet suggests at least 200 milliseconds
  
  Wire.requestFrom(Adr,3);
  if (2 <= Wire.available()) {
    x = Wire.read();  // receive high byte (overwrites previous reading)
    x = x << 8;    // shift high byte to be high 8 bits
    x |= Wire.read(); // receive low byte as lower 8 bits
    Serial.println(code_to_voltage(x,5.0));   // print the reading
   }
   else {
    Serial.println(1);   // error message
    c = Wire.available();
    Serial.println(c);
   }
//   delay(1000);
}
void loop(){
  for(int i=0; i<15;i++){
    read_ADC_voltage(CHANNELS_SE[i]);
//    delay(100);
    }
//  uint32_t x;
//  Wire.beginTransmission(Adr); // transmit to device 0x32
//  // the address specified in the datasheet is 224 (0xE0)
//  // but i2c adressing uses the high 7 bits so it's 112
//  Wire.write(adc_command);      // sets register pointer to the command register (0x00)
//  // use 0x51 for centimeters
//  // use 0x52 for ping microseconds
//  Wire.endTransmission();
//    delay(400);                   // datasheet suggests at least 200 milliseconds
//
//  Wire.requestFrom(Adr,3);
//  if (2 <= Wire.available()) { // if two bytes were received
//    x = Wire.read();  // receive high byte (overwrites previous reading)
//    x = x << 8;    // shift high byte to be high 8 bits
//    x |= Wire.read(); // receive low byte as lower 8 bits
//    Serial.println(code_to_voltage(x,5.0));   // print the reading
//  }
//  else {
//    Serial.println("did not recieve 2 bytes from ADC");   // error message
//    c = Wire.available();
//    Serial.println(c);
//  }
//  delay(1000);
       
}
