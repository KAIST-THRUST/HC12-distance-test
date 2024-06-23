#define HC12 Serial1

void setup() {
  HC12.begin(9600); // establish UART with HC12 receiver
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long packet;
  if (HC12.available() > 0) {
    HC12.readBytes((uint8_t*)&packet, sizeof(packet));
    Serial.println(packet);
    digitalWrite(13, HIGH);
    HC12.write((u_int8_t*)&packet, sizeof(packet)); // echo back to TX
    delay(10);
    digitalWrite(13, LOW);
  }
}