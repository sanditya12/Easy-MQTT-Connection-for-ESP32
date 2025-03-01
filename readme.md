# xcamp.h Library

## Description
This header file aims to simplify and remove boilerplate when trying to make a MQTT connection on ESP32. It provides an easy way to initialize a connection, create widgets for data publishing, and handle data updates for MQTT connection from an ESP32 system.


---

## Quickstart Guide

### 1. Install Project
Copy the `xcamp.h` file into your Arduino/ESP32 project folder. Then, include it at the beginning of your main Arduino file:

```cpp
#include "xcamp.h"
```

### 2. Initialize the `Xcamp` Class
Initialize the `Xcamp` class with the MQTT broker parameters:

```cpp
char* SERVER = "your_mqtt_broker";
int PORT = 1883;
char* MAC_ADDRESS = "your_mac_address";
char* USERNAME = "your_username";
char* PASSWORD = "your_password";
char* EVENT_NAME = "your_event_name";

Xcamp xcamp(SERVER, PORT, MAC_ADDRESS, EVENT_NAME, USERNAME, PASSWORD);
```

### 3. Connect to WiFi and MQTT Broker
Call the `connectWiFi` and `connect` methods inside the `setup()` function:

```cpp
void setup() {
  Serial.begin(115200);
  
  char* SSID = "your_wifi_ssid";
  char* WIFI_PASS = "your_wifi_password";
  xcamp.connectWiFi(SSID, WIFI_PASS);
  
  char* EVENT_TOPIC = "your_event_topic";
  xcamp.addEventTopic(EVENT_TOPIC);
  xcamp.connect();
}
```

### 4. Create a Widget
To create a data object (widget), use one of the `newWidget` methods based on the data type:

```cpp
WidgetString* ambulanceNameWidget = xcamp.newWidgetString("ambulanceName");
WidgetDouble* bpmWidget = xcamp.newWidgetDouble("bpm");
WidgetDouble* spo2Widget = xcamp.newWidgetDouble("spo2");
```

### 5. Set Values in the Loop
Update the widget values dynamically inside the `loop()` function:

```cpp
void loop() {
  ambulanceNameWidget->setValue("Ambulance1");
  bpmWidget->setValue(random(100, 200));
  spo2Widget->setValue(random(70, 100));
  xcamp.loop();
}
```

### 6. Call the Loop Function
Ensure `xcamp.loop();` is called inside the `loop()` function to maintain the MQTT connection and send data continuously.

---

## Notes
- Ensure your device has internet access for MQTT communication.
- Adjust the WiFi credentials and MQTT parameters accordingly.

For more details, refer to the `xcamp.h` source code or the example file `example_main.ino`, or reach out via GitHub Issues.
