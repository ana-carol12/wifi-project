// #include <Arduino.h>
// #include <WiFi.h>
// #include <ezTime.h>
// //Endereço de IP: 172.16.45.162

// // prototipar as funções
// void conexaowifi();
// void reconexaowifi();

// const char *SSID = "SALA 25"; //caixa alta e baixa fazem diferença
// const char *SENHA = "info@134";
//   const unsigned long tempoesperaconexao = 5000;
// const unsigned long tempoesperareconexao = 5000;

// Timezone sp;

// void setup() {
//   Serial.begin(115200);

//   conexaowifi();

//   waitForSync();

//   sp.setLocation("America/Sao_paulo");
//   // sp.setPosix("UTC-3");

//   Serial.println(sp.dateTime());
// }

// void loop() {
// reconexaowifi();
// }

// void conexaowifi() {
//   Serial.printf("Conectando ao Wifi: %s", SSID);

//   WiFi.begin(SSID, SENHA);// faz ele conectar
//   unsigned long tempoinicialwifi = millis();

//   while (WiFi.status() != WL_CONNECTED && millis() - tempoinicialwifi < tempoesperaconexao); {
//     Serial.print(".");
//     delay(500);
//   }
//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("Wifi conectado com sucesso! UHUUUU");
//     Serial.print("Endereço de IP: ");
//     Serial.println(WiFi.localIP());
//   }
//   else {
//     Serial.println("Que pena, deu pra conectar não :(((");
//   }

//     Serial.println(sp.dateTime("'hoje é' 1, D 'de' F 'de' Y"));

// }

// void reconexaowifi() {
//   unsigned long tempoatual = millis();
//   unsigned long tempoultimaconexao = 0;

//   if (tempoatual - tempoultimaconexao > tempoesperareconexao) {
//     if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("Conexão Wifi perdida");
//     conexaowifi();
//     }
//   tempoultimaconexao = tempoatual;
//   }
// }