// #include <Arduino.h>
// #include <WiFi.h>
// #include <ezTime.h>

// void conexaowifi();
// void reconexaowifi();

// const char *SSID = "SALA 25";
// const char *SENHA = "info@134";
// const unsigned long tempoesperaconexao = 5000;
// const unsigned long intervaloAtualizacao = 60000; // 1 minuto

// Timezone sp;
// unsigned long ultimoUpdate = 0;

// void setup() {
//   Serial.begin(115200);

//   conexaowifi();

//   waitForSync();
//   sp.setLocation("America/Sao_Paulo");

//   Serial.println("Iniciado!");
// }

// void loop() {
//   reconexaowifi();

//   unsigned long agora = millis();
//   if (agora - ultimoUpdate >= intervaloAtualizacao) {
//     ultimoUpdate = agora;

//     // Formato solicitado
//     String texto = sp.dateTime(
//       "\\H\\o\\j\\e\\ \\é\\ l, d \\d\\e\\ F \\de\\ Y, \\a\\g\\o\\r\\a\\ \\s\\ã\\o\\ h:i:s - p (BRT)"
//     );

//     Serial.println(texto);
//   }
// }

// void conexaowifi() {
//   Serial.printf("Conectando ao Wifi: %s\n", SSID);

//   WiFi.begin(SSID, SENHA);
//   unsigned long inicio = millis();

//   while (WiFi.status() != WL_CONNECTED && millis() - inicio < tempoesperaconexao) {
//     Serial.print(".");
//     delay(500);
//   }

//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.println("\nWifi conectado!");
//     Serial.print("IP: ");
//     Serial.println(WiFi.localIP());
//   } else {
//     Serial.println("\nFalha ao conectar ao Wifi!");
//   }
// }

//  // Formato solicitado
//     String texto = sp.dateTime(
//       "'Hoje é' l, d 'de' F 'de' Y', agora são' h:i:s - p ' (BRT)'"
//     );


// void reconexaowifi() {
//   if (WiFi.status() != WL_CONNECTED) {
//     Serial.println("Reconectando ao Wifi...");
//     conexaowifi();
//   }
// }
