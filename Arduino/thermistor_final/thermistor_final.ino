#include <Adafruit_MCP3008.h>
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    
 
// What pin to connect the sensor to
#define THERMISTORPIN A0 
#define NUMsamples 5

//define pin connections
#define CS_PIN 10
#define CLOCK_PIN 13
#define MOSI_PIN 11
#define MISO_PIN 12
#define V 5.00 
Adafruit_MCP3008 mcp;

float average;
float temp_sense(float reading){
float resistance_array []= {164990.549,121695.1317,90891.59689,68688.18469,52486.24064,40526.10018,31600.36456,24870.159,19745.71925,15807.74524,12754.94602,10368.63165,8488.538203,6996.142144,5803.024431,4842.675746,4064.670748,3430.48915,2910.492292,2481.717676,2126.257506,1830.057568,1582.021067,1373.335323,1196.962561,1047.252319,919.6446241,810.4413221,716.6289247,635.7406016,565.7481078,504.9767184,452.0379452,405.7760658};
float temp_array[]= {233.15,238.15,  243.15,  248.15,  253.15,  258.15,  263.15,  268.15,  273.15,  278.15,  283.15,  288.15,  293.15,  298.15,  303.15,  308.15,  313.15,  318.15,  323.15,  328.15,  333.15,  338.15,  343.15,  348.15,  353.15,  358.15,  363.15,  368.15,  373.15,  378.15,  383.15,  388.15,  393.15,  398.15};
float temp_new = linear_interpolation(reading,resistance_array,temp_array);
return(temp_new);
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
void setup() 
{
 // open serial port
 Serial.begin(9600);
 mcp.begin(10);
}
//
//float voltage_read(float adc,float V_ref){
//  return ((adc*V_ref)/1024.0);
//}
void loop() 
{ int counter = 0;
average = 0.0;
  while(counter <=5){
  for(int i =0; i<8;i++){
    if(i==7){
          float val = mcp.readADC(i);
    Serial.print("ADC is reading channel # ");
    Serial.println(i+1);
    Serial.print("The Analog read value from the ADC is ");
    Serial.println(val);
      average+=val;
      counter++;
      Serial.println(counter);
    }
    
    }  
  }
  float av_val = 0.0;
  average/=5;
  av_val = (1024.0 / average)  - 1;     // (1023/ADC - 1) 
  av_val = SERIESRESISTOR / av_val;  // 10K / (1023/ADC - 1)
   Serial.print("Thermistor resistance "); 
   Serial.println(av_val);
   float temp = temp_sense(av_val);
   Serial.print("Temp is  = "); 
    Serial.println(temp);
    delay(10000); 
}
