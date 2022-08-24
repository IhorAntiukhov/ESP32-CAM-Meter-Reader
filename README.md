## ESP32-CAM Meter Reader

With this project, you can see the current reading of your *water, gas, or electricity meter* from my *app*. From it you can also see the previous readings of the meter on the *chart*. I made my project based on [AI-on-the-edge-device](https://github.com/jomjol/AI-on-the-edge-device). I made it so that the meter readings are *not sent to the MQTT server*, but are stored in the *Firebase* Realtime Database. Besides, I improved the HTML pages for the Web server and made them prettier. **Below is my video about this project on YouTube**.

[![Video about my project on YouTube](https://img.youtube.com/vi/txgsXdb_OfQ/0.jpg)](https://www.youtube.com/watch?v=txgsXdb_OfQ)

## Firmware flashing

In general, you can learn how to flash the firmware from the [original repository](https://github.com/jomjol/AI-on-the-edge-device/wiki/Installation), but to understand the project, I will describe this in my repository.

To flash firmware using *esptool* in python, first install esptool.

```
pip install esptool
```

Then connect the ESP32-CAM board via *USB-UART converter* and use this command to clear the flash memory.

```
esptool.py.exe erase_flash
```

After that, open a command prompt in the *"firmware"* folder and enter command below.

```
esptool.py.exe write_flash 0x01000 bootloader.bin 0x08000 partitions.bin 0x10000 firmware.bin
```

## Micro SD

Open the *"wlan.ini"* file from the *"micro-sd-content"* folder and specify the name and password of your WiFi network. Then *format* your Micro SD card with FAT32 file system and copy all files from *"micro-sd-content"* folder to Micro SD.

## Tools and frameworks that I used

[<img align="left" alt="ESP-IDF" width="36px" src="https://cdn-images-1.medium.com/max/278/1*f5X-ZCG4vlJ7V5W7KPBicg@2x.png"/>](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
[<img align="left" alt="AndroidStudio" width="36px" src="https://img.icons8.com/color/344/android-studio--v3.png"/>](https://developer.android.com/studio)
[<img align="left" alt="Firebase" width="36px" src="https://raw.githubusercontent.com/github/explore/80688e429a7d4ef2fca1e82350fe8e3517d3494d/topics/firebase/firebase.png"/>](https://firebase.google.com)
</br>
</br>
## Firebase

I also created a project on the [Firebase](https://firebase.google.com) platform. I have used the following Firebase tools:
+ [Firebase Authentication](https://firebase.google.com/docs/auth)
+ [Realtime Database](https://firebase.google.com/docs/database)