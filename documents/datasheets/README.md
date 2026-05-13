# دیتاشیت

>اطلاعات قطعات یا Datasheet به مستنداتی گفته می‌شود که نحوه بکار بستن آنها را شرح می‌دهد.
>توجه داشته باشید که ممکن است قطعه بکار بسته شده با اطلاعات ارائه شده اختلاف داشته و مشابه آن باشد.
>همچنین برخی قطعات بی کیفیت خطای بالایی دارند که با اطلاعات ارائه شده همخوانی نخواهند داشت.

## فهرست مطالب

- [اطلاعات](#اطلاعات)
    - [ESP8266QuickStartGuide](#ESP8266QuickStartGuide)
    - [ESP8266TechnicalReference](#ESP8266TechnicalReference)
    - [TwoWireInterface](#TwoWireInterface)
    - [LM2596Datasheet](#LM2596Datasheet)
    - [CapacitiveSoilMoistureSensorDatasheet](#CapacitiveSoilMoistureSensorDatasheet)
    - [AosongAHT10Datasheet](#AosongAHT10Datasheet)
- [لینک‌](#لینک)
- [منابع](#منابع)

# اطلاعات
اطلاعات ارائه شده در هر سند ارائه شده می‌تواند در هر قالبی باشد.
یک راهنمای شروع بکار سریع، دفترچه مشخصات فنی، کاتالوگ، بروشور یا لینک وبسایت قطعه از انواع متفاوت این اطلاعات می‌باشند.
ارائه اطلاعات بیشتر در نهایت به درک بهتر کمک خواهد کرد، لیکن در صورت غیر ضروری بودن، به نحوی آنرا مشخص کنید تا از گمراهی همکاران جلوگیری شود.

## ESP8266QuickStartGuide
<img src="/archive/images/AVR-esp8266_quick_start_guide_en.jpg" alt="ESP8266QuickStartGuide" title="ESP8266QuickStartGuide" align="right">

میکروکنترلر Espressif ESP8266 در نوع خود بینظیر بوده و هم بصورت SMD و هم در قالب بوردهای توسعه در بازار موجود است.

بوردهای توسعه‌ای نظیر NodeMCU و Wemos از بیشترین کاربری در نمونه‌سازی برخوردار است.

محصول نهایی می‌تواند از محصولی که در این سند اطلاعات آن در دسترس قرار گرفته بهرمند شود.

## ESP8266TechnicalReference
<img src="/archive/images/AVR-esp8266-technical_reference_en.jpg" alt="ESP8266TechnicalReference" title="ESP8266TechnicalReference" align="right">

مشخصات فنی میکروکنترلر Espressif ESP8266 به ما اطلاعات مهمی پیرامون آن می‌دهد.

این اطلاعات شامل میزان انرژی مصرفی، اتصالات هر خروجی یا ورودی، نحوه برقراری ارتباط با سایر تجهیزات از طریق پروتکل SPI[^1] و TWI می‌شود.

در ادامه به نحوه استفاده از قابلیت PWM[^2] اشاره شده و راهکار‌های کنترل و عیبیابی نیز مورد بررسی قرار میگیرند.

## TwoWireInterface
<img src="/archive/images/Protocol-TWI.jpg" alt="TwoWireInterface" title="TwoWireInterface" align="right">

پروتکل ارتباطی Two Wire Interface که به اختصار TWI نیز نامیده می‌شود، استانداردی می‌باشد که امکان برقراری ارتباط با تجهیزات مختلف بر روی بستر پروتکل I2C ممکن می‌نماید.

دانش بر نحوه عملکرد آن می‌تواند به درک بهتر چالش‌های پیش رو در زمان اتصال قطعات به میکروکنترلر کمک نماید.

## LM2596Datasheet
<img src="/archive/images/Regulator-LM2596_Datasheet.jpg" alt="LM2596Datasheet" title="LM2596Datasheet" align="right">

رگولاتور جریان الکتریکی LM2596 یکی از تولیدات شرکت تگزاس اینسترومنتس[^3] می‌باشد.

در دفترچه اطلاعات این قطعه به خروجی‌ها و ورودی‌های آن اشاره شده و نحوه مصرف آن نیز بررسی می‌گردد.

## CapacitiveSoilMoistureSensorDatasheet
<img src="/archive/images/Sensor-Capacitive_Soil_Moisture_Sensor_Datasheet.jpg" alt="CapacitiveSoilMoistureSensorDatasheet" title="CapacitiveSoilMoistureSensorDatasheet" align="right">

حسگر رطوبت خاک خازنی بر اساس اثر دی‌الکتریک موجود در مواد مختلف عمل می‌کند.

این حسگر از یک تایمر برای نمونه برداری از جریان ذخیره شده در صفحات خود بهره میگیرد.

**برخی نمونه‌های در دسترس با اختلاف پتانسیل ۳/۳ ولت تحریک نشده و بایستی ولتاژ بالاتری برای فعال نمودن آنها بکار گرفت.**

## AosongAHT10Datasheet
<img src="/archive/images/Sensor-Temperature-Aosong_AHT10_en_draft_0c.jpg" alt="AosongAHT10Datasheet" title="AosongAHT10Datasheet" align="right">

استفاده از حسگر‌های کالیبره شده در کارخانه از راهکارهای مطمئن سنجش پارامترهای محیطی می‌باشد.

در سالهای اخیر حسگرهای AHT با قیمت پایین و همچنین دقت مثال زدنی خود توانسته‌اند تا گوی رقابت را از سایر رقبا بربایند.

پروتکل ارتباطی این حسگر از نوع TWI می‌باشد که توسط عموم میکروکنترلرها پشتیبانی می‌شود.

# لینک
[وبسایت شرکت اسپرسیف](https://www.espressif.com/ "وبسایت شرکت اسپرسیف")

[وبسایت شرکت آساییر](https://asairsensors.com/ "وبسایت شرکت آساییر")

# منابع
[^1]: https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/all

[^2]: https://docs.arduino.cc/learn/microcontrollers/analog-output/

[^3]: https://en.wikipedia.org/wiki/Texas_Instruments