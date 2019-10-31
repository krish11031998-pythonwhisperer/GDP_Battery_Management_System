#include <MCP3008.h>
#include<Wire.h>
#include <util/delay.h>
#define Adr_1 0x45 //LOW FLOAT FLOAT
#define Adr 0x44 //LOW FLOAT FLOAT
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
#define I1 A0
#define I2 A1
uint8_t adr;

//definations for MCP3008 ADC for thermistors
#define fanpin 3
#define SERIESRESISTOR 17800    
#define THERMISTORPIN A0 
#define NUMsamples 5
#define CS_PIN_1 10
#define CLOCK_PIN_1 13
#define MOSI_PIN_1 11
#define MISO_PIN_1 12
#define CS_PIN_2 9
//#define CLOCK_PIN_2 6
//#define MOSI_PIN_2 7
//#define MISO_PIN_2 8
//#define CS_PIN_3 9
//#define CLOCK_PIN_3 10
//#define MOSI_PIN_3 11
//#define MISO_PIN_3 12
#define V 5.00 
unsigned long starttime;
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
  pinMode(fanpin,OUTPUT);
  Wire.begin();
  starttime = millis();
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

void voltage_meas (int x,int y){
  if(x == 1){adr = Adr;Serial.println(adr);}
  else{adr = Adr_1; Serial.println(adr);}
  for(int i=0;i<y;i++){
    read_ADC_voltage(CHANNELS_SE[i]);
    delay(200);}
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
float resistance_array []= {194560.2838,143505.428,107181.2597,80998.53467,61892.86559,47789.21943,37263.80652,29327.40827,23284.56244,18640.82166,15040.89738,12226.90589,10009.86063,8249.996191,6843.046991,5710.583867,4793.144206,4045.304089,3432.112989,2926.493052,2507.327033,2158.041912,1865.552115,1619.465549,1411.483123,1234.941696,1084.46405,955.6892474,845.063719,749.6785276,667.1419246,595.4790394,533.052538,478.4995685};
float temp_array[]= {233.15,238.15,  243.15,  248.15,  253.15,  258.15,  263.15,  268.15,  273.15,  278.15,  283.15,  288.15,  293.15,  298.15,  303.15,  308.15,  313.15,  318.15,  323.15,  328.15,  333.15,  338.15,  343.15,  348.15,  353.15,  358.15,  363.15,  368.15,  373.15,  378.15,  383.15,  388.15,  393.15,  398.15};
float temp_new = linear_interpolation(reading,resistance_array,temp_array);
return(temp_new);
 }

float linear_interpolation(float x0, float res[], float temp[]){
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
void measure_temp(int index){
  int fan_counter = 0;
  if(index == 1){
    MCP3008 adc(CLOCK_PIN_1, MOSI_PIN_1, MISO_PIN_1, CS_PIN_1);
      int counter = 0;
  int sample_temp[8] = {0,0,0,0,0,0,0,0};
  while(counter < 5){
   for (int i=0; i<8; i++) {
   int val = adc.readADC(i);
   sample_temp[i]+=val;
//   Serial.println(sample_temp[i]);
   }
   counter++;
  }
  for(int j=0;j<8;j++){
  
    float avg,av_val,temp_av_val;
    avg = sample_temp[j]/5.0;
    av_val = (1024.0/avg)-1;
    av_val = SERIESRESISTOR/av_val;
//    Serial.print("Therm resistance : ");
//    Serial.println(av_val);
    temp_av_val = temp_sense(av_val);
//    Serial.print("Temp is : ");
//    Serial.println(temp_av_val);
      Serial.println(temp_av_val);
      if(temp_av_val > 23.0){
        fan_counter = 1;}
  }
    fan_turn_offon(fan_counter);
    delay(2000);
}
   else if(index == 2){
    MCP3008 adc(CLOCK_PIN_1, MOSI_PIN_1, MISO_PIN_1, CS_PIN_2);
      int counter = 0;
  int sample_temp[8] = {0,0,0,0,0,0,0,0};
  while(counter < 5){
   for (int i=0; i<8; i++) {
   int val = adc.readADC(i);
   sample_temp[i]+=val;
//   Serial.println(sample_temp[i]);
   }
   counter++;
  }
  for(int j=0;j<8;j++){
    float avg,av_val,temp_av_val;
    avg = sample_temp[j]/5.0;
    av_val = (1024.0/avg)-1;
    av_val = SERIESRESISTOR/av_val;
//    Serial.print("Therm resistance : ");
//    Serial.println(av_val);
    temp_av_val = temp_sense(av_val);
//    Serial.print("Temp is : ");
//    Serial.println(temp_av_val);
      Serial.println(temp_av_val);
     // if(temp_av_val > 23.0){
        fan_counter = 1;}
//      if(temp_av_val > 25.00){
//        delay(100);
//        fan_turn_offon(1);}
//      else{
//        delay(100);
//        fan_turn_offon(0);}
    // }
//     Serial.println("");
//    fan_turn_offon(fan_counter);
    delay(2000);
}
    }
 
void current_sensor(int count){
if(count == 1){
int x = analogRead(I1);
Serial.println(x);
float voltage = (x/1024.0)*5.0;
float I_cal = ((voltage-2.5)*200)/1.25;
Serial.println(I_cal);
}
if(count == 2){
int x = analogRead(I2);
Serial.println(x);
float voltage = (x/1024.0)*5.0;
float I_cal = ((voltage-2.5)*200)/1.25;
Serial.println(I_cal);
}
}
//Code for Fan
void fan_turn_offon(int turn){
  if(turn == 0){
    digitalWrite(fanpin,LOW);
    }
   else if(turn == 1){
    digitalWrite(fanpin,HIGH);
    }
    }
void loop(){
  for(int i=0; i<5;i++){
  delay(1000);
  voltage_meas(1,16);
  delay(300);
  voltage_meas(2,4);
  delay(300);
  measure_temp(1);
  delay(1000);
  measure_temp(2);
  delay(1000);
  current_sensor(1);
  delay(1000);
  current_sensor(2);
  delay(1000);
  unsigned long endtime = millis();
  Serial.println(endtime - starttime);
  }
  Serial.println(11031998);
  delay(1000);
}
