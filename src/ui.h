#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;
void draw_screen(String user);
void totalArc(int total,int submissions);
void easyArc(int easy);
void mediumArc(int medium);
void hardArc(int hard);
void rank(int rank,int rating);
void connectingWifi(String ssid);
void httpsError();
void wifiFailed(String ssid);
void userNotFound(String USER);

#endif 