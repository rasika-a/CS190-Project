#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>

//uint8_t config_pin = 12;

//String to_email = "rahproject190@gmail.com";

//String subject_line = "Rah Package Notification";
//String message;

/*#include <DHT.h>

#if SIMULATED_DATA



float readTemperature()
{
    return random(20, 30);
}

float readHumidity()
{
    return random(30, 40);
}

#else

static DHT dht(DHT_PIN, DHT_TYPE);
void initSensor()
{
    dht.begin();
}

float readTemperature()
{
    return dht.readTemperature();
}

float readHumidity()
{
    return dht.readHumidity();
}

#endif

void initSensor()
{
    pinMode(config_pin,INPUT_PULLUP);
    if(config_pin == LOW){ // Short pin to GND for config AP
      alert.config();
     Serial.println("setup complete");
    }

    alert.connect();
}*/

float readFSR()
{
  int fsrPin = A0;
  return (float)analogRead(fsrPin);
}

bool readMessage(int messageId, char *payload)
{
    float fsrReading = readFSR();
    //float humidity = readHumidity();
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["deviceId"] = DEVICE_ID;
    root["messageId"] = messageId;
    bool packageAlert = false;

    // NAN is not the valid json, change it to NULL
    if (std::isnan(fsrReading))
    {
        root["fsr"] = NULL;
    }
    else
    {
        root["fsr"] = fsrReading;
        if (fsrReading < NO_PACKAGE)
        {
            Serial.println(" - No pressure");
            packageAlert = false;
        } else {
            Serial.println(" - Package detected");
            packageAlert = true;
        }
    }

    /*if (std::isnan(humidity))
    {
        root["humidity"] = NULL;
    }
    else
    {
        root["humidity"] = humidity;
    }*/
    root.printTo(payload, MESSAGE_MAX_LEN);
    return packageAlert;
}

void parseTwinMessage(char *message)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success())
    {
        interval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval"))
    {
        interval = root["interval"];
    }
}
