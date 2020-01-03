/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */
 
// Pin 2-8 is connected to the 7 segments of the display.
#define U_max 10.88

#define pinA 6
#define pinB 9
#define pinC 11
#define pinD 4
#define pinE 2
#define pinF 10
#define pinG 13
#define d 3

#define D1 5
#define D2 7
#define D3 8
#define D4 12

uint16_t analogInput = 0;
float value = 0;
float valueFiltered = 0;
char buff[] = {'1', '2', '.', '3', '4'};
byte digits[] = {D1, D2, D3, D4};

float errmeasure = 6; // разброс измерения
float errestimate = 6;  // разброс оценки
float q = 0.9;  // скорость изменения значений
float currentestimate = 0.0;
float lastestimate = 0.0;
float kalmangain = 0.0;

// the setup routine runs once when you press reset:
void setup() {
  
  Serial.begin(9600);
  Serial.println("Enter float value");                
  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   

  for (byte i = 0; i < 4; i++){
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
    }
}

void off(){
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);  
  digitalWrite(d, LOW); 
  
  }

void zero(){
    //0
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);  
}

void one(){
  //1
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);  
}

void two(){
  //2
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);  
}

void three(){
  //3
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);  
}

void four(){
  //4
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);  
}

void five(){
  //5
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);  
}

void six(){
  //6
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);  
}

void seven(){
  //7
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);  
}

void eight(){
  //8
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);  
}

void nine(){
  //9
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);   
  }

// функция фильтрации
float filter(float value) {
  kalmangain = errestimate / (errestimate + errmeasure);
  currentestimate = lastestimate + kalmangain * (value - lastestimate);
  errestimate =  (1.0 - kalmangain) * errestimate + fabs(lastestimate - currentestimate) * q;
  lastestimate = currentestimate;
  return currentestimate;
}

float filter2(int value){
  
}

void display_(){
  
  //Serial.println("displaying...");
  char sign = 'c';
  byte currentDigit = 3;  
  
  // points to buffer
  for (int8_t i = 4; i >= 0; i--){
    //Serial.print("i = ");
    //Serial.println(i);
    sign = buff[i]; 

    for (byte j = 0; j < 4; j++){
      digitalWrite(digits[j], HIGH);
    }
    
    if (sign == '.'){
      digitalWrite(d, HIGH);
      //Serial.println("dot");
      //delay(3000);
      continue;
    }    

    switch(sign){
      case '0':
        zero();
        break;
      case '1':
        one();
        break;
      case '2':
        two();
        break;
      case '3':
        three();
        break;
      case '4':
        four();
        break;
      case '5':
        five();
        break;
      case '6':
        six();
        break;
      case '7':
        seven();
        break;
      case '8':
        eight();
        break;
      case '9':
        nine();
        break;
        /*
      case '.':
        digitalWrite(d, HIGH);
        currentDigit++;
        break;*/
      }
      
      digitalWrite(digits[currentDigit], LOW);
      
      delay(2);
      
      off();
      currentDigit--;
  }
  //Serial.println("end of func");
}

void test1() {
  digitalWrite(D1, LOW);
  one();
  delay(500);
  off();
  delay(500);
}

void AskSerial(){
    if (Serial.available()){
    value = Serial.parseFloat();
    dtostrf(value, 4, 2, buff);

    for (int i = 0; i < 4; i++){
          Serial.print(buff[i]);
          Serial.print(" ");
      }
      Serial.println();
    }
}

void dotCheck(){
  
  for (byte i = 0; i < 4; i++){
  pinMode(digits[i], OUTPUT);
  digitalWrite(digits[i], LOW);
  }
    
  digitalWrite(d, HIGH);  
  delay(500);
  digitalWrite(d, LOW);  
  delay(500);
}

void loop() {
  
  analogInput = analogRead(A0);
  Serial.print(analogInput);
  Serial.print(" = ");
  
  value = analogInput * U_max / 1024;
  valueFiltered = filter(value);
  Serial.println(value);
  Serial.println(valueFiltered);
  
  dtostrf(valueFiltered, 4, 2, buff);
  display_();
}
