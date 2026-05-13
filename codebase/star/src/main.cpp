/*  AHT10 Sensor              Active
    Scheduler                 Active
    Wifi Connectivity         Active
    HTTP UDP Stack            Active
    UID                       Active
    Software Watchdog         Active
    Masoud
    June 16, 2022
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

//Constants
//==============================================================================================================
#define D4 (2)                                              //SerialControl pins of ESP8266
//Set WiFi credentials
#define WIFI_SSID "Ang-GW"                                  // Replace with your SSID
#define WIFI_PASS "qwerty4387"                              // Replace with your password
//#define WIFI_SSID "Moaven-Greenhouse"                     // Replace with your SSID
//#define WIFI_PASS "38300710ali"                           // Replace with your password
//UDP
WiFiUDP UDP;                                                // Create UDP object
IPAddress remote_IP(192,168,4,1);                           // IP of the ESP8266
#define UDP_PORT 4210                                       // Port of the ESP8266
//UDP Buffer
char packet[255];                                           // Buffer for incoming and outgoing packets
char reply[] = "Packet received!";                          // Reply to be sent back to the ESP8266

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
void tempSense();                                           // Prototype so PlatformIO doesn't complain
void receiveUDP();
void transmitUDP();
void uptime();
String getValue(String data, char separator, int index);

//Instances
//==============================================================================================================
AHT10 myAHT10(AHT10_ADDRESS_0X38);                          // Create AHT10 object

//Setup
//==============================================================================================================
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

  //Begin UDP port
  UDP.begin(UDP_PORT);                                      // Start UDP port
  Serial.print("Opening UDP port ");                        // Print opening UDP port message
  Serial.println(UDP_PORT);                                 // Print UDP port

  //Port defaults to 8266
  ArduinoOTA.setPort(8266);                                 // Set OTA port

  //Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("myesp8266");                      // Set OTA hostname

  //No authentication by default
  //ArduinoOTA.setPassword("admin");                        // Set password if desired

  //Password can be set with it's md5 value as well
  //MD5(admin) = 21232f297a57a5a743894a0e4a801fc3           // Set password to md5 value
  //ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");         // Set password to md5 value

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

//Main program
//==============================================================================================================
void loop() {                                               // Loop
  uptime();                                                 // Update uptime
  receiveUDP();                                             // Receive UDP
  
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
    transmitUDP();                                          //Transmit UDP

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
  airTemperature = myAHT10.readTemperature();               //Read temperature sensor
  airHumidity = myAHT10.readHumidity();                     //Read humidity sensor
  Serial.print("Temperature: ");Serial.print(airTemperature);Serial.println(" degrees C");
  Serial.print("Humidity: ");Serial.print(airHumidity);Serial.println(" RH %");
}

void receiveUDP(){                                          //Receive UDP
  // If packet received...                                  // If packet received
  int packetSize = UDP.parsePacket();                       // Parse packet
  if (packetSize) {                                         // If packet size is not 0
    Serial.print("Received packet! Size: ");                // Print received packet size
    Serial.println(packetSize);                             // Print received packet size
    int len = UDP.read(packet, 255);                        // Read packet
    if (len > 0){                                           // If packet size is not 0
      packet[len] = '\0';                                   // Add null terminator
    }                                                       // End if
    Serial.print("Packet received: ");                      // Print packet received
    Serial.println(packet);                                 // Print packet
  }                                                         // End if
}                                                           // End receiveUDP

void transmitUDP(){                                         //Transmit UDP
  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);                     // Begin packet
  UDP.print(ESP.getChipId());                               // Print chip ID
  UDP.write(",");                                           // Write comma
  UDP.print(soilMoisture);                                  // Print soil moisture
  UDP.write(",");                                           // Write comma
  UDP.print(airTemperature);                                // Print air temperature
  UDP.write(",");                                           // Write comma
  UDP.print(airHumidity);                                   // Print air humidity
  UDP.endPacket();                                          // End packet
}                                                           // End transmitUDP

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

//String  var = getValue( StringVar, ',', 2);               //If  a,4,D,r  would return D        
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
}// END
//==============================================================================================================