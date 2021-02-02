#include <Arduino.h>
uint8_t cyfra[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111,0b1100110,
0b1101101, 0b1111101, 0b0000111, 0b1111111,0b1101111};
uint8_t D3Val = 0, D2Val = 0, D1Val = 0, D0Val = 0; 
uint16_t licznik =0;
void set_digit(int8_t digitNo);
void dec_to_7seg(uint8_t dec);
 
void setup() {
  for (uint8_t i= 0; i < 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for(uint8_t i = 8; i < 12; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
 
  OCR1A = 125;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1<< CS12);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}
void loop () {
  licznik++;
  if (licznik >9999)
  licznik = 0;
  D3Val = (licznik / 1000);
  D2Val = (licznik - (D3Val * 1000)) / 100;
  D1Val = (licznik - (D3Val *1000) - (D2Val *100))/10;
  D0Val = (licznik - (D3Val *1000) - (D2Val * 100) - (D1Val *10));
 
  delay(10);
}
 
void dec_to_7seg(uint8_t dec) {
  for (uint8_t i =0; i < 8; i++) {
    if (cyfra[dec] & (1 << i))
    digitalWrite(i, LOW);
    else
    digitalWrite(i, HIGH);
 
  }
}
void set_digit(int8_t digitNo) {
  if (digitNo ==0){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
   if (digitNo ==1){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    }
     if (digitNo ==2){
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    }
      if (digitNo ==3){
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    }
     
}
 
ISR(TIMER1_COMPA_vect) {
  static int8_t led= 3;
  if (led ==3) {
    set_digit(3);
    dec_to_7seg(D3Val);
  }
  if (led ==2) {
    set_digit(2);
    dec_to_7seg(D2Val);
  }
  if (led ==1) {
    set_digit(1);
    dec_to_7seg(D1Val);
  }
  if (led ==0) {
    set_digit(0);
    dec_to_7seg(D0Val);
  }
  led--;
  if(led<0)
  led =3;
}