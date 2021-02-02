#include <Arduino.h>
uint8_t cyfra[10] = {0b0111111, 0b0000110,0b1001111,0b1100110,
0b1101101,0b0000111,0b1111111,0b1101111};
void dec_to_7seg(uint8_t);
void setup() {
  for (uint8_t i= 0; i < 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  for(uint8_t i = 8; i < 12; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  digitalWrite(8, HIGH);
  }
  void loop() {
    for (int i =0; i < 10; i++) {
    dec_to_7seg(i);
    delay(1000);
  }
}

void dec_to_7seg(uint8_t dec) {
  for (uint8_t i=0; i < 8; i++) {
    if (cyfra[dec] & (1 << i))
      digitalWrite(i, LOW);
    else
    digitalWrite(i, HIGH);
  }
  }