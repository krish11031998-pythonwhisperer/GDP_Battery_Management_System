#include <Adafruit_MCP3008.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x08
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
// 10 byte data buffer
int receiveBuffer[9];
uint8_t keepCounted = 0;
void setup() 
{
 // open serial port
 Serial.begin(9600);
 mcp.begin(10);
 Wire.begin(SLAVE_ADDRESS);
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);
 Serial.println("I2C Ready!");
}

// Read data in to buffer, offset in first element.
void receiveData(int byteCount){
  int counter = 0;
  while(Wire.available()) {
    receiveBuffer[counter] = Wire.read();
    //Serial.print("Got data: ");
    //Serial.println(receiveBuffer[counter]);
    counter ++;
  }
}

// Use the offset value to select a function
void sendData(){
  if (receiveBuffer[0] == 99) {
    writeData(keepCount());
  } else{
    Serial.println("No function for this address");
  }
}
 
 
// Write data
void writeData(char newData) {
  char data[] = {receiveBuffer[0], newData};
  int dataSize = sizeof(data);
  Wire.write(data, dataSize);
}
 
 
// Counter function
int keepCount() {
  keepCounted ++;
  if (keepCounted > 255) {
    keepCounted = 0;
    return 0;
  } else {
    return keepCounted;
  }
}
//Function used for sensing the temperature of the battery pack environment
float temp_sense(float reading){
float resistance_array [31]= {33620.60372143574, 25924.56241959352, 20174.57702398485, 15837.147664908136, 12535.32581266281, 10000.0, 8037.140686973137, 6505.531126156567, 5301.466859409668, 4348.136850059472, 3588.182581929083, 2978.4358964646267, 2486.164751473382, 2086.372143385967, 1759.8370085233807, 1491.682246331595, 1270.3202348436205, 1086.6707693930255, 933.5770577947557, 805.3667325785383, 697.5197729861881, 606.4157634819621, 529.1404012869156, 463.33652255524424, 407.0887766466278, 358.8338772400338, 317.2904020403304, 281.4036129965835, 250.3018770260832, 223.26209037708867, 199.68212461492274};
float temp [31]= {273.15, 278.15, 283.15, 288.15, 293.15, 298.15, 303.15, 308.15, 313.15, 318.15, 323.15, 328.15, 333.15, 338.15, 343.15, 348.15, 353.15, 358.15, 363.15, 368.15, 373.15, 378.15, 383.15, 388.15, 393.15, 398.15, 403.15, 408.15, 413.15, 418.15, 423.15};
float temp_new = linear_interpolation(reading,resistance_array,temp);
return(temp_new);
 }
//Function used for linear interpoloation of the temperature measurand
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

//Function used to convert the digital voltage measurement measurement into analog voltage measurement w.r.t. the refernce voltage
float voltage_read(float adc,float V_ref){
  return ((adc*V_ref)/1024.0);
}

void MCP_voltage_read(int x,int y = 8){
  for(int i =x; i<y;i++){
    float val = mcp.readADC(i);
    Serial.print("ADC is reading channel # ");
    Serial.println(i+1);
    Serial.print("The Analog read value from the ADC is ");
    Serial.print(val);
    Serial.print(" The voltage reading with respect to 5V (Vref) ");
    Serial.print(voltage_read(val,V));
    Serial.println("..............");
    delay(1000); 
   }
}

void Thermistor_read(){
  float reading;
  float average = 0.0;
  for(int i=0; i<NUMsamples;i++){
    reading = analogRead(THERMISTORPIN);
    delay(10);
    average+=reading;
   }
   average/= NUMsamples;
  
 
  Serial.print("Analog reading "); 
  Serial.println(average);
 
  // convert the value to resistance
  average = (1023 / average)  - 1;     // (1023/ADC - 1) 
  average = SERIESRESISTOR / average;  // 10K / (1023/ADC - 1)
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
  float temp = temp_sense(average);
  Serial.print("Temp is  = "); 
  Serial.println(temp);
  delay(1000);
}
void loop() 
{
  MCP_voltage_read(4,8);
  Thermistor_read();
  
   
}
