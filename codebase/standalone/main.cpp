#line 1 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
/*  AHT10 Sensor              Active
    Scheduler                 Active
    Wifi Connectivity         Active
    HTTP UDP Stack            Active
    UID                       Active
    Software Watchdog         Active

*/

//Preprocessing
//==============================================================================================================
#include <Arduino.h>                                        // Arduino library
#include <Wire.h>
#include <AHT10.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h> 

//Constants
//==============================================================================================================
#define D4 (2)                                              //SerialControl pins of ESP8266
int cnt ;
String topic = "";
String message = "";

// server
#define WIFI_SSID "NAVID 0168"          // Replace with your SSID
#define WIFI_PASS "navid2212"           // Replace with your SSID
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

const String prefix  = "/angizeh/toossab/1/8";
const char* clientID = "AirHumidityNode010";

const char* mqttServerName = "mqtt.angizehco.com";
const int   mqttport = 1883;
const char* mqttuser =  "security_system";
const char* mqttpass =  "]Hs3@j?[W8BC35~]";

WiFiClient wclient;                        
PubSubClient client(wclient);



//Variables
//==============================================================================================================
boolean pulseTimer = true;                                  // Timer for the pulse
int soilMoisture = 0;                                       // Soil moisture
float airTemperature = 0.0, airHumidity = 0.0;              // Air temperature and humidity
//Timer Variables
long Day = 0;                                               // Day
int Hour = 0;                                               // Hour
int Minute = 0;                                             // Minute
int Second = 0;                                             // Second
int SecondStamp = 0;                                        // Second Stamp
int Once = 0;                                               // Once

//Prototyping
//==============================================================================================================
void uptime();
String getValue(String data, char separator, int index);

//Instances
//==============================================================================================================
AHT10 myAHT10(AHT10_ADDRESS_0X38);                          // Create AHT10 object

//Setup
//==============================================================================================================
#line 71 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
void setup();
#line 168 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
void loop();
#line 205 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
void tempSense();
#line 267 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
boolean reconnect();
#line 292 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
char * toCharArray(String str);
#line 296 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
void onMessageArrived(char* t, byte* m, unsigned int length);
#line 71 "C:\\Users\\Navid.H\\Desktop\\NPK\\SoilMoistureHumidity_sensor_standalone\\humid_sensor_server_standalone\\humid_sensor_server_standalone.ino"
void setup() {                                              // Setup
  //Setup serial port
  Serial.begin(115200);                                     // Start serial port
  Serial.println();                                         // Print a new line
  Serial.println("Booting...");                             // Print booting message

  while (myAHT10.begin() != true)                           // Start AHT10
    {                                                       // If AHT10 fails to start
      Serial.println(F("AHT10 not connected or fail to load calibration coefficient"));//(F()) save string to flash & keeps dynamic memory free
      delay(5000);                                          // Wait 5 seconds
    }                                                       // End if
  Serial.println(F("AHT10 OK"));                            //(F()) save string to flash & keeps dynamic memory free

  //Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);                         // Connect to WiFi network
  WiFi.mode(WIFI_STA);                                      // Set WiFi mode to station
  
  //Connecting to WiFi...
  Serial.print("Connecting to ");                           // Print connecting to message
  Serial.print(WIFI_SSID);                                  // Print SSID
  
  //Loop continuously while WiFi is not connected
  
  while (WiFi.status() != WL_CONNECTED)                     // While WiFi is not connected
  {                                                         // If WiFi is not connected
    delay(100);                                             // Wait 100 milliseconds
    Serial.print(".");                                      // Print a dot
  }                                                         // End if
  
  //Connected to WiFi
  Serial.println();                                         // Print a new line
  Serial.print("Connected! IP address: ");                  // Print connected message
  Serial.println(WiFi.localIP());                           // Print IP address


client.setServer(mqttServerName, mqttport);
client.setCallback(onMessageArrived);
  while (!client.connected()) {
    delay(1000);
    Serial.println("Connecting To Server ...");
    if (client.connect(clientID, mqttuser, mqttpass, toCharArray(prefix + "Will"), 1, true, toCharArray("Disconnected"), true)) {
       Serial.println("Connected To Server");
       
    }
    else { 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  ArduinoOTA.setPort(8266);                                 // Set OTA port

  //Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("myesp8266");                      // Set OTA hostname


  ArduinoOTA.onStart([]() {                                 // When OTA starts
    String type;                                            // String for OTA type
    if (ArduinoOTA.getCommand() == U_FLASH) {               // If OTA command is U_FLASH
      type = "sketch";                                      // Set type to sketch
    } else { //U_FS                                         // If OTA command is U_FS
      type = "filesystem";                                  // Set type to filesystem
    }                                                       // End if

    //NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);               // Print start updating message
  });                                                       // End ArduinoOTA.onStart
  ArduinoOTA.onEnd([]() {                                   // When OTA ends
    Serial.println("\nEnd");                                // Print end message
  });                                                       // End ArduinoOTA.onEnd
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {// When OTA progress
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));// Print progress
  });                                                       // End ArduinoOTA.onProgress
  ArduinoOTA.onError([](ota_error_t error) {                // When OTA error
    Serial.printf("Error[%u]: ", error);                    // Print error
    if (error == OTA_AUTH_ERROR) {                          // If error is OTA_AUTH_ERROR
      Serial.println("Auth Failed");                        // Print auth failed message
    } else if (error == OTA_BEGIN_ERROR) {                  // If error is OTA_BEGIN_ERROR
      Serial.println("Begin Failed");                       // Print begin failed message
    } else if (error == OTA_CONNECT_ERROR) {                // If error is OTA_CONNECT_ERROR
      Serial.println("Connect Failed");                     // Print connect failed message
    } else if (error == OTA_RECEIVE_ERROR) {                // If error is OTA_RECEIVE_ERROR
      Serial.println("Receive Failed");                     // Print receive failed message
    } else if (error == OTA_END_ERROR) {                    // If error is OTA_END_ERROR
      Serial.println("End Failed");                         // Print end failed message
    }                                                       // End if
  });                                                       // End ArduinoOTA.onError
  ArduinoOTA.begin();                                       // Start OTA
  Serial.println("Ready");                                  // Print ready message
}                                                           // End setup

// server


//Main program
//==============================================================================================================

void loop() {                                               // Loop
  uptime();                                                 // Update uptime
  
  constexpr  uint32_t interval    = 1000;                   //interval at which to blink (milliseconds)
  static uint32_t nextMillis  = millis();                   //will store next time LED will updated
  if (millis() > nextMillis) {                              //if it's time to blink the LED
    nextMillis += interval;                                 //save the next time you blinked the LED
  }                                                         //end if

  if ((Second - 1) % 5 == 0 && pulseTimer) {                //If the second is a multiple of 5 and pulseTimer is true
    //ESP LED pulsating to show proper functionality
    digitalWrite(D4, LOW);                                  //Turn on ESP LED

    tempSense();                                            //Update temperature

    pulseTimer = false;                                     //Set pulseTimer to false
  }                                                         //end if

  if (Second % 5 == 0 && !pulseTimer){                      //If the second is a multiple of 5 and pulseTimer is false
    //ESP LED pulsating to show proper functionality
    digitalWrite(D4, HIGH);                                 //Turn off ESP LED

    Serial.print("Device; ");Serial.print("Chip ID: ");Serial.print(ESP.getChipId());Serial.print(" MAC Address: ");Serial.println(WiFi.macAddress());
    Serial.print("Soil Moisture: ");Serial.println(soilMoisture);
    Serial.print("Temperature: ");Serial.print(airTemperature);Serial.println(" degrees C");
    Serial.print("Humidity: ");Serial.print(airHumidity);Serial.println(" RH %");
//    transmitUDP();                                          //Transmit UDP

    pulseTimer = true;                                      //Set pulseTimer to true
  }                                                         //end if
  
  ArduinoOTA.handle();                                      //Handle OTA
}                                                           // End loop

//Functions
//==============================================================================================================

void tempSense(){                                           //Temperature sensor
  soilMoisture = analogRead(A0);                            //Read soil moisture sensor
  
  Serial.print("Device; ");Serial.print("Chip ID: ");Serial.print(ESP.getChipId());Serial.print(" MAC Address: ");Serial.println(WiFi.macAddress());
  Serial.print("Soil Moisture: ");Serial.println(soilMoisture);
  client.publish(toCharArray("/angizeh/toossab/1/8/soilMoisture"), toCharArray(String(soilMoisture)));
  
  airTemperature = myAHT10.readTemperature();               //Read temperature sensor
  airHumidity = myAHT10.readHumidity();                     //Read humidity sensor
  Serial.print("Temperature: ");Serial.print(airTemperature);Serial.println(" degrees C");
  Serial.print("Humidity: ");Serial.print(airHumidity);Serial.println(" RH %");
  client.publish(toCharArray("/angizeh/toossab/1/8/Humidity"), toCharArray(String(airHumidity)));
  client.publish(toCharArray("/angizeh/toossab/1/8/temprature"), toCharArray(String(airTemperature)));
}

void uptime(){                                              //Uptime
  //Checks For a Second Change
  if(millis() % 1000 <= 500 && Once == 0){                  //If the millisecond is a multiple of 1000 and Once is false
  SecondStamp = 1;                                          //Set SecondStamp to 1
  Once = 1;                                                 //Set Once to true
  }                                                         //End if
 
  //Makes Sure Second Count Doesnt Happen More Than Once a Second
  
  if (millis() % 1000 > 500){                               //If the millisecond is not a multiple of 1000
  Once = 0;                                                 //Set Once to false
  }                                                         //End if
  
  if (SecondStamp == 1) {                                   //If SecondStamp is 1
    Second ++;                                              //Increment Second
    SecondStamp = 0;                                        //Set SecondStamp to 0
    if (Second == 60){                                      //If Second is 60
      Minute ++;                                            //Increment Minute
      Second = 0;                                           //Set Second to 0
      if (Minute == 60) {                                   //If Minute is 60
        Minute = 0;                                         //Set Minute to 0
        Hour ++;                                            //Increment Hour
        if (Hour == 24) {                                   //If Hour is 24
          Hour = 0;                                         //Set Hour to 0
          Day ++;                                           //Increment Day
        }                                                   //End if
      }                                                     //End if
    }                                                       //End if
  }                                                         //End if
}                                                           //End uptime

String getValue (String data, char separator, int index) {  
    int found = 0;                                          //Set found to 0
    int strIndex[] = { 0, -1 };                             //Set strIndex to 0
    int maxIndex = data.length();                           //Set maxIndex to data length

    for (int i = 0; i <= maxIndex && found <= index; i ++) {//For i less than or equal to maxIndex and found less than or equal to index
        if (data.charAt(i) == separator || i == maxIndex) { //If data character at i is separator or i is maxIndex
            found ++;                                       //Increment found
            strIndex[0] = strIndex[1] + 1;                  //Set strIndex[0] to strIndex[1] plus 1
            strIndex[1] = (i == maxIndex) ? i + 1 : i;      //Set strIndex[1] to i if i is maxIndex plus 1 or i
        }                                                   //End if
    }                                                       //End for
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";// Return data substring from strIndex[0] to strIndex[1] if found is greater than index or "" if not

}
    //server
    boolean reconnect() {
   while (WiFi.status() != WL_CONNECTED){
    ESP.wdtFeed();            
    ESP.wdtDisable();                     
    delay(500);
    Serial.print(".");
    delay(500);
    cnt--;
        if(cnt==0){
    ESP.wdtDisable();
    #ifdef SOFT_WATCHDOG
    ESP.wdtEnable(0);
    #endif  
    while(1);  
  }
  }
  delay(1000);
  if (client.connect(clientID, mqttuser, mqttpass, toCharArray(prefix + "/Will"), 1, true, toCharArray("Disconnected"), true)) {
    client.setCallback(onMessageArrived);
    Serial.print("***Disconnected***");
  return client.connected();
  }
}
//=======================================================================

char* toCharArray(String str) {
  return &str[0];
}

void onMessageArrived(char* t, byte* m, unsigned int length) {
  topic = String(t);
  message = String((char*)m);
  message = message.substring(0, length);

  if (message == "HELLO") {
    Serial.println("Hello client");
    client.publish(toCharArray(prefix + "/server"), toCharArray("HELLO"));
    Serial.println("Hello server");
  }
}



// END
//==============================================================================================================

