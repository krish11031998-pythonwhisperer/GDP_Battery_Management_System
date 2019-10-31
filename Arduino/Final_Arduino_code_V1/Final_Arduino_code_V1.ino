#include <Adafruit_MCP3008.h>
#include<Wire.h>
#include <util/delay.h>
//definations for LTC_2497 ADC
#define Adr_FFF 0x45 //FLOAT FLOAT FLOAT, 
#define Adr_LFF 0x44 //LOW FLOAT FLOAT 
//#define Adr_FLF 0x36 //FLOAT LOW FLOAT 
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
uint8_t adr;
//definations for MCP3008 ADC for thermistors
#define SERIESRESISTOR 10000    
#define THERMISTORPIN A0
#define CurrentSensor_1 A1
#define NUMsamples 5
#define CS_PIN_1 1
#define CLOCK_PIN_1 2
#define MOSI_PIN_1 3
#define MISO_PIN_1 4
#define CS_PIN_2 5
#define CLOCK_PIN_2 6
#define MOSI_PIN_2 7
#define MISO_PIN_2 8
#define CS_PIN_3 9
#define CLOCK_PIN_3 10
#define MOSI_PIN_3 11
#define MISO_PIN_3 12
#define V 5.00 
Adafruit_MCP3008 mcp;

unsigned long StartTime;
unsigned long EndTime;

//CODE FOR LTC2497 ADC for VOLTAGE Measurement
const uint8_t CHANNELS_SE[16] = {LTC24XX_MULTI_CH_CH0, LTC24XX_MULTI_CH_CH1, LTC24XX_MULTI_CH_CH2, LTC24XX_MULTI_CH_CH3,
    LTC24XX_MULTI_CH_CH4, LTC24XX_MULTI_CH_CH5, LTC24XX_MULTI_CH_CH6, LTC24XX_MULTI_CH_CH7,
    LTC24XX_MULTI_CH_CH8, LTC24XX_MULTI_CH_CH9, LTC24XX_MULTI_CH_CH10, LTC24XX_MULTI_CH_CH11,
    LTC24XX_MULTI_CH_CH12, LTC24XX_MULTI_CH_CH13, LTC24XX_MULTI_CH_CH14, LTC24XX_MULTI_CH_CH15};
//const uint8_t ADC_CH[5] = {Adr_FFF,Adr_LFF,Adr_FLF};
uint8_t adc_command = LTC24XX_MULTI_CH_CH0;
uint32_t c;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //StartTime = millis();
}

float code_to_voltage(int32_t adc_code, float vref)
{
  float voltage;
  voltage=(float) adc_code;
  voltage = voltage / 65535.0;    //! 2) This calculates the input as a fraction of the reference voltage (dimensionless)
  voltage = voltage * vref;           //! 3) Multiply fraction by Vref to get the actual voltage at the input (in volts)
  return(voltage);
}

void voltage_meas (int x){
  if(x == 1){adr = Adr_FFF;Serial.println(adr);}
  else{adr = Adr_LFF; Serial.println(adr);}
//  else{adr = Adr_FLF; Serial.println(adr);}
  for(int i=0;i<16;i++){
    read_ADC_voltage(CHANNELS_SE[i]);
    delay(200);
    }
  }
void read_ADC_voltage(uint8_t adc_ch){
  int32_t x;
  Wire.beginTransmission(adr);
   // transmit to device 0x32
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
    Wire.write(adc_ch); 
  // sets register pointer to the command register (0x00)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();
  delay(200);                   // datasheet suggests at least 200 milliseconds
  Wire.requestFrom(adr,3);
  if (2 <= Wire.available()) {
    x = Wire.read();  // receive high byte (overwrites previous reading)
    x = x << 8;    // shift high byte to be high 8 bits
    x |= Wire.read(); // receive low byte as lower 8 bits
    Serial.println(code_to_voltage(x,5.0));
    // print the reading
   }
   else {
    Serial.println(1);   // error message
    c = Wire.available();
    Serial.println(c);
   }
//   delay(1000);
}
//CODE FOR THERMISTOR USING MCP3008 ADC

float average;

float temp_sense(float reading){
float resistance_array []= {164990.549,121695.1317,90891.59689,68688.18469,52486.24064,40526.10018,31600.36456,24870.159,19745.71925,15807.74524,12754.94602,10368.63165,8488.538203,6996.142144,5803.024431,4842.675746,4064.670748,3430.48915,2910.492292,2481.717676,2126.257506,1830.057568,1582.021067,1373.335323,1196.962561,1047.252319,919.6446241,810.4413221,716.6289247,635.7406016,565.7481078,504.9767184,452.0379452,405.7760658};
float temp_array[]= {233.15,238.15,  243.15,  248.15,  253.15,  258.15,  263.15,  268.15,  273.15,  278.15,  283.15,  288.15,  293.15,  298.15,  303.15,  308.15,  313.15,  318.15,  323.15,  328.15,  333.15,  338.15,  343.15,  348.15,  353.15,  358.15,  363.15,  368.15,  373.15,  378.15,  383.15,  388.15,  393.15,  398.15};
float temp_new = linear_interpolation(reading,resistance_array,temp_array);
return(temp_new);
 }

void mcp_setup(uint8_t sck,uint8_t mosi,uint8_t miso, uint8_t cs){
  mcp.begin(sck,mosi,miso,cs);
  }
float linear_interpolation(float x0, float res[], float temp[]){
  Serial.println("This function is being called");
  for(int i = 0; i<31;i++){
    if(x0 < res[i] && x0 > res[i+1]){
      float x1 = res[i];
      float x2 = res[i+1];
      float y1 = temp[i];
      float y2 = temp[i+1];
      float slope = (y2-y1)/(x2-x1);
      float y0 = y1+(x0-x1)*slope;
      return (y0-273.15);
    }
    else{
      continue;}
   }
}

float current_measurement(){
  int sensorValue = analogRead(CurrentSensor_1);
  float V_m = (sensorValue/1023.0)*5.0;
  float amp = ((sensorValue/1023.0)*400.0)-200.0;
//  Serial.print("Vol : ");
  Serial.println(V_m);
//  Serial.print("Amp : ");
  Serial.println(amp);
  delay(1000);
}
  
  }
float* measure_temp(){
  int counter = 0;
  float average[24];
  float temperature[24];
  int i =0;
  for(i=1;i<13; i+=4){
    uint8_t sck = i+1;
    uint8_t mosi = i+2;
    uint8_t miso = i+3;
    uint8_t cs = i;
    mcp_setup(sck,mosi,miso,cs);
    while(counter <=5){
    for(int i =0; i<6;i++){
      float val = mcp.readADC(i);
//    Serial.print("ADC is reading channel # ");
//    Serial.println(i+1);
//    Serial.print("The Analog read value from the ADC is ");
//    Serial.println(val);
      average[i]+=val;
     
//     Serial.println(counter);
    }
    counter++;
    }
    }  
    for(int j;j<sizeof(average)/sizeof(float);j++){
      float av_val;
      average[j] = average[j]/5.0;
      av_val = (1024.0/average[j])-1;
      av_val = SERIESRESISTOR/av_val;
      temperature[j] = temp_sense(av_val);
      }
      return(temperature);
  }
// MAIN LOOP FOR ARDUINO
void loop(){
  //voltage measurement
  delay(1000);
  voltage_meas(1);
  delay(300);
  voltage_meas(2);
  delay(300);
  //themristor code
  float *temp;
  temp = measure_temp();
  for(int j=0;j<24;j++){
   Serial.println(temp[j]);
   delay(100);
  }
  //current measurement
  current_measurement() //When the bike is running at 25A discharge current setting
//  //current_measurement(2) //When the bike is running at 30A discharge current settting
//     EndTime = millis();
//     time_elapsed = EndTime - StartTime;
//     Serial.println(time_elapsed);
}
