/*
  VÍDEO 1 - ROSTO NA TELA OLED (só ESP32 + tela)

  Ligações (apenas 4 fios):
    OLED VCC -> 3V3
    OLED GND -> GND
    OLED SDA -> GPIO 27
    OLED SCL -> GPIO 26

  O que faz: mostra um rosto que pisca e que muda de expressão sozinho
  (feliz -> surpreso -> sonolento -> feliz ...).
*/

#include <Wire.h>              // comunicação I2C (os 2 fios de dados da tela)
#include <Adafruit_GFX.h>      // biblioteca para desenhar formas e textos
#include <Adafruit_SSD1306.h>  // biblioteca da nossa tela OLED

// ---------- 1. PINOS E TELA ----------
#define PIN_SDA 27   // fio de dados
#define PIN_SCL 26   // fio do relógio

// Cria o objeto "tela": 128 pixels de largura x 64 de altura
Adafruit_SSD1306 tela(128, 64, &Wire, -1);

// ---------- 2. EXPRESSÕES ----------
// enum = uma lista de opções com nome. Facilita ler o código.
enum Expressao { FELIZ, SURPRESO, SONOLENTO };
Expressao expressaoAtual = FELIZ;

// ---------- 3. CONTROLE DE TEMPO ----------
// Usamos millis() (milissegundos desde que o ESP32 ligou) em vez de delay(),
// para o rosto poder piscar e trocar de expressão sem travar o programa.
unsigned long proximaPiscada = 0;   // quando vai piscar de novo
unsigned long fimPiscada = 0;       // quando termina a piscada atual
bool piscando = false;              // true = olhos fechados agora

unsigned long proximaTroca = 0;                   // quando muda de expressão
const unsigned long TEMPO_EXPRESSAO = 8000;       // cada expressão dura 8 segundos

// ---------- 4. DESENHO DO ROSTO ----------
// fechados = true -> desenha os olhos fechados (usado na piscada)
void desenharRosto(Expressao e, bool fechados) {
  tela.clearDisplay();   // apaga tudo antes de desenhar de novo

  switch (e) {

    case FELIZ:
      if (fechados) {
        // olho fechado = uma linha horizontal
        tela.drawFastHLine(30, 30, 22, SSD1306_WHITE);
        tela.drawFastHLine(76, 30, 22, SSD1306_WHITE);
      } else {
        // olho aberto = retângulo com cantos arredondados
        tela.fillRoundRect(30, 16, 22, 28, 6, SSD1306_WHITE);
        tela.fillRoundRect(76, 16, 22, 28, 6, SSD1306_WHITE);
      }
      // boca sorrindo (3 linhas formando um "U" achatado)
      tela.drawLine(48, 52, 56, 58, SSD1306_WHITE);
      tela.drawLine(56, 58, 72, 58, SSD1306_WHITE);
      tela.drawLine(72, 58, 80, 52, SSD1306_WHITE);
      break;

    case SURPRESO:
      if (fechados) {
        tela.drawFastHLine(29, 30, 24, SSD1306_WHITE);
        tela.drawFastHLine(75, 30, 24, SSD1306_WHITE);
      } else {
        // olhos redondos e grandes
        tela.fillCircle(41, 30, 12, SSD1306_WHITE);
        tela.fillCircle(87, 30, 12, SSD1306_WHITE);
      }
      // boca aberta = círculo vazio
      tela.drawCircle(64, 54, 5, SSD1306_WHITE);
      break;

    case SONOLENTO:
      // olhos "meio fechados" (retângulos baixos). Este não pisca.
      tela.fillRoundRect(30, 28, 22, 8, 3, SSD1306_WHITE);
      tela.fillRoundRect(76, 28, 22, 8, 3, SSD1306_WHITE);
      // boca reta
      tela.drawFastHLine(54, 56, 20, SSD1306_WHITE);
      // "zzz" no canto
      tela.setTextSize(1);
      tela.setTextColor(SSD1306_WHITE);
      tela.setCursor(104, 8);
      tela.print("z");
      tela.setCursor(112, 0);
      tela.print("Z");
      break;
  }

  tela.display();   // envia o desenho para a tela
}

// ---------- 5. LÓGICA DA PISCADA ----------
void atualizarPiscada() {
  // O sonolento não pisca (os olhos já estão meio fechados)
  if (expressaoAtual == SONOLENTO) return;

  unsigned long agora = millis();

  if (!piscando && agora >= proximaPiscada) {
    // chegou a hora de piscar: fecha os olhos
    piscando = true;
    fimPiscada = agora + 150;                       // fica fechado por 150 ms
    desenharRosto(expressaoAtual, true);
  } else if (piscando && agora >= fimPiscada) {
    // acabou a piscada: abre os olhos
    piscando = false;
    proximaPiscada = agora + random(2000, 5000);    // próxima piscada em 2 a 5 s
    desenharRosto(expressaoAtual, false);
  }
}

// ---------- 6. TROCA DE EXPRESSÃO ----------
void atualizarExpressao() {
  unsigned long agora = millis();

  if (agora >= proximaTroca) {
    // avança para a próxima expressão da lista (e volta ao começo no fim)
    expressaoAtual = (Expressao)((expressaoAtual + 1) % 3);

    piscando = false;
    proximaPiscada = agora + 2000;                  // dá um tempo antes da 1ª piscada
    proximaTroca = agora + TEMPO_EXPRESSAO;
    desenharRosto(expressaoAtual, false);
  }
}

// ---------- SETUP: roda UMA vez ----------
void setup() {
  Wire.begin(PIN_SDA, PIN_SCL);   // inicia o I2C nos nossos pinos

  // 0x3C é o "endereço" da tela no I2C
  if (!tela.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) delay(1000);     // se a tela não responder, para aqui
  }

  randomSeed(micros());           // faz o "aleatório" mudar a cada execução

  proximaPiscada = millis() + 2000;
  proximaTroca   = millis() + TEMPO_EXPRESSAO;
  desenharRosto(expressaoAtual, false);
}

// ---------- LOOP: roda para sempre ----------
void loop() {
  atualizarExpressao();   // vê se é hora de trocar de expressão
  atualizarPiscada();     // vê se é hora de piscar
}
