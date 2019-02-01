# Arklab_RobotCon_Joystick
## RobotCon_Joystick 產品照片
![JoyStick](https://raw.githubusercontent.com/arklab-source/Arklab_RobotCon_Joystick/master/RobotCon_Joystick.jpg)
# 最新版本說明：https://www.notion.so/arklab/RobotCon-Joystick-163908c4140c4ea38140ec90c0e64b9b
# RobotCon Joystick 創客的遙控器

# 介绍

---

RobotCon Joystick 是堪稱創客專用的遙控器，可以從遙控器自行定義各個腳位，內裝Arduino 單晶片控制器、藍芽，可供創客來操控不同的專題。

# 系統特性

---

- 核心板：ATmega328 相容於：Arduino Pro or Pro Mini(5V, 16MHz)
- 電池電壓：3.7V
- 電池規格：三顆4號AA電池
- 充電方式：無
- 充電供電：5V
- 遙控距離：藍芽2.0 10m   nRF24L01 100m

# 材料清單

---

1. Micro USB線 x1
2. Arduino 主板
3. Arduino 藍芽模組 HC05
4. nRF24L01 
5. 各部按鈕零件
6. 遙控外殼(上、下)
7. M2螺絲 x3

# **接口布局和尺寸**

---

## 尺寸圖

![](2019-01-0810-fe18a305-325d-4c2c-b364-0e48975836b5.24.16.png)

## 按鈕解說

![](-cefe3431-b595-40ac-8862-78d774d9c824.png)

## 電路板布局

![](-f250a159-e7de-4ae2-b1cf-b9d34d33f75a.png)

# 快速入門

![](-1e724db2-33a0-47e8-8816-e86cb237e478.png)

![](-2b5cbd59-272e-4272-91cf-8036623c775e.jpg)

![](2019-01-0810-a8e1ed44-368c-4de3-a688-5cbe8aee04db.24.04.png)

材料清單

[13b69b7be6585b3a5805206d33cf27d4-208f22e3-6d16-46fe-b0de-b5c01211e350.pdf](13b69b7be6585b3a5805206d33cf27d4-208f22e3-6d16-46fe-b0de-b5c01211e350.pdf)

電路圖（點選右鍵看原圖）

---

# 設備連接應用

1. 將Micro-USB 連接到飛機上

    ![](2019-01-0810-b645d185-8ed1-496c-81c2-047019e9b8e6.39.08.png)

2. 電腦端驅動程式安裝
    1. 將連結上飛控核心的 CH340 插入電腦 USB 連接埠中。
    2. 如出現裝置驅動軟體安裝不成功

        ![](Untitled-a69002ad-444c-46bf-bc34-6dc5516d77af.png)

    3. 請打開下載的資料包（Robot fly開源資料包\程式燒錄器Driver\CH341SER.EXE）

        ![](Untitled-0fdf57c6-2638-4373-9b88-7ac53e61e79f.png)

    4. 記住裝置連接埠（ㄅㄨˋ）

        ![](Untitled-67509488-f801-4b94-8b1c-6f5d976a6aab.png)

# 燒錄程式碼

1. 安裝好Arduino 1.0.6 可以使用材料包內的安裝檔案
2. 程式碼：在Github 上的 MultiWii_x4_mpu6050_last_bluetooth
將MultiWii_x4mpu6050_last_bluetooth.ino 以Arduino開啟

    [arklab-tw/arklab-blockyfly](https://github.com/arklab-tw/arklab-blockyfly/tree/master/MultiWii_x4_mpu6050_last_bluetooth)

3. 設定Arduino 板子
Arduino Pro or Pro Mini(5V, 16MHz) w/ATmega328

    ![](Untitled-8d679601-3519-4fe5-940d-d61acdbb52eb.png)

4. 上傳程式碼

    ![](Untitled-13905aeb-04b0-4d0a-be31-3225863e1ab2.png)

    ## 若燒錄失敗

    - 藍芽開關是否關閉！
    - 是否已經安裝了驅動程式
    - 電腦與 FTDI 是否有接上
    - USB 連接線正確連接
    - 晶片與序列埠是否選擇正確
    - Arduino 建議使用開源包內的版本

---

# 資源連結

## 程式碼

# WIKI 更新日誌

- 2018/10/26
    - Version 1
