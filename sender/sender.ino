#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("CAN Sender");

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  int r = analogRead(A0);
  char rpm[8];
    snprintf(rpm, sizeof(rpm), "rpm=%d", r);
  Serial.print("Sending packet ... ");
  CAN.beginPacket(0x12);
  for(int i=0;rpm[i]!='\0';i++)
  {
   CAN.write(rpm[i]); 
  }
  
  CAN.endPacket();

  Serial.println("done");

  delay(1000);

}
