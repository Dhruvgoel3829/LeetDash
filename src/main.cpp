#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "ui.h" 
 // Include your TFT UI helpers

TFT_eSPI tft = TFT_eSPI();

#define USERNAME "Dhruvgoel3829"
#define WIFI_SSID "Jio_2"
#define WIFI_PASSWORD "00000000"
// Your API host and path
#define API_HOST "leetcodestat.vercel.app"
#define API_PORT 443
#define API_PATH "/api/leetcode/" USERNAME
#define FETCH_INTERVAL 30000  // in milliseconds

WiFiClientSecure client;

int totalSolved = 0, easySolved = 0, mediumSolved = 0, hardSolved = 0;
int ranking = 0, rating = 0, submissions = 0;

// Connect to WiFi with timeout
bool connectToWiFi(const char* ssid, const char* password, int timeout = 15000) { ///timeout in milliseconds
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED && millis() - start < timeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    return true;
  } else {
    Serial.println("\nWiFi connection failed");
    return false;
  }
}

// Fetch and parse LeetCode data from API
bool fetchLeetCodeData() {
  client.setInsecure();  // Insecure, use SSL certificate if available.

  Serial.printf("Connecting to %s...\n", API_HOST);
  if (!client.connect(API_HOST, API_PORT)) {
    Serial.println("HTTPS connection failed");
    httpsError();
    delay(5000);
    draw_screen(USERNAME);
    return false;
  }

  // Build and send HTTP request
  client.print(String("GET ") + API_PATH + " HTTP/1.1\r\n" +
               "Host: " + API_HOST + "\r\n" +
               "User-Agent: ESP32\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String payload = client.readString();
  client.stop();

  if (payload.length() == 0) {
    Serial.println("No response received");
    httpsError();
    delay(5000);
    draw_screen(USERNAME);
    return false;
  }

  // Parse JSON
  DynamicJsonDocument doc(4096);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print("JSON parse error: ");
    Serial.println(error.c_str());
    return false;
  }
  
  // Check for error response
  if (doc.containsKey("error")) {
    Serial.println("API Error: User not found");
    userNotFound(USERNAME);
    return false;
  }

  // Extract values
  if (doc.containsKey("profile")) {
    ranking = doc["profile"]["ranking"] | 0;
    rating = doc["profile"]["reputation"] | 0;
  }

  for (JsonObject sub : doc["submitStats"]["acSubmissionNum"].as<JsonArray>()) {
    String difficulty = sub["difficulty"].as<String>();
    int count = sub["count"] | 0;
    int subs = sub["submissions"] | 0;

    if (difficulty == "Easy") easySolved = count;
    else if (difficulty == "Medium") mediumSolved = count;
    else if (difficulty == "Hard") hardSolved = count;
    else if (difficulty == "All") {
      totalSolved = count;
      submissions = subs;
    }
  }

  

  Serial.println("Stats fetched:");
  Serial.printf("Total: %d, Easy: %d, Medium: %d, Hard: %d\n", totalSolved, easySolved, mediumSolved, hardSolved);
  Serial.printf("Ranking: %d, Rating: %d\n", ranking, rating);

  return true;
}

// Refresh screen with data
void updateDisplay() {
  totalArc(totalSolved, submissions);
  easyArc(easySolved);
  mediumArc(mediumSolved);
  hardArc(hardSolved);
  rank(ranking, rating);
}

void setup() {
  Serial.begin(115200);

  // Initialize TFT
  tft.begin();
  tft.setRotation(3);
  connectingWifi(WIFI_SSID);

  // Connect to WiFi
  if (!connectToWiFi(WIFI_SSID, WIFI_PASSWORD)) {
    
    wifiFailed(WIFI_SSID);
    while (true);  // Halt here
  }

  // Initial data load
  //draw_screen(USERNAME);
  fetchLeetCodeData();
  updateDisplay();
  draw_screen(USERNAME);
}

void loop() {
  static unsigned long lastFetch = 0;
  unsigned long now = millis();

  if (now - lastFetch >= FETCH_INTERVAL) {
    if (fetchLeetCodeData()) {
      updateDisplay();
    }
    lastFetch = now;
  }

  delay(200);  // Minimal delay to allow background tasks
}
