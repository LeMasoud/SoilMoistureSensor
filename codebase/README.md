# برنامه منبع

>هر پروژه مبتنی بر فناوری دیجیتال شامل کد و برنامه‌هایی می‌شود.
حال این مجموعه کد‌هایی که تشکیل یک برنامه را می‌دهند در هر مخزن قرار داده خواهند شد تا توان مدیریتی بیشتری به اعضای گروه ببخشد.
لازمه این امر تفکر پودمانی می‌باشد که می‌تواند برنامه را به بخش‌های مختلفی تقسیم کند.
بصورت پیشفرض هر دسته از پروژه‌ها شامل پودمان‌های مشخصی می‌شوند که در ادامه بعنوان راهنما به برخی از آنها اشاره می‌شود.


## فهرست مطالب

- [برنامه](#برنامه)
    - [مستقل](#مستقل)
    - [مش](#مش)
    - [ستاره](#ستاره)
- [لینک‌](#لینک)
- [منابع](#منابع)

# برنامه
هر گره بکار گرفته شده در اینترنت اشیاء از برنامه مشخصی پیروی می‌کند.
در زمان نگارش برنامه تلاش کنید تا از محیط توسعه‌ای بهره بگیرید تا شناسایی بخش‌های مختلف کد نوشته شده را برای شما تسهیل کند.
همچنین تلاش کنید تا با نوشتن توضیحات تکمیلی به درک بهتر کد نوشته شده کمک کنید تا سایرین زمان کمتری را برای درک برنامه شما صرف کنند.

در زیر نمونه‌ای از این شیوه کدنویسی آورده شده است:

```C++
if (message == "HELLO") {                                                   //loop to check if message is "HELLO"
    Serial.println("Hello client");                                         //print "Hello client" in serial monitor
    client.publish(toCharArray(prefix + "/server"), toCharArray("HELLO"));  //publish "HELLO" to topic "prefix/server"
    Serial.println("Hello server");                                         //print "Hello server" in serial monitor
}                                                                           //end of if
```

در نهایت با توجه به محصول تلاش کنید که کد‌ها را تا جای ممکن یکسان سازی کنید.
در صورتیکه هنوز امکان آن وجود ندارد، سعی کنید تا برای هر نوع از محصول کد مختص به خود را بنویسید.
در آینده با استفاده از همین کد‌ها قادر به ارائه برنامه‌ای مجسم برای ارائه‌ی محصولی چند جانبه خواهیم شد.

#### مستقل
لازمه استفاده از برنامه‌ها فارق از بستر ابری یا سرویس‌دهندگان محلی، تببین نحوه عملکرد آنها به نحوی است که بر بعنوان سامانه بر روی پردازشگر‌هاست.
این بدان معنیست که کد‌های سخت‌افزار، رایانش ابری و پیشخوان نیز قادر به ارائه چنین خدماتی بعنوان یک پودمان خواهند داشت.
تلاش بایستی بر آن باشد که حداکثر میزان ترابرپذیری را برای این دسته از کد‌ها فراهم آوریم.
در زیر تصویر دو نمونه حسگر مستقل ECOWITT WH0291[^1] در سمت چپ و HS2_HydroSense_II[^2] در سمت راست نمایش داده شده‌اند.

![حسگر رطوبت خاک مستقل](/archive/images/ECOWITT_WH0291_and_HS2_HydroSense_II_Handheld_Soil_Moisture_Sensor.jpg)

#### مش
مش یا تور نوعی توپولوژی ارتباطی هست که در آن هر گره می‌تواند به دیگری خدمات زیرساخت نیز ارائه کند.
در طراحی گره‌هایی با قابلیت مش، این فرصت را برای گسترش شبکه بواسطه ارتباط هر نود با دیگری بواسطه سایر نود‌ها فراهم میکنیم.
پردازش مه در این گونه از توپولوژی‌ها بسیار مرسوم می‌باشد.
در زیر تصویر دو نمونه حسگر مش S05-SM Zigbee[^3] در سمت چپ و NCD[^4] در میانه و Tyya[^5] در سمت چپ نمایش داده شده است.

![حسگر رطوبت خاک مش](/archive/images/NCD_and_S05-SM_Tuya_ZigBee_Wireless_Outdoor_Soil_Moisture_Sensor.jpg)

#### ستاره
توپولوژی ستاره درست بمانند سوئیچ‌های کنونی شبکه یا سرور‌ها عمل میکند که یک گره بعنوان درگاه ارتباطی به تمامی گره‌ها خدمات می‌دهد.
این نوع از توپولوژی به دلیل ارائه خدمات پردازش لبه و مه بسیار مرسوم می‌باشند.
در تصویر زیر دو نمونه حسگر با توپولوژی ستاره Plaid[^6] در سمت چپ و Soilmote[^7] در سمت راست نمایش داده شده‌اند.

![حسگر رطوبت خاک ستاره‌ای](/archive/images/Soilmote_and_Plaid_Systems_Spruce_Irrigation_Soil_Moisture_Sensor_Gen_3.jpg)

# لینک
[مش زیگبی](https://www.nxp.com/products/wireless/zigbee:ZIGBEE-PROTOCOL "مش زیگبی")

# منابع
[^1]: https://www.amazon.com/ECOWITT-Moisture-Digital-Display-Outdoor/dp/B07CJYTSH1/ref=asc_df_B07CJYTSH1/?tag=hyprod-20&linkCode=df0&hvadid=242081228138&hvpos=&hvnetw=g&hvrand=12380156495847551252&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=2840&hvtargid=pla-522582047691&psc=1

[^2]: https://www.campbellsci.com/hs2

[^3]: https://www.cens.com/cens/html/en/product/product_main_137535.html

[^4]: https://store.ncd.io/product/wireless-soil-moisture-sensor-greenhouse-iot/

[^5]: https://expo.tuya.com/product/839027

[^6]: https://www.amazon.com/Plaid-Systems-Spruce-Irrigation-Moisture/dp/B07TYJCG1J/ref=asc_df_B07TYJCG1J/?tag=hyprod-20&linkCode=df0&hvadid=385169514948&hvpos=&hvnetw=g&hvrand=12380156495847551252&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=2840&hvtargid=pla-849473477017&psc=1&tag=&ref=&adgrpid=80078690138&hvpone=&hvptwo=&hvadid=385169514948&hvpos=&hvnetw=g&hvrand=12380156495847551252&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=2840&hvtargid=pla-849473477017

[^7]: https://www.zynect.com/home/store/buy-soilmote/?gclid=CjwKCAjw46CVBhB1EiwAgy6M4urnhoM4-bRy712tTdy5PQHc4hVtBV4wRRBqir0P_AuZqPXDww3dRhoCvGcQAvD_BwE