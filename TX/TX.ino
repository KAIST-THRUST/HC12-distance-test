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
  unsigned long curr_time = millis();
    if (curr_time - time_counter >= 500) {

      time_counter = millis();
      Serial.print("cnt: ");
      Serial.print(cnt);
      Serial.print("\tSent:");
      digitalWrite(13, HIGH);
      HC12.write((u_int8_t*)&cnt, sizeof(cnt)); // send curr time to RX
      Serial.println(cnt);
      digitalWrite(13, LOW);

      cnt += 1;
    }
}