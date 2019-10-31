
void send_over_serial(float*arr,int x){
  for(int i=0;i<80;i++){
  Serial.println(float(arr[i]));
  delay(100);
  }
  Serial.println(0.0);
  delay(60000);
  
}
void setup(){
Serial.begin(9600);
}

void loop(){
  delay(5000);
  float batt [80];
  for(int i=0;i<80;i++){
    batt[i] = 1.25;  
  }
  
  send_over_serial(batt,80);
}


