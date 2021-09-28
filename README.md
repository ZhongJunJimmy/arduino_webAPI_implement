# arduino_webAPI_implement

#### 設備:
1. Arduino UNO
2. ENC28J60 網路擴展模組
3. DHT 22 溫濕度感測器

#### 接線說明:
#### 接線說明:
![image](https://github.com/xiguanTw/arduino_webAPI_implement/blob/main/image/pins.png?raw=true)

#### 程式庫:
1. EtherCard
2. DHT

#### 說明:
- 燒錄至Arduino UNO板後，可透過send GET request給 http://[IP]/getdht ，取得DHT22模組之檢測數值。
