#include "xcamp.h"

char* SERVER = "devdeviceconnect.iot.xpand.asia";
int PORT = 1893;
char* MAC_ADDRESS = "7137871163971976";
char* USERNAME ="sandi-development-ampv1_6746";
char* PASSWORD = "1633059474_6746";
char* EVENT_NAME = "AmbulanceData";
char* EVENT_TOPIC = "sandi/development/ampv1/common";
 char* SSID = "";
 char* WIFI_PASS = "";

//initialize xcamp
Xcamp xcamp(SERVER,1893,MAC_ADDRESS, EVENT_NAME, USERNAME, PASSWORD);
//initialize display widget
WidgetString* ambulanceNameWidget = xcamp.newWidgetString("ambulanceName");
WidgetDouble* bpmWidget = xcamp.newWidgetDouble("bpm");
WidgetDouble* spo2Widget = xcamp.newWidgetDouble("spo2");
WidgetDouble* tempWidget = xcamp.newWidgetDouble("temp");
WidgetDouble* latWidget = xcamp.newWidgetDouble("lat");
WidgetDouble* longWidget = xcamp.newWidgetDouble("long");

void setup() {
  Serial.begin(115200);

  //connect to wifi
  xcamp.connectWiFi(SSID, WIFI_PASS);

  xcamp.addEventTopic(EVENT_TOPIC);
  //connect to dashboard
  xcamp.connect();
}

void loop() {
  ambulanceNameWidget->setValue("Ambulance1");
  bpmWidget->setValue(random(100,200));
  spo2Widget->setValue(random(70,100));
  tempWidget->setValue(random(350,400)/10.0);
  latWidget->setValue(random(38.8951, 100.5764));
  longWidget->setValue(random(38.8951, 100.5764));
  xcamp.loop();
}
