# arduino_webAPI_implement

#### 設備:
1. Arduino UNO
2. ENC28J60 網路擴展模組
3. DHT 22 溫濕度感測器

#### 接線說明:
1. ENC28J60 Module
	VCC		-> 3v3
	CLKOUT	->
	ENC-WOL	->
	RESET	-> RESET
	ENC-INT	-> pin 2
	GND		-> GND
	SCK		-> pin 13
	MIDO	-> pin 12
	MOSI	-> pin 11
	CS		-> pin 10
2. DHT 22 Module
	VCC		-> 5v
	DATA	-> pin 7
	NC		->
	GND		-> GND

#### 程式庫:
1. EtherCard
2. DHT
