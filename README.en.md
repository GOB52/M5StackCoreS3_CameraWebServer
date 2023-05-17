# M5StackCoreS3_CameraWebServer

[日本語](README.md)

<img src="./M5StackCoreS3_CameraWebServer.jpg" width="480">

## Overview
Porting of [espressif/arduino-esp32](https://github.com/espressif/arduino-esp32) example [CameraWebServer](https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Camera/CameraWebServer) to M5Stack CoreS3 (GC0308).  
Access CoreS3 from a browser via WiFi to control the camera and receive streaming.


## Required libraries
* [M5Unified](https://github.com/m5stack/M5Unified)
* [es32-camera](https://github.com/espressif/esp32-camera/tree/master)   
However, If you set platform = espressif32 and framework = arduino in platformio, esp32-camera is included in the package, so you do not need to specify es32-camera in lib_deps.
* [gob_GC0308](https://github.com/GOB52/gob_GC0308)
* WiFi connection available

## How to use
Once executed, the IP address will be displayed on the screen and on the serial monitor.  
(This is an example, so the actual IP will vary depending on the environment.)
```
 setup(): Camera ready use: http;//192.168.1.20 to connect
```
Access that IP address from your browser.

### When WiFi connection fails
The connection is made as follows, 
assuming that CoreS3 has the SSID / Password of the already connected it stored.
```cpp
// main.cpp
    WiFi.begin(); // Connects to credential stored in the hardware.
```
Please save the credential in some way or rewrite the source.
```cpp
// main.cpp
    WiFi.begin("Your SSID", "Your password");
```

## Browser screen description
### Basic settings
* Resolution  
The currently set camera resolution is displayed. The resolution cannot be changed.
* Contrast  
Change the contrast.
* Special Effect  
Change the special effect.

|Menu|Description|
|---|---|
|NoEffect|No effect|
|Negative|Negative effect|
|Grayscale|Grayscale effect|
|RedTint|Red tint effect|
|GreenTint|Green tint effect|
|BlueTint|Blue tint effect|
|Sepia|Sepia effect|

* WB Mode  
Change the white balance.

|Menu|Description|
|---|---|
|Auto|Automatic|
|Sunny|Sunny|
|Cloudy|Cloudy|
|Office|Fluorescent light|
|Home|Light bulb|

* Gain  
Change the gain.
* H-Mirror  
Changes the horizontal image inversion.
* V-Flip  
Changes the vertical image inversion.
* Color Bar  
Color bar display ON/OFF.
* Get Still  
Obtains a still image.
* Start/Stop Stream  
Start/Stop receiving stream.
* Save  
Download incoming images.
* X  
Stop receiving stream.

### Advanced settings
* Register Get/Set  
The values can be set and retrieved for the camera registers.  
Refer to data sheets and other sources for register and function information.  
**Caution** <ins>Be careful not to set inappropriate values to inappropriate registers. </ins>

## Changes from the original
* The application is now dedicated to M5Stack Core3.
* M5Unified base to work.
* Modified html for GC0308.
* Functions not present in GC0308 were omitted.
