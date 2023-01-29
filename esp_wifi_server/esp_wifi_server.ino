// ESP Web Server
// kompatibilní s ESP32 a ESP8266
// navody.dratek.cz

// pro použití s ESP32, odkomentujte řádek níže
// #define ESP32

// připojení potřebných knihoven
#ifdef ESP32
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
  #include <ESPmDNS.h>
#else
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>
#endif
// vytvoření proměnných s názvem WiFi sítě a heslem
const char* nazevWifi = "PODA_1325";
const char* hesloWifi = "2AA05AA3";

// incializace webserveru na portu 80
#ifdef ESP32
  WebServer server(80);
#else
  ESP8266WebServer server(80);
#endif
// propojovací pin indikační LED diody a analogového pinu
#ifdef ESP32
  #define LEDka 31
  #define analogPin 32
#else
  #define LEDka LED_BUILTIN
  #define analogPin A0
#endif

// podprogram s hlavní zprávou, která je vytištěna
// při zadání IP adresy do prohlížeče
void zpravaHlavni() {
  // načtení hodnoty analogového pinu a času
  // od spuštění Arduina ve formátu String
  String analog = String(analogRead(analogPin));
  String cas = String(millis() / 1000);
  // vytvoření zprávy, která bude vytištěna
  // v prohlížeči (<br> znamená nový řádek)
  String zprava = "Ahoj Arduino svete!<br>";
  zprava += "Analogovy pin A0: ";
  zprava += analog;
  zprava += "<br>Cas od spusteni Arduina je ";
  zprava += cas;
  zprava += " vterin.<br><br>";
  zprava += "Stav LED: ";
  zprava += digitalRead(LEDka);
  zprava += "<br><br>";
  zprava += "<a href=\"/ledON\"\">Zapni LEDku</a><br><br>";
  zprava += "<a href=\"/ledOFF\"\">Vypni LEDku</a>";
  // vytištění zprávy se statusem 200 - OK
  server.send(200, "text/html", zprava);
}

// podprogram s chybovou zprávou, která je vytištěna
// při zadání IP adresy s neexistující podstránkou
void zpravaNeznamy() {
  // vytvoření zprávy s informací o neexistujícím odkazu
  // včetně metody a zadaného argumentu
  String zprava = "Neexistujici odkaz\n\n";
  zprava += "URI: ";
  zprava += server.uri();
  zprava += "\nMetoda: ";
  zprava += (server.method() == HTTP_GET) ? "GET" : "POST";
  zprava += "\nArgumenty: ";
  zprava += server.args();
  zprava += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    zprava += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  // vytištění zprávy se statusem 404 - Nenalezeno
  server.send(404, "text/plain", zprava);
}

void setup() { 
  // nastavení LED diody jako výstupní a její vypnutí
  pinMode(LEDka, OUTPUT);
  digitalWrite(LEDka, LOW);
  // zahájení komunikace po sériové lince
  Serial.begin(115200);
  // zahájení komunikace po WiFi s připojením
  // na router skrze zadané přihl. údaje
  WiFi.begin(nazevWifi, hesloWifi);
  // čekání na úspěšné připojení k routeru,
  // v průběhu čekání se vytiskne každých
  // 500 milisekund tečka po sériové lince
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // odřádkování a výpis informací o úspěšném připojení
  // včetně přidelené IP adresy od routeru
  Serial.println("");
  Serial.print("Pripojeno k WiFi siti ");
  Serial.println(nazevWifi);
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());
  // kontrola funkčnosti MDNS
  if (MDNS.begin("espwebserver")) {
    Serial.println("MDNS responder je zapnuty.");
  }
  // nastavení vytištění hlavní zprávy po přístupu
  // na samotnou IP adresu
  server.on("/", zpravaHlavni);
  // pokud chceme vytisknout pouze menší zprávy, není
  // nutné je vytvářet v podprogramech jako zpravaHlavni,
  // viz. ukázka níže

  // nastavení vytištění jiné zprávy po přístupu na
  // podstránku ukazka, tedy např. 10.0.0.31/ukazka
  server.on("/ukazka", []() {
    String zprava = "Ukazka odkazu pro vice stranek.";
    server.send(200, "text/plain", zprava);
  });
  // nastavení stavu LED diody na zapnuto
  server.on("/ledON", []() {
    // zapnutí LED diody
    digitalWrite(LEDka, HIGH);
    Serial.println("Zapni LED.");
    // vytištění hlavní stránky
    zpravaHlavni();
  });
  // nastavení stavu LED diody na vypnuto
  server.on("/ledOFF", []() {
    // vypnutí LED diody
    digitalWrite(LEDka, LOW);
    Serial.println("Vypni LED.");
    // vytištění hlavní stránky
    zpravaHlavni();
  });
  // nastavení vytištění informací o neznámém
  // odkazu pomocí podprogramu zpravaNeznamy
  server.onNotFound(zpravaNeznamy);
  // zahájení aktivity HTTP serveru
  server.begin();
  Serial.println("HTTP server je zapnuty.");
}

void loop() {
  // pravidelné volání detekce klienta,
  // v případě otevření stránky se provedou
  // funkce nastavené výše
  server.handleClient();
  // krátká pauza před novým během smyčky
  delay(10);
}