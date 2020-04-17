// Basics
#define null 0


// PINs
#define PIN_BUZZER 3

#define PIN_DIGI_PAD_LATCH 7
#define PIN_DIGI_PAD_CLOCK 6
#define PIN_DIGI_PAD_DATA  5

#define PIN_ANAL_HUNIDITY 5


// Pad Masks
#define PAD_MASK         0b01111111
#define PAD_MASK_LEFT    0b01000000
#define PAD_MASK_TOP     0b00100000
#define PAD_MASK_BOTTOM  0b00010000
#define PAD_MASK_CENTER  0b00001000
#define PAD_MASK_RIGHT   0b00000100
#define PAD_MASK_ACTIONR 0b00000010
#define PAD_MASK_ACTIONL 0b00000001


// String constants
//const char[] = "aze";
//const char *textTitle20 = "AGRD Deluxe Edition";
const char *textTitle = "AGRD Deluxe";

const char *textMainWifi    = "WIFI";
const char *textMainSensor  = "Sensors";
const char *textMainAlarm   = "Alarm";
const char *textMainLogging = "Logging";

const char *textWifiStatus = "Status";
const char *textWifiConnect = "Connect";
const char *textWifiDisconnect = "Disconnect";
//const char *textWifiWPS = "WPS";
// Memory stuff

const char *textSensorsStatus = "Status";

const char *textAlarmToggle = "Toggle";
const char *textAlarmHumidity = "Humidity";
const char *textAlarmGaz = "Gaz";
const char *textAlarmCO = "CO";
const char *textAlarmNO2 = "NO2";

const char *textPartSettings = "Settings";
const char *textPartValue = "Value";
//#define *textPartAlarm *textPartSettings
