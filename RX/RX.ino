#define HC12 Serial1

unsigned long time_counter;
unsigned long cnt = 0;

void setup() {
  HC12.begin(9600); // establish UART with HC12 receiver
  pinMode(13, OUTPUT);
  Serial.begin(115200);

  Serial.println("BOOT COMPLETE!");
}

void loop() {
  unsigned long packet;
  if (HC12.available() > 0) {
    digitalWrite(13, HIGH);
    HC12.readBytes((uint8_t *)&packet, sizeof(packet));
    Serial.print("Data: ");
    Serial.println(packet);
    delay(50);
    digitalWrite(13, LOW);
  }
}