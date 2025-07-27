//B
#include <WiFi.h>
#include <esp_now.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// GPIO Definitions
const int buttonPins[5] = {13, 12, 14, 27, 26};
const char* messages[5] = {
  "Hello!",
  "Where are you?",
  "Need help!",
  "See you soon!",
  "All OK here."
};
const int buzzerPin = 33;

// MAC of ESP-A
uint8_t peerAddress[] = {0x, 0x, 0x, 0x, 0x, 0x};

String lastSent = "";
String lastReceived = "";

void displayMessages() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.print("Sent:");
  display.setCursor(0, 10);
  display.print(lastSent);
  display.setCursor(0, 30);
  display.print("---------------");
  display.setCursor(0, 35);
  display.print("Received:");
  display.setCursor(0, 45);
  display.print(lastReceived);

  display.display();
}

void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  char msg[64];
  memcpy(msg, incomingData, len);
  msg[len] = '\0';
  lastReceived = String(msg);
  displayMessages();

  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    while (true);
  }

  display.clearDisplay();
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    while (true);
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (!esp_now_is_peer_exist(peerAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  displayMessages();
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      lastSent = messages[i];
      esp_now_send(peerAddress, (uint8_t *)messages[i], strlen(messages[i]));
      displayMessages();
      delay(300); // debounce
    }
  }
}
