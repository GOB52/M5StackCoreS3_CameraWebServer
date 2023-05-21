# M5StackCoreS3_CameraWebServer

[English](README.en.md)

<img src="https://user-images.githubusercontent.com/26270227/239725404-c5dd33c4-c511-4d05-a192-3d184ef4de8b.png" width="480">

## 概要
[espressif/arduino-esp32](https://github.com/espressif/arduino-esp32) の [CameraWebServer](https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Camera/CameraWebServer) を M5Stack CoreS3 向けに移植した物です。  
WiFi 経由でブラウザから CoreS3 へアクセスし、カメラの制御とストリーミング受信を行います。


## 必要な物
* [M5Unified](https://github.com/m5stack/M5Unified)
* [es32-camera](https://github.com/espressif/esp32-camera/tree/master)  
platformio で platform = espressif32, framework = arduino なら同梱なので必要無し
* [gob_GC0308](https://github.com/GOB52/gob_GC0308)
* WiFi 接続可能な環境

## ビルド種別
|Env|説明|
|---|---|
|release|基本設定|
|release_face|顔検出、認識あり|


## 使い方
実行すると、画面とシリアルモニタに接続先 IP アドレスが表示されます。  
下記は例なので実際は環境によって IP は異なります
```
 setup(): Camera ready use: http;//192.168.1.20 to connect
```
ブラウザからその IP アドレスへアクセスしてください。

### WiFi 接続ができない時
接続は以下のように行っています。CoreS3 に接続済みの SSID / Password が保存されていることが前提です。

```cpp
// main.cpp
    WiFi.begin(); // Connects to credential stored in the hardware.
```
何某かの手段で情報を保存するか、ソースを書き換えてください。
```cpp
// main.cpp
    WiFi.begin("Your SSID", "Your password");
```

## ブラウザ画面説明
### 基本機能
* Resolution  
現在設定されているカメラの解像度を表示しています。解像度変更はできません。
* Contrast  
コントラストを変更します。
* Special Effect  
エフェクトをかけます。

|メニュー|説明|
|---|---|
|NoEffect|エフェクト無し|
|Negative|ネガポジ変換|
|Grayscale|グレイスケール化|
|RedTint|赤化|
|GreenTint|緑化|
|BlueTint|青化|
|Sepia|セピア化|

* WB Mode  
ホワイトバランスを変更します。

|メニュー|説明|
|---|---|
|Auto|自動|
|Sunny|晴天|
|Cloudy|曇天|
|Office|蛍光灯|
|Home|電球|

* Gain  
ゲインを変更します。

* H-Mirror  
水平方向の画像反転を変更します。
* V-Flip  
垂直方向の画像反転を変更します。
* Color Bar  
カラーバー表示の ON/OFF

* Face Detection  
顔検知機能の ON/OFF
* Face Recognition  
顔認識機能の ON/OFF  
**注 顔認識は処理がとても重くなります。**

* Get Still  
静止画像取得
* Start/Stop Stream  
ストリーム受信の開始/終了
* Enroll Face  
カメラに写っている顔を登録します。  
登録すると Face Recogintion ON の時に侵入者(赤枠)扱いになりません。

* Save  
受信画像をダウンロードします。
* X  
ストリームの終了

### 拡張機能
* Register Get/Set  
カメラのレジスタに対しての値の設定、取得ができます。  
レジスタと機能についてはデータシートなどを参考にしてください。  
**注意** <ins>適切でない値を適切でないレジスタへ設定しないように気をつけてください。</ins>

## オリジナルからの変更点
* M5StackCoreS3 専用のアプリケーションになった。
* M5Unified ベースで動作するようにした。
* GC0308 用に html を修正した。
* GC0308 に無い機能を割愛した。
 
