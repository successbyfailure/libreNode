//#include <GDBStub.h>
#define MQTT_MAX_PACKET_SIZE    2048
#include <Arduino.h>
#define FW_VERSION 0.60
//Defines y hacks
#define ADC_UNDERVOLT
#ifdef ADC_UNDERVOLT
  ADC_MODE(ADC_VCC)
#endif
//FASTLED
#define LED_PIN   D8
#define LED_CLOCK D7
//#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#define NTP_SERVER "es.pool.ntp.org"

//librerias
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#include <TimeLib.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <EasyNTPClient.h>
#include <WiFiManager.h>
#include <FastLED.h>

#include <LXWiFiArtNet.h>
#include <LXWiFiSACN.h>
#include <PubSubClient.h>
//
#include "aux.h"
#include "strings.h"
#include "baseNode.h"
#include "nLedBar.h"
#include "nLedKey.h"
#include "nLedMatrix.h"

baseNode*     node;
spifsStorage* s;
#include "ugly.h" //este include va aqui - ugly-hacks

void setup()
{
  Serial.begin(115200);
  Serial.println("\nStart!... V:"+String(FW_VERSION));
  //delay(6000);//Delay para darle tiempo al atom para abrir el terminal serie
  s = new spifsStorage();

  //s->setKeyValue(CONFIG_MODE,ON_BOOT_ERROR);
  startOTA(s->getNodeConfig(NODE_ID));
  if(enterConfigMode(s)) baseNode::launchConfigPortal(s);

  String nodeT = s->getNodeConfig(NODE_TYPE);

  if      (nodeT == NODE_LEDBAR)    node = new ledBarNode(s);
  else if (nodeT == NODE_LEDKEY)    node = new ledKeyNode(s);
  else if (nodeT == NODE_LEDMATRIX) node = new ledMatrixNode(s);
  else                              node = new baseNode(s);

  node->setup();
}

void loop()
{
    node->update();
}
