# حسگر مستقل

>زمانیکه میخواهیم از یک گره بعنوان گیت‌وی برای پیاده‌سازی پردازش لبه استفاده کنیم و یا امنیت مخابره اطلاعات مطرح می‌شود، بکار گرفتن توپولوژی ستاره یک گزینه مطمئن می‌باشد.
>در این توپولوژی هر گره اطلاعات را به گره گیت‌وی مخابره کرده و سپس تصمیمگیری درباره نحوه استفاده از اطلاعات در گیت‌وی صورت می‌گیرد.

## فهرست مطالب

- [مستقل](#مستقل)
    - [بستر](#بستر)
    - [پروتکل](#پروتکل)
    - [تجزیه](#تجزیه)
    - [ضربان](#ضربان)
    - [بروزرسانی](#بروزرسانی)
- [لینک‌](#لینک)
- [منابع](#منابع)

# مستقل


## بستر
![استاندارد ۸۰۲ آی تریپل ای](/archive/images/ieee-802.png)
بستر در این گروه حسگر‌ها مبتنی بر استاندارد ۸۰۲ از موسسه مهندسین برق و الکترونیک یا IEEE می‌باشد.
این استاندارد تعیین کننده نحوه مدیریت ارتباط فیزیکی و ارتباط داده شبکه‌ها می‌باشد.
این استاندارد با تعیین نحوه کنترل منطقی اتصالات (LLC)[^1] و شیوه کنترل دسترسی به بستر (MAC)[^2] قابلیت سوئیچینگ و ارتباط با چند گره را فراهم می‌کند.

حال برای ارتباط بیسیم این ارتباط بصورت نیمه دوطرفه از طریق امواج رادیویی برقرار می‌شود.
در این حالت، هر نود به شنود بستر پرداخته و در صورت آزاد بودن کانال ارتباطی، اقدام به پیروی از استاندارد با هدف برقراری ارتباط می‌نماید.

به نمونه کد آورده شده توجه کنید:

```C++
// Set WiFi credentials
#define WIFI_SSID "Ang-GW"                  //WiFi SSID
#define WIFI_PASS "qwerty4387"              //WiFi password
```

در این بخش از کد، نحوه اتصال به شبکه با پروتکل ۸۰۲/۱۱ را شرح می‌دهد.
توجه به این بخش از کد ضروری بوده و تعیین کننده ارتباط بین تجهیزات می‌باشد.

در بخش دیگری از کد داریم:

```C++
//Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);         //Connect to WiFi network
  WiFi.mode(WIFI_STA);                      //Set mode to station
  
  //Connecting to WiFi...
  Serial.print("Connecting to ");           //Print connecting to WiFi
  Serial.print(WIFI_SSID);
  //Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)     //Wait for connection
  {
    delay(100);                             //Wait 100ms
    Serial.print(".");                      //Print a dot
  }
  
  //Connected to WiFi
  Serial.println();                         //Print a new line
  Serial.print("Connected! IP address: ");  //Print connected
  Serial.println(WiFi.localIP());           //Print IP address
```

این بخش سعی میکند تا با استفاده از کد به شبکه متصل شود.
سپس نوع اتصال به شبکه را تعیین می‌کند.
در ادامه اطلاعات مربوط به عملیاتی که در حال انجام آن می‌باشد را گزارش می‌کند.
با هدف برقراری دوباره اتصال در صورت قطعی ارتباط، در ادامه وضعیت اتصال بیسیم بررسی شده و در صورت بروز هرگونه قطعی هر یکصد میلی ثانیه نسبت به چاپ یک نقطه اقدام می‌نماید.
در پایان عملیات در خطی جدید آدرس گره را در شبکه به ما نمایش می‌دهد.

## پروتکل
![پروتکل داده‌نگار کاربر](/archive/images/UDP_encapsulation.jpg)
در این پروتکل تلاش می‌شود تا بدون برقرار نمودن ارتباطی مشخص نسبت به ارسال اطلاعات اقدام کنیم.
استفاده از این پروتکل[^3] در مواردی که نیاز به بررسی صحت و اصلاح داده‌ها ضروری نیست و یا در مقصد انجام پذیر می‌باشد کاربردی می‌باشد.
همین خصائص این سربار این پروتکل را کاهش داده و سرعت ارتباط را افزایش می‌دهد که مناسب برای سیستم‌های بلادرنگ یا Realtime[^4] می‌باشد.

به نمونه کد آورده شده توجه کنید:

```C++
// UDP
WiFiUDP UDP;                                    //UDP object
IPAddress remote_IP(192,168,4,1);               //IP of the remote server
#define UDP_PORT 4210                           //UDP port of the remote server

// UDP Buffer
char packet[255];                               //buffer for receiving and sending data
char reply[] = "Packet received!";              //reply to the client
```

در این بخش نحوه برقراری ارتباط UDP شرح داده شده است.
ابتدا نامی برای استفاده در برنامه‌نویسی شیء گرای C++ استفاده شده در کتابخانه WiFiUDP تعریف می‌نماییم.
سپس آدرس سرور را در شبکه تعیین نموده و در نهایت پورت مورد استفاده توسط برنامه را مشخص می‌کنیم.

در ادامه میزان حافظه اختصاص داده شده به بسته‌های UDP دریافت شده پیش از دور ریختن آنها را در نظر می‌گیریم.
در نهایت نیز پیامی که در تایید دریافت شدن بسته توسط سیستم بایستی ارسال شود را تبیین می‌نماییم.

در جای دیگری از کد داریم:

```C++
//Begin UDP port
  UDP.begin(UDP_PORT);                          //start UDP connection
  Serial.print("Opening UDP port ");            //print status
  Serial.println(UDP_PORT);                     //print port number
```

که وظیقه برقراری ارتباط UDP بواسطه توابع کتابخانه WiFiUDP را بر عهده دارد.

با توجه به اینکه گره کنونی از نوع مانیتورینگ می‌باشد، ابتدا به نحوه ارسال داده می‌پردازیم:

```C++
void transmitUDP(){                             //defining a void function
  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);         //begin sending data to predefined address and port
  UDP.print(ESP.getChipId());                   //send device identification number
  UDP.write(",");                               //send a comma
  UDP.print(soilMoisture);                      //send soil moisture value
  UDP.write(",");                               //send a comma
  UDP.print(airTemperature);                    //send air temperature value
  UDP.write(",");                               //send a comma
  UDP.print(airHumidity);                       //send air humidity value
  UDP.endPacket();                              //declare end of data packet
}                                               //end of function
```

در این بخش با استفاده از توابع print و write اطلاعات دریافت شده توسط حسگر‌ها را به گیت‌وی ارسال می‌کنیم.
در پاسخ به بسته‌های ارسال شده به گیت‌وی نیز بسته‌ای دریافت خواهد شد، و همچنین می‌توانیم دستوراتی را نیز دریافت کنیم.

دریافت دستورات بواسطه کد زیر صورت میگیرد:

```C++
void receiveUDP(){                              //defining a void function
  // If packet received...
  int packetSize = UDP.parsePacket();           //receive packet and store it in variable
  if (packetSize) {                             //check if buffer is not empty
    Serial.print("Received packet! Size: ");    //declare if a message is in buffer
    Serial.println(packetSize);                 //print the size of data packet
    int len = UDP.read(packet, 255);            //read buffer and get one packet
    if (len > 0){                               //loop through the packet
      packet[len] = '\0';                       //wait for end of packet
    }                                           //end of if
    Serial.print("Packet received: ");          //declare if packet is receive
    Serial.println(packet);                     //print the contents of the packet
  }                                             //end of if
}                                               //end of function
```

در این بخش بافر تعیین شده در حافظه مورد بررسی قرار گرفته و سپس آنرا چاپ می‌کنیم.
حال می‌توان آنرا در یک متغیر قرار داده و نسبت به تجزیه اطلاعات آن اقدام نمود. 

## تجزیه

حال در صورتیکه بسته‌ای داده را دریافت کنیم و بخواهیم آنرا تفسیر نماییم، ابتدا بایستی آنرا تجزیه کنیم.
تجزیه بسته‌های داده در عموم مواقع بواسطه بسته‌های JSON انجام می‌شوند، لیکن تجزیه بسته‌های این استاندارد بوسیله میکروکنترلر‌ها می‌تواند سربار پردازشی و حافظه قابل توجهی در بر داشته باشد.
در مرحله نمونه‌سازی با هدف کاهش مشکلات ناشی از عدم پایداری ارتباطات و بهینه نبودن کد‌ها هر داده را ترتیب داده و با یک علامت کاما از دیگری جدا می‌نماییم.

```C++
//String  var = getValue( StringVar, ',', 2);                               //If  a,4,D,r  would return D        
String getValue (String data, char separator, int index) {                  //defining a void function
    int found = 0;                                                          //declare a variable
    int strIndex[] = { 0, -1 };                                             //declare an array
    int maxIndex = data.length();                                           //declare a variable

    for (int i = 0; i <= maxIndex && found <= index; i ++) {                //loop through the string
        if (data.charAt(i) == separator || i == maxIndex) {                 //check if the character is a separator
            found ++;                                                       //increment the counter
            strIndex[0] = strIndex[1] + 1;                                  //increment the first index
            strIndex[1] = (i == maxIndex) ? i + 1 : i;                      //increment the second index
        }                                                                   //end of if
    }                                                                       //end of for
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";   //return the value
}                                                                           //end of function
```

در این تابع بسته داده بهمراه تفکیک کننده و مرتبه آن را تعیین می‌کنیم.
سپس تابع بدنبال کاراکتر تفکیک کننده تمامی بسته را کاراکتر به کاراکتر تجزیه کرده و به محض مشاهده تفکیک کننده، شمارنده مرتبه را تا رسیدن به مرتبه تعیین شده افزایش می‌دهد.
زمانیکه به مرتبه تعیین شده رسیدیم، عبارت تا تفکیک کننده بعدی در متغیری ذخیره شده و ارائه می‌شود.

## ضربان

عموم تجهیزات اینترنت اشیاء شامل ضربان می‌شوند که سلامت عملکرد آنها را گزارش می‌کند.
در این برنامه بجای گزارش وضعیت گره، ارسال داده جدید را ضربان مفروض شده‌ایم.
برای تنظیم زمانبندی نیز تلاش می‌شود تا بر اساس پالس‌های کریستال در مدار میکروکنترلر، نسبت به نگهداری زمان اقدام نماییم.

کد زیر زمان را محاسبه کرده و در متغیر‌های خاص نگهداری می‌کند:

```C++
void uptime(){                                  //defining a void function
  //Checks For a Second Change
  if(millis() % 1000 <= 500 && Once == 0){      //if the millis() is a multiple of 1000 and the Once variable is 0
  SecondStamp = 1;                              //set the SecondStamp variable to 1
  Once = 1;                                     //set the Once variable to 1
  }                                             //end of if
  //Makes Sure Second Count Doesnt Happen More Than Once a Second
  if (millis() % 1000 > 500){                   //if the millis() is a multiple of 1000 and the Once variable is 1
  Once = 0;                                     //set the Once variable to 0
  }                                             //end of if
  if (SecondStamp == 1) {                       //if the SecondStamp variable is 1
    Second ++;                                  //increment the Second variable
    SecondStamp = 0;                            //set the SecondStamp variable to 0
    if (Second == 60){                          //if the Second variable is 60
      Minute ++;                                //increment the Minute variable
      Second = 0;                               //set the Second variable to 0
      if (Minute == 60) {                       //if the Minute variable is 60
        Minute = 0;                             //set the Minute variable to 0
        Hour ++;                                //increment the Hour variable
        if (Hour == 24) {                       //if the Hour variable is 24
          Hour = 0;                             //set the Hour variable to 0
          Day ++;                               //increment the Day variable
        }                                       //end of if
      }                                         //end of if
    }                                           //end of if
  }                                             //end of if
}                                               //end of function
```

تابع نمایش داده شده تلاش میکند تا با محاسبه باقیمانده شمارنده زمان در مدار میکروکنترلر بر ۱۰۰۰ زمان تقریبی سپری شدن یک ثانیه را حدس بزند.
حال با شمردن ثانیه‌ها نسبت به محاسبه دقیقه و ساعت و روز نیز اقدام می‌کند.
حال برای محاسبه ضربان می‌توانیم باقیمانده عدد ثانیه را بر زمان مورد نظر برای ایجاد ضربان بکار بگیریم.

نمونه کد زیر نحوه انجام این کار را نمایش می‌دهد:

```C++
if ((Second - 1) % 5 == 0 && pulseTimer) {      //if the second is a multiple of 5 and the pulseTimer is 1
    //ESP LED pulsating to show proper functionality
    digitalWrite(D4, LOW);                      //turn the ESP LED off

    tempSense();                                //call the tempSense function

    pulseTimer = false;                         //set the pulseTimer to 0
}                                               //end of if
```

هماهنگونه که مشاهده می‌کنید، هر پنج ثانیه نسبت به خاموش نمودن چراغ تعبیه شده بر روی ESP اقدام نموده و تابع مرتبط با حسگرها را فراخوانی می‌نماییم.

## بروزرسانی

در حال حاضر امکان بروزرسانی از طریق فضای ابری ممکن نیست، لیکن بروزرسانی کد میکروکنترلر از طریق وای فای ممکن می‌باشد.

به کد زیر توجه کنید:

```C++
//Port defaults to 8266
  ArduinoOTA.setPort(8266);                                                     //set the port to 8266
  
  //Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("myesp8266");                                          //set the hostname to myesp8266

  //No authentication by default
  //ArduinoOTA.setPassword("admin");                                            //set the password to admin

  //Password can be set with it's md5 value as well
  //MD5(admin) = 21232f297a57a5a743894a0e4a801fc3                               //set the password to the md5 value of admin
  //ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");             //set the password to the md5 value of admin

  ArduinoOTA.onStart([]() {                                                     //when the OTA starts
    String type;                                                                //create a string variable
    if (ArduinoOTA.getCommand() == U_FLASH) {                                   //if the OTA is flashing a new firmware
      type = "sketch";                                                          //set the type to sketch
    } else { //U_FS                                                             //if the OTA is flashing a new filesystem
      type = "filesystem";                                                      //set the type to filesystem
    }                                                                           //end of if

    //NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);                                   //print the start of the update
  });                                                                           //end of onStart
  ArduinoOTA.onEnd([]() {                                                       //when the OTA ends
    Serial.println("\nEnd");                                                    //print the end of the update
  });                                                                           //end of onEnd
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {         //when the OTA progresss
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));              //print the progress of the update
  });                                                                           //end of onProgress
  ArduinoOTA.onError([](ota_error_t error) {                                    //when the OTA errors
    Serial.printf("Error[%u]: ", error);                                        //print the error
    if (error == OTA_AUTH_ERROR) {                                              //if the error is an authentication error
      Serial.println("Auth Failed");                                            //print the authentication failed
    } else if (error == OTA_BEGIN_ERROR) {                                      //if the error is a begin error
      Serial.println("Begin Failed");                                           //print the begin failed
    } else if (error == OTA_CONNECT_ERROR) {                                    //if the error is a connect error
      Serial.println("Connect Failed");                                         //print the connect failed
    } else if (error == OTA_RECEIVE_ERROR) {                                    //if the error is a receive error
      Serial.println("Receive Failed");                                         //print the receive failed
    } else if (error == OTA_END_ERROR) {                                        //if the error is an end error
      Serial.println("End Failed");                                             //print the end failed
    }                                                                           //end of if
  });                                                                           //end of onError
  ArduinoOTA.begin();                                                           //start the OTA
  Serial.println("Ready");                                                      //print the ready message
```

توجه داشته باشید که قادر به تغییر hostname به نام دلخواه برای بروزرسانی از طریق گیت‌وی خواهید بود.
همچنین می‌توانید بوسیله پسوردی از بروزرسانی بدون هماهنگی کد‌های غیرمجاز جلوگیری بعمل آورید.
در نهایت تنها کافیست تا تابع مدیریت درخواست‌های بروزرسانی را هر سیکل فراخوانی کنیم:

```C++
ArduinoOTA.handle();                                                            //call the OTA handle function
```

# لینک
[استاندارد ۸۰۲](https://www.ieee802.org/ "استاندارد ۸۰۲")

[قرارداد داده‌نگار کاربر](https://datatracker.ietf.org/doc/html/rfc768 "قرارداد داده‌نگار کاربر")

# منابع
[^1]: https://www.techopedia.com/definition/5689/logical-link-control-llc

[^2]: https://www.techopedia.com/definition/25059/media-access-control-mac

[^3]: https://www.geeksforgeeks.org/user-datagram-protocol-udp/

[^4]: https://www.dmcinfo.com/latest-thinking/blog/id/192/rt-201-plcs-vs-real-time-systems