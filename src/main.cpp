/*
  M5StackCoreS3_CameraWebServer
  Porting of espressif/arduino-esp32 example to M5Stack CoreS3 (GC0308)
  See also https://github.com/espressif/arduino-esp32/tree/master/libraries/ESP32/examples/Camera/CameraWebServer

  Author GOB https://twitter.com/gob_52_gob (*^○^*)
*/
#include <M5Unified.h>
#include <esp_camera.h>
#include <WiFi.h>
#include <gob_GC0308.hpp>

// --------------------------------
// Camera GC0308
// Pin settings
#define CAM_PIN_PWDN    -1
#define CAM_PIN_RESET   -1
#define CAM_PIN_XCLK    -1
#define CAM_PIN_SIOD    -1
#define CAM_PIN_SIOC    -1
#define CAM_PIN_D7      47
#define CAM_PIN_D6      48
#define CAM_PIN_D5      16
#define CAM_PIN_D4      15
#define CAM_PIN_D3      42
#define CAM_PIN_D4      15
#define CAM_PIN_D2      41
#define CAM_PIN_D1      40
#define CAM_PIN_D0      39
#define CAM_PIN_VSYNC   46
#define CAM_PIN_HREF    38
#define CAM_PIN_PCLK    45

extern void startCameraServer(); // server.cpp

void setup()
{
    // M5
    M5.begin();
    M5.Log.setEnableColor(m5::log_target_serial, false);
    
    // Camera
    camera_config_t ccfg{};
    ccfg.pin_pwdn  = CAM_PIN_PWDN;
    ccfg.pin_reset = CAM_PIN_RESET;
    ccfg.pin_xclk = CAM_PIN_XCLK;
    ccfg.pin_sccb_sda = CAM_PIN_SIOD;
    ccfg.pin_sccb_scl = CAM_PIN_SIOC;
    ccfg.pin_d7 = CAM_PIN_D7;
    ccfg.pin_d6 = CAM_PIN_D6;
    ccfg.pin_d5 = CAM_PIN_D5;
    ccfg.pin_d4 = CAM_PIN_D4;
    ccfg.pin_d3 = CAM_PIN_D3;
    ccfg.pin_d2 = CAM_PIN_D2;
    ccfg.pin_d1 = CAM_PIN_D1;
    ccfg.pin_d0 = CAM_PIN_D0;
    ccfg.pin_vsync = CAM_PIN_VSYNC;
    ccfg.pin_href = CAM_PIN_HREF;
    ccfg.pin_pclk = CAM_PIN_PCLK;
    ccfg.xclk_freq_hz = 20000000;
    ccfg.ledc_timer = LEDC_TIMER_0;
    ccfg.ledc_channel = LEDC_CHANNEL_0;
    ccfg.pixel_format = PIXFORMAT_RGB565;
    //ccfg.frame_size = FRAMESIZE_VGA; // 640x480
    ccfg.frame_size = FRAMESIZE_QVGA; // 320x240
    //ccfg.frame_size = FRAMESIZE_QQVGA; // 160x120
    ccfg.fb_count = 1;
    ccfg.grab_mode = CAMERA_GRAB_WHEN_EMPTY;    
    ccfg.sccb_i2c_port = M5.In_I2C.getPort(); // Using initialized I2C

    esp_err_t err = esp_camera_init(&ccfg);
    if (err != ESP_OK)
    {
        M5.Display.clear(TFT_RED);
        M5.Display.setCursor(0,0);
        M5_LOGE("Failed to init camera:%d", err);
        delay(1000);
        abort();
    }
    if(!gob::GC0308::complementDriver())
    {
        M5_LOGE("Failed to complement GC0308");
    }
    M5.Display.clear(TFT_DARKGREEN);

    // WiFi
    WiFi.begin(); // // Connects to credential stored in the hardware.
    //WiFi.begin("Your SSID", "Your password"); // or use it.
    WiFi.setSleep(false);

    int retry = 32;
    M5.Display.setCursor(0,0);
    while(retry-- > 0 && WiFi.status() != WL_CONNECTED)
    {
        M5.Display.printf(".");
        delay(200);
    }
    if(WiFi.status() != WL_CONNECTED)
    {
        M5.Display.clear(TFT_RED);
        M5.Display.setCursor(0,0);
        M5_LOGE("Failed to connect WiFi");
        delay(1000);
        abort();
    }

    // Server
    startCameraServer();
    M5.Display.clear(0);
    M5_LOGI("Camera ready use: http;//%s to connect", WiFi.localIP().toString().c_str());
    
    M5.Log.setLogLevel(m5::log_target_display,  ESP_LOG_NONE); // Disable output to display
}

void loop()
{
    delay(10000);
}
