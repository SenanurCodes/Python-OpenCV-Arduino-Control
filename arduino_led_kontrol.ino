/*
  El Hareketleri ile LED Kontrol Sistemi - Arduino Taslağı
  Geliştirici: Senanur Bildirici

  Açıklama:
  Bu taslak, Python uygulamasından (Seri port üzerinden) gönderilen 
  parmak sayısını ('0' - '5' arası karakter) okur ve ilgili sayıda 
  LED'i sırayla yakar.

  Varsayılan Donanım Yapılandırması:
  - Baud Rate: 9600 bps
  - Dijital Çıkış Pinleri (LED 1 - LED 5): 
      LED 1 -> Dijital Pin 13
      LED 2 -> Dijital Pin 12
      LED 3 -> Dijital Pin 11
      LED 4 -> Dijital Pin 10
      LED 5 -> Dijital Pin 9
  - Devre Notu: Her LED'in anot bacağı ilgili Arduino pinine, 
    katot bacağı ise 220 Ohm / 330 Ohm direnç üzerinden GND pinine bağlanır.

  Alternatif (pyFirmata):
  Eğer Python tarafındaki pyFirmata protokolü doğrudan kullanılacaksa, 
  Arduino IDE içerisinden:
  Dosya -> Örnekler -> Firmata -> StandardFirmata 
  seçilerek karta yüklenebilir.
*/

const int ledPins[] = {13, 12, 11, 10, 9};
const int totalLeds = 5;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < totalLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    
    if (receivedChar >= '0' && receivedChar <= '5') {
      int fingerCount = receivedChar - '0';
      updateLeds(fingerCount);
    }
  }
}

void updateLeds(int count) {
  for (int i = 0; i < totalLeds; i++) {
    if (i < count) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
