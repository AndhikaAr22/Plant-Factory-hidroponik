//sensor DHT11
#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);
float suhu_DHT11;
float kelembapan_DHT11;

//sensor TDS
int sensorPinTDS = A1;
float tegTDS [10];
float rata_rata_tegTDS, jumlahTDS;
int nilai_TDS;
int bacapemingguTDS ;
int takaranTDS;
int langkah ;
int ngaturtds;
//sensor pH
int sensorPinpH = A3;
float tegpH[10];
float rata_rata_tegpH, jumlahpH, nilai_pH;
int bacaharianpH;
int langkahpH;

// Posisi pin relay
int relay1 = 4;  //pompa Hidroponik
int relay2 = 5;  //pompa pH UP
int relay3 = 6;  //pompa pH DOWN
int relay4 = 7;  //pompa pupuk A
int relay5 = 8;  //pompa pupuk B
int relay6 = 9;  //Fan DC
int relay7 = 10; //Grow LED
int relay8 = 11; //valve
int relay9 = 13; //humidifr


// Status relay
int relay1Status = 0; // kontrol pompa Hidroponik
int relay2Status = 0; // kontrol pompa pH UP
int relay3Status = 0; // kontrol pompa pH DOWN
int relay4Status = 0; // kontrol pompa pupuk A
int relay5Status = 0; // kontrol pompa pupuk B
int relay6Status = 0; // kontrol fan DC
int relay7Status = 0; // kontrol Grow LED
int relay8tatus  = 0; // kontrol valve
int relay9tatus  = 0; // kontrol humidifer

//lampu dan pompa
int lampu_pompa = 0;

// Hari buat reset var langkah
int hari, hariSeb;

// Variabel serial

#include <SoftwareSerial.h>
SoftwareSerial serialPort(2, 3); // RX, TX
String dataSerial;
unsigned long waktu, millisTDS;
int durasi = 1500;

// Konfigurasi awal
void setup() {

  // Kecepatan komunikasi serial
  Serial.begin(9600);
  dht.begin();
  serialPort.begin(9600);

  // Konfigurasi pin relay jadi output
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  //pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(relay9, OUTPUT);
  // Kondisi awal pin relay
  //digitalWrite(relay4, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay8, LOW);




  // Nyamain dulu sekali
  nerimaData();
  hariSeb = hari;
}

// Fungsi utama
void loop() {

  nerimaData();
//ini nerima data
  if (millis() > waktu) {
    waktu = millis() + durasi;
    ngirimData();
    pembacaan_DHT ();
    pembacaan_TDS ();
    pembacaan_pH ();
   //Serial.println (langkah);
    //kontrol lampu dan pompa hidroponik
    if (lampu_pompa == 1) {
      digitalWrite (relay1, LOW);
      digitalWrite (relay7, LOW);
      //      Serial.println ("nyala lampu pompa");
    } else {
      digitalWrite (relay1, HIGH);
      digitalWrite (relay7, HIGH);
      //      Serial.println ("mati lampu pompa");
    }
    //kontrol suhu
    if (suhu_DHT11 >= 30) {
      digitalWrite(relay6 , LOW);
      //      Serial.println ("nyala fan");
    } else if (suhu_DHT11 <= 28){
      digitalWrite(relay6 , HIGH);
      //      Serial.println ("mati fan");
    }
    //kontrol kelembapan
    if (kelembapan_DHT11 < 80) {
      digitalWrite(relay9 , LOW);
      //      Serial.println ("nyala humi");
    } else {
      digitalWrite(relay9 , HIGH);
      //      Serial.println ("mati humi");
    }

    //kontrol pompa nutrisi
    if (bacapemingguTDS == 1 ) {
      // Langkah
      if (langkah == 1) {
        pembacaan_TDS ();

      }
      else if (langkah == 2) {
        pompa_nutrisi ();
      }
      else if (langkah == 3) {// ngaduk nutrisi
        kelar_pompa_nutrisi();
      }
      else if (langkah == 4) { // kelar ngaduk nutrisi
        digitalWrite (relay4, HIGH);
        digitalWrite (relay5, HIGH);
        digitalWrite (relay8, LOW); //buka valve
      }
//      kontrol pompa pH
//      else if (langkah == 5) {
//        pembacaan_pH ();
//      }
//      else if (langkah == 6) {
//        pompa_pH();
//      }
//      else if (langkah == 7) {
//        digitalWrite (relay2, HIGH);
//        digitalWrite (relay3, HIGH);
//      }
//      else if (langkah == 8) {
//        digitalWrite (relay8, LOW); //buka valve
//      }

      // Durasi TDS
      if (millisTDS < millis() and langkah == 0) {
        langkah = 1;
        millisTDS = millis() + 10000;
      }
      else if (millisTDS < millis() and langkah == 1) {
        langkah = 2;
        millisTDS = millis() + 5000;
      }
      else if (millisTDS < millis() and langkah == 2) {
        langkah = 3;
        millisTDS = millis() + 30000;
      }
      if (millisTDS < millis() and langkah == 3 and nilai_TDS < takaranTDS) {
        langkah = 2;
        millisTDS = millis() + 5000;
      }
      else if (millisTDS < millis() and langkah == 3 and nilai_TDS >= takaranTDS) {
        langkah = 4;
        millisTDS = millis() + 60000;
      }

      //durasi pH
//      if (millisTDS < millis() and langkah == 4 ) {
//        langkah = 5;
//        millisTDS = millis() + 10000;
//      }
//      else if (millisTDS < millis() and langkah == 5) {
//        langkah = 6;
//        millisTDS = millis() + 10000;
//      }
//      else if (millisTDS < millis() and langkah == 6) {
//        langkah = 7;
//        millisTDS = millis() + 30000;
//      }
//      if (millisTDS < millis() and langkah == 7 and (nilai_pH < 6 or nilai_pH > 7)) {
//        langkah = 6;
//        millisTDS = millis() + 10000;
//      }
//      else if (millisTDS < millis() and langkah == 7 and nilai_pH >= 6 and nilai_pH <= 7) {
//        langkah = 8;
//      }
    }
//    if (bacaharianpH == 1) {
//      if (langkah == 5) {
//        pembacaan_pH ();
//      }
//      else if (langkah == 6) {
//        pompa_pH();
//      }
//      else if (langkah == 7) {
//        digitalWrite (relay2, HIGH);
//        digitalWrite (relay3, HIGH);
//      }
//      else if (langkah == 8) {
//        digitalWrite (relay8, LOW); //buka valve
//      }
//      if (millisTDS < millis() and langkah == 4) {
//        langkah = 5;
//        millisTDS = millis() + 10000;
//      }
//      else if (millisTDS < millis() and langkah == 5) {
//        langkah = 6;
//        millisTDS = millis() + 10000;
//      }
//      else if (millisTDS < millis() and langkah == 6) {
//        langkah = 7;
//        millisTDS = millis() + 30000;
//      }
//      if (millisTDS < millis() and langkah == 7 and (nilai_pH < 5 or nilai_pH > 6)) {
//        langkah = 6;
//        millisTDS = millis() + 10000;
//      }
//      else if (millisTDS < millis() and langkah == 7 and nilai_pH >= 5 and nilai_pH <= 6) {
//        langkah = 8;
//      }
//    }
  }

  // Reset var langkah
  if (hari != hariSeb and hari != 0 and langkah == 8) {
    langkah = 5;
    hariSeb = hari;
  }
  else if (hari != hariSeb and hari == 0 and langkah == 8) {
    langkah = 0;
    hariSeb = hari;
  }
////  if (ngaturtds == 0){
//    langkah = 0;
//  }
}

// Fungsi parsing data serial
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
