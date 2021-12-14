# 實做在Arduino上透過http GET取值 (以溫溼度感應為例)

#### 設備:
1. Arduino UNO
2. ENC28J60 網路擴展模組
3. DHT 22 溫濕度感測器

#### 接線說明:
| ENC28J60 Module   | Arduino UNO   |
|-       |-      |
| VCC    | 3v3   |
| CLKOUT |       |
| ENC-WOL|       |
| RESET  | RESET |
| ENC-INT| 2     |
| GND    | GND   |
| SCK    | 13    |
| MIDO   | 12    |
| MOSI   | 11    |
| CS     | 10    |

| DHT 22 Module   | Arduino UNO   |
|-       |-      |
| VCC    | 5v    |
| GND    | GND   |
| DATA   | 7     |

#### 程式庫:
1. EtherCard
2. DHT

#### 說明:
1. 將 webServer/webServer.ino 編譯後燒錄至Arduino UNO板。
2. 依照接線說明將ENC28J60模組及DNH 22模組接上Arduino UNO板後
3. 透過send GET request給 http://[IP]/getdht ，取得DHT22模組之檢測數值。
