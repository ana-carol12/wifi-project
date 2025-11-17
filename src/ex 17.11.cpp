#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

const char *SSID = "SENAI IoT";
const char *SENHA = "Senai@IoT";
const unsigned long tempoEsperaConexao = 10000;
const unsigned long tempoEsperaReconexao = 5000;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED 2
#define BOTAO 15   

int alarmHour = -1;
int alarmMinute = -1;
bool alarmAtivo = false;
bool alarmTocando = false;

String linha1_antiga = "";
String linha2_antiga = "";

const char* meses[] = {
  "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
  "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
};

void configuraHora() {
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Sincronizando horário");

  time_t agora = time(nullptr);
  while (agora < 100000) {
    Serial.print(".");
    delay(500);
    agora = time(nullptr);
  }

  Serial.println("\nHorário sincronizado!");
}

void atualizaLCD(String l1, String l2) {
  if (l1 != linha1_antiga) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(l1);
    linha1_antiga = l1;
  }

  if (l2 != linha2_antiga) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(l2);
    linha2_antiga = l2;
  }
}


void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  pinMode(LED, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  digitalWrite(LED, LOW);

  Serial.println("Conectando ao WiFi...");
  WiFi.begin(SSID, SENHA);

  unsigned long inicio = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicio < tempoEsperaConexao) {
    delay(300);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
    Serial.println("\nWiFi conectado!");
  else
    Serial.println("\nFalha ao conectar!");

  configuraHora();

  Serial.println("\nDigite a hora do alarme (HH MM): ");
  while (Serial.available() == 0);
  alarmHour = Serial.parseInt();
  alarmMinute = Serial.parseInt();

  alarmAtivo = true;

  Serial.printf("Alarme definido para %02d:%02d\n", alarmHour, alarmMinute);
}


void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    static unsigned long ultimaTentativa = 0;
    if (millis() - ultimaTentativa > tempoEsperaReconexao) {
      ultimaTentativa = millis();
      WiFi.begin(SSID, SENHA);
    }
  }

  time_t agora = time(nullptr);
  struct tm* t = localtime(&agora);

  int dia = t->tm_mday;
  int mes = t->tm_mon;
  int ano = t->tm_year + 1900;
  int hora = t->tm_hour;
  int min  = t->tm_min;
  int seg  = t->tm_sec;

  String linha1 = String(dia) + " " + meses[mes] + " " + String(ano);

  String linha2 =
    (hora < 10 ? "0" : "") + String(hora) + ":" +
    (min  < 10 ? "0" : "") + String(min) + ":" +
    (seg  < 10 ? "0" : "") + String(seg) +
    " A:" +
    (alarmHour < 10 ? "0" : "") + String(alarmHour) + ":" +
    (alarmMinute < 10 ? "0" : "") + String(alarmMinute);

  atualizaLCD(linha1, linha2);

  if (alarmAtivo && !alarmTocando && hora == alarmHour && min == alarmMinute) {
    alarmTocando = true;
    Serial.println("Alarme acionado!");
  }

  if (alarmTocando) {
    static unsigned long ultimoBlink = 0;
    static bool estado = false;

    if (millis() - ultimoBlink >= 300) {
      ultimoBlink = millis();
      estado = !estado;

      digitalWrite(LED, estado);
      if (estado) lcd.backlight();
      else lcd.noBacklight();
    }

    // Botão BOOT desliga alarme
    if (digitalRead(BOTAO) == LOW) {
      alarmTocando = false;
      alarmAtivo = false;
      digitalWrite(LED, LOW);
      lcd.backlight();
      Serial.println("Alarme desligado!");
    }
  }

  delay(100);
}