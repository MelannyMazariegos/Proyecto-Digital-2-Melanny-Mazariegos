/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "maz21055"
#define IO_KEY       "aio_FwDT165c5C4pO6zdilzaF94YBDdl"

/******************************* WIFI **************************************/
#define WIFI_SSID "Salvatierra"
#define WIFI_PASS "Drgadmiel"
// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);