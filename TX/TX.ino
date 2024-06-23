#define HC12 Serial1
#define TIME_OUT_MS 3000

unsigned long time_counter;
unsigned long cnt = 0;

void setup() {
  Serial.begin(115200); // establish UART with PC
  HC12.begin(9600); // establish UART with HC12 receiver
  time_counter = millis(); // initialize time counter
  pinMode(13, OUTPUT); // LED indicator

  delay(2000);
  Serial.println("Boot Completed!");
}

void loop() {
  unsigned long curr_time = millis();
  if (curr_time - time_counter >= 1000) {

    time_counter = millis();
    Serial.print("cnt: ");
    Serial.print(cnt);
    Serial.print("\tSent:");

    digitalWrite(13, HIGH);
    HC12.write((u_int8_t*)&curr_time, sizeof(curr_time)); // send curr time to RX
    

    Serial.println(curr_time);
    listen(curr_time, TIME_OUT_MS); // hear back from RX
    digitalWrite(13, LOW);

    cnt += 1;
  }

}

void listen(unsigned long msg, unsigned long timeout_ms) {
  Serial.println("\tWating for RX to respond back...");
  unsigned long listen_counter = millis();
  while( !HC12.available() && ((millis() - listen_counter) <= timeout_ms)) {
    // wait doing nothing until any respond from RX
    // Serial.println(millis() - listen_counter);
    // delay(10);
  }

  if(HC12.available() > 0) {
    unsigned long response_time;
    response_time = millis();
    unsigned long response;
    HC12.readBytes((u_int8_t*)&response, sizeof(response));
    Serial.print("\tRX's response: ");
    Serial.println(response);
    Serial.print("\tsame: ");
    Serial.println(response == msg);
    Serial.print("\tdelay (ms): ");
    Serial.println(response_time - msg);
    Serial.println("");


  } else {
    Serial.println("\tTime Out!");
    Serial.println("");
  }

  return;
}
