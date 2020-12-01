#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <SPI.h>

class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

MyParser::MyParser() {}

void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // If error, return
  // I don't know why it starts on 2, I just following the example
  //if (buf[2] == 1) return;

  // If empty, return
  // I check on 2 because the previous if check on 2 too
  //if (buf[2] == 0) return;

  // Like above, WHY it starts on 2 ?
  // What is the purpose of bit in 0 and 1 ?
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print(buf[i]);
    Serial.print(" ");
  }

  Serial.println();
}

USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser     Parser;

void setup() {
  Serial.begin( 115200 );
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  Hid.SetReportParser(0, &Parser);
}

void loop() {
  Usb.Task();
}
