/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "maz21055"
#define IO_KEY       "aio_TnKX69EMBar2gax1Vz87hMum0ZQq"

/******************************* WIFI **************************************/
#define WIFI_SSID "Gaby celular"
#define WIFI_PASS "pami123guate"
// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);