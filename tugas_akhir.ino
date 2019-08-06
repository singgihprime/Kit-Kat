// Deklarasi variabel 
int pin_PIR1 = 8; 
int pin_PIR2 = 9; 
int pin_ULTRA = 7; 
int pin_LEDmerah = 4; 
int pin_LEDhijau = 2; 
int sensor_PIR_1 = LOW; 
int sensor_PIR_2 = LOW; 
int times = 0;

// Deklarasi pin
void setup() {
  Serial.begin(9600); 
  pinMode(pin_PIR1, INPUT); 
  pinMode(pin_PIR2, INPUT); 
  pinMode(pin_ULTRA, OUTPUT);
  pinMode(pin_LEDmerah, OUTPUT); 
  pinMode(pin_LEDhijau, OUTPUT);  
}

void loop() { 
// Program sistem deteksi dan sistem pengusir
  sensor_PIR_1 = digitalRead(pin_PIR1);
  sensor_PIR_2 = digitalRead(pin_PIR2);
  if (sensor_PIR_1 == LOW && sensor_PIR_2 == LOW) {
    digitalWrite(pin_LEDhijau, HIGH);
    digitalWrite(pin_LEDmerah, LOW);
    digitalWrite(pin_ULTRA, LOW);
    delay(500);
    if (times==0){
      Serial.println("No Motion Detected!");
      times=1;
    }
  }

  else if (sensor_PIR_1 == HIGH && sensor_PIR_2 == LOW) {
    digitalWrite(pin_LEDhijau, HIGH);
    digitalWrite(pin_LEDmerah, LOW);
    digitalWrite(pin_ULTRA, LOW);
    delay(500);
    if (times==0){
      Serial.println("No Motion Detected!");
      times=1;
    }
  }
  else if (sensor_PIR_1 == LOW && sensor_PIR_2 == HIGH) {
    digitalWrite(pin_LEDhijau, HIGH);
    digitalWrite(pin_LEDmerah, LOW);
    digitalWrite(pin_ULTRA, LOW);
    delay(500);
    if (times==0){
      Serial.println("No Motion Detected!");
      times=1;
    }
  }
  else if (sensor_PIR_1 == HIGH && sensor_PIR_2 == HIGH) {
    digitalWrite(pin_LEDmerah, LOW);
    digitalWrite(pin_ULTRA, LOW);
    delayMicroseconds(5);
    digitalWrite(pin_LEDhijau, LOW);
    digitalWrite(pin_LEDmerah, HIGH);
    digitalWrite(pin_ULTRA, HIGH);
    delayMicroseconds(10);
    if (times==1){
      Serial.println("Motion Detected!");
      times=0;
    }
  }
} 
