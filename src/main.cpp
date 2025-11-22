#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <VectorXf.h>

#include "MPU6500_Raw.h"
MPU6500 mpu;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET, 2000000, 400000);

#define FEUP_LOGO_WIDTH 128
#define FEUP_LOGO_HEIGHT 64

const unsigned char epd_bitmap_feup1234 [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x03, 0x00, 0xfc, 0x0f, 0x00, 0x70, 0x01, 0xe0, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xce, 0x39, 0xe7, 0xce, 0x33, 0x1d, 0xcf, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xcf, 0x31, 0xf3, 0xce, 0x37, 0x1d, 0x9f, 0x9f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xcf, 0x33, 0xf1, 0xcf, 0x37, 0x1d, 0x9f, 0x9f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xcf, 0x33, 0xf1, 0xce, 0x3f, 0x1f, 0x1f, 0x8f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xce, 0x23, 0xf1, 0xce, 0x7f, 0x1f, 0x1f, 0x8f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xc4, 0x63, 0xf9, 0xc0, 0xff, 0x1f, 0x1f, 0x8f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xc1, 0xe3, 0xf1, 0xce, 0x7f, 0x1f, 0x1f, 0x8f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xcf, 0xf3, 0xf1, 0xce, 0x3f, 0x1f, 0x1f, 0x8f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xcf, 0xf3, 0xf1, 0xce, 0x3f, 0x1f, 0x9f, 0x9f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x83, 0x00, 0x03, 0xcf, 0xf1, 0xf3, 0xce, 0x3f, 0x1f, 0x9f, 0x9f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x81, 0x80, 0x23, 0xcf, 0xf9, 0xe7, 0xce, 0x3f, 0x1f, 0xcf, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0xc0, 0x23, 0x07, 0xfc, 0x0f, 0x07, 0x1e, 0x0f, 0xe0, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x3f, 0x9a, 0x66, 0x6c, 0xbd, 0xaf, 0xfc, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x0f, 0x43, 0xc8, 0x01, 0x02, 0x04, 0x0c, 0x00, 0x00, 0xa0, 0x0f, 0xff, 0xff, 
	0xff, 0xff, 0x9c, 0xef, 0x59, 0xc0, 0x41, 0x20, 0x84, 0x8c, 0x82, 0x20, 0x00, 0x07, 0xff, 0xff, 
	0xff, 0xff, 0x9c, 0xef, 0x59, 0xd0, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x80, 0x07, 0xff, 0xff, 
	0xff, 0xff, 0x84, 0x2f, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x9c, 0xef, 0x43, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x9d, 0xee, 0x5f, 0xff, 0xfc, 0xb7, 0x34, 0xcc, 0xce, 0xc9, 0x27, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x9c, 0x20, 0xdf, 0xd0, 0x01, 0x04, 0x04, 0x18, 0x04, 0x20, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x39, 0xdf, 0xd0, 0x25, 0x10, 0x41, 0x19, 0x34, 0x21, 0x5b, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc2, 0x24, 0x00, 0x08, 0x0c, 0x0d, 0x81, 0x63, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xfd, 0xf7, 0x7e, 0xdd, 0xdf, 0xdf, 0xf7, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define Sok_pin 2 // GPIO 2 but Pin 4
#define Snext_pin 3 // GPIO 3 but Pin 5
#define Sesc_pin 4 // GPIO 4 but Pin 6
#define MY_LOGO_WIDTH 128
#define MY_LOGO_HEIGHT 64

void showSplashScreen() {
  display.clearDisplay();
  display.drawBitmap(
    (display.width() - FEUP_LOGO_WIDTH) / 2,
    (display.height() - FEUP_LOGO_HEIGHT) / 2,
    epd_bitmap_feup1234,
    FEUP_LOGO_WIDTH,
    FEUP_LOGO_HEIGHT,
    SSD1306_WHITE
  );
  display.display();
  delay(3000);
  display.clearDisplay();
}

// --- Menu do desenho---
const char* menuItems[] = {"Dados do IMU","Calib. Acel-Gyro", "Num. de Dados", "Num. de faces", "Tempo a rodar"};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
int menuIndex = 0;   // índice da opção atual
int menuPage = 0;    // 0 = menu principal, 1..n = submenus
int diceRange = 6;  // tipo de dado (4, 6, 10, 20)
int nDice = 1;      // número de dados
int spinTime = 3;   // tempo de spin em segundos

// ---- shake globals (uma só definição) ----
int shakeCount = 0;                // antigo contador de picos positivos (reutilizado)
unsigned long lastShakeTime = 0;   // tempo do último pico (qualquer)
bool calibratedDone = false;
int diceResults[4]; // resultado final (até 4 dados)

uint8_t Sok = 0, prevSok = 0;
uint8_t Snext = 0, prevSnext = 0;
uint8_t Sesc = 0, prevSesc = 0;

static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

uint32_t interval = 0, last_cycle = 0;
uint32_t loop_micros = 0;
uint32_t cycle_count = 0;

typedef struct {
  int state, new_state;
  unsigned long tes, tis;
} fsm_t;

// Creating my State Machines and variables
fsm_t fsm1; // Sok button long-press
fsm_t fsm2; // OLED on/off
fsm_t fsm3; // Sesc button long-press
fsm_t fsm4; // Menu navigation
fsm_t fsm5; // Calibration FSM
fsm_t fsm6; // Shake -> roll FSM

// Defining meaningful names for the states of fsm
enum 
{ 
  sm1_off = 0, 
  sm1_on 
};
enum
 { 
  sm2_off = 0, 
  sm2_on 
};
enum 
{ 
  sm3_off = 0, 
  sm3_on 
};

enum { 
  rest = 0, down, 
  up, sellect, rest_select 
};

enum { 
  Stop = 0, mensagem_ini, 
  cal_colect, cal_finish 
};

enum { 
  dice_idle = 0, dice_detecting, 
  dice_launching, dice_showing 
};

// calibration accumulators (persistentes)
float cal_wx = 0, cal_wy = 0, cal_wz = 0;
float cal_ax = 0, cal_ay = 0, cal_az = 0;

// --- Variáveis globais para os offsets ---
float gyroBias[3] = {0, 0, 0};
float accelBias[3] = {0, 0, 0};

// other globals used by calibration
int contador = 0;
const int samples = 200;

// Detecção front-back (variáveis específicas)
int forwardCount = 0;                  // conta picos "frente" válidos (positivo)
int lastDetectedSign = 0;              // -1 = last was negative, 0 = none, 1 = last positive
unsigned long lastPeakTime = 0;        // tempo do último pico (positivo ou negativo)
const float FORWARD_THRESHOLD = 0.6f;  // ajustar conforme força real (em g) - positivo
const float BACK_THRESHOLD = -0.6f;    // negativo
const unsigned long PEAK_DEBOUNCE_MS = 200; // evitar múltiplos triggers no mesmo pico
const unsigned long SEQUENCE_TIMEOUT_MS = 2000; // timeout para reset da contagem

// prevent menu redraw during roll/show
bool inRollingAnimation = false;

// Defining my functions
void set_state(fsm_t& fsm, int new_state) {
  if (fsm.state != new_state) {
    fsm.state = new_state;
    fsm.tes = millis();
    fsm.tis = 0;
  }
}

void set_interval(float new_interval) {
  interval = (uint32_t)(new_interval * 1000000L);   // In microseconds
}

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Cada item ocupa 12 px de altura → 5 itens = 60 px → cabe bem no 64px de altura
  for (int i = 0; i < menuLength; i++) {
    int y = i * 12;  // espaçamento vertical
    if (i == menuIndex) {
      // Fundo branco para o item selecionado
      display.fillRect(0, y, 128, 12, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    }

    display.setCursor(4, y + 2);
    display.print(menuItems[i]);
  }

  display.display();
}
void drawDiceFace(int x, int y, int size, int value, int range) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (range == 4) {
    // D4 - pirâmide triangular
    int h = size;
    int cx = x + size / 2;
    display.drawLine(cx, y, x, y + h, SSD1306_WHITE);
    display.drawLine(cx, y, x + size, y + h, SSD1306_WHITE);
    display.drawLine(x, y + h, x + size, y + h, SSD1306_WHITE);
    display.setCursor(cx - 3, y + h / 2 - 2);
    display.printf("%d", value);
  }

  else if (range == 6) {
    // D6 - cubo com pontos clássicos
    display.drawRect(x, y, size, size, SSD1306_WHITE);
    int cx = x + size / 2;
    int cy = y + size / 2;
    int offset = size / 4;

    // desenhar pontos consoante o valor
    switch (value) {
      case 1:
        display.fillCircle(cx, cy, 2, SSD1306_WHITE);
        break;
      case 2:
        display.fillCircle(x + offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + size - offset, 2, SSD1306_WHITE);
        break;
      case 3:
        display.fillCircle(x + offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(cx, cy, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + size - offset, 2, SSD1306_WHITE);
        break;
      case 4:
        display.fillCircle(x + offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + offset, y + size - offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + size - offset, 2, SSD1306_WHITE);
        break;
      case 5:
        display.fillCircle(x + offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + offset, y + size - offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + size - offset, 2, SSD1306_WHITE);
        display.fillCircle(cx, cy, 2, SSD1306_WHITE);
        break;
      case 6:
        display.fillCircle(x + offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + offset, cy, 2, SSD1306_WHITE);
        display.fillCircle(x + offset, y + size - offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + offset, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, cy, 2, SSD1306_WHITE);
        display.fillCircle(x + size - offset, y + size - offset, 2, SSD1306_WHITE);
        break;
    }
  }

  else if (range == 10) {
  // D10 - losango com base ligeiramente achatada
  int w = size;           // largura total
  int h = size * 0.9;     // altura total
  int cx = x + w / 2;
  int cy = y + h / 2;

  // proporções do losango
  int topY = y;
  int midY = cy;
  int bottomY = y + h;
  int leftX = x;
  int rightX = x + w;

  // Ajustar a base para ser mais "curta" (achatada/bicuda)
  int bottomOffset = h * 0.2; // quão mais curta fica a base
  int bottomYAdj = bottomY - bottomOffset;

  // Desenhar contorno
  display.drawLine(cx, topY, rightX, midY, SSD1306_WHITE);       // lado superior direito
  display.drawLine(rightX, midY, cx, bottomYAdj, SSD1306_WHITE); // lado inferior direito
  display.drawLine(cx, bottomYAdj, leftX, midY, SSD1306_WHITE);  // lado inferior esquerdo
  display.drawLine(leftX, midY, cx, topY, SSD1306_WHITE);        // lado superior esquerdo

  // Número centrado na face
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  int16_t x1, y1;
  uint16_t wText, hText;
  char buf[8];
  sprintf(buf, "%d", value);
  display.getTextBounds(buf, 0, 0, &x1, &y1, &wText, &hText);
  display.setCursor(cx - wText / 2, cy - hText / 2);
  display.print(buf);
}

else if (range == 20) {
  // D20 - hexágono alongado
  int h = size / 2;
  int cx = x + size / 2;
  int cy = y + size / 2;

  // Contorno
  display.drawLine(cx - size / 2, cy, cx - size / 3, cy - h, SSD1306_WHITE);
  display.drawLine(cx - size / 3, cy - h, cx + size / 3, cy - h, SSD1306_WHITE);
  display.drawLine(cx + size / 3, cy - h, cx + size / 2, cy, SSD1306_WHITE);
  display.drawLine(cx + size / 2, cy, cx + size / 3, cy + h, SSD1306_WHITE);
  display.drawLine(cx + size / 3, cy + h, cx - size / 3, cy + h, SSD1306_WHITE);
  display.drawLine(cx - size / 3, cy + h, cx - size / 2, cy, SSD1306_WHITE);

  // Número centrado
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  char buf[8];
  sprintf(buf, "%d", value);

  int16_t x1, y1;
  uint16_t wText, hText;
  display.getTextBounds(buf, 0, 0, &x1, &y1, &wText, &hText);

  // centra horizontal e verticalmente no hexágono
  display.setCursor(cx - wText / 2, cy - hText / 2);
  display.print(buf);
}

  else {
    // fallback genérico
    display.drawRect(x, y, size, size, SSD1306_WHITE);
    display.setCursor(x + size / 2 - 3, y + size / 2 - 3);
    display.printf("%d", value);
  }
}




void rollDiceAnimationAndResults() {
  inRollingAnimation = true;

  int numToRoll = constrain(nDice, 1, 4);
  unsigned long spinStart = millis();

  while (millis() - spinStart < (unsigned long)spinTime * 1000UL) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("A rodar...");

    int spacing = 30;
    int size = 20;
    int baseX = (SCREEN_WIDTH - (numToRoll * spacing)) / 2;
    int baseY = 20;

    // efeito de tremor (shake)
    int shakeX = random(-2, 3);
    int shakeY = random(-2, 3);

    for (int i = 0; i < numToRoll; i++) {
      int r = random(1, diceRange + 1);
      int dx = baseX + i * spacing + random(-1, 2) + shakeX;
      int dy = baseY + random(-1, 2) + shakeY;
      drawDiceFace(dx, dy, size, r, diceRange);
    }

    display.display();
    delay(120);
  }

  // gera resultados finais
  for (int i = 0; i < numToRoll; i++) {
    diceResults[i] = random(1, diceRange + 1);
  }

  // mostrar resultados finais
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Resultado:");

  int spacing = 30;
  int size = 20;
  int startX = (SCREEN_WIDTH - (numToRoll * spacing)) / 2;
  int y = 20;

  for (int i = 0; i < numToRoll; i++) {
    drawDiceFace(startX + i * spacing, y, size, diceResults[i], diceRange);
  }

  int total = 0;
  for (int i = 0; i < numToRoll; i++) total += diceResults[i];

  // total centrado em baixo
  String totalStr = "Total: " + String(total);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(totalStr, 0, 0, &x1, &y1, &w, &h);
  int totalX = (SCREEN_WIDTH - w) / 2;
  display.setCursor(totalX, 54);
  display.print(totalStr);

  display.display();
  Serial.printf("Total: %d\n", total);
}



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  pinMode(Sok_pin, INPUT_PULLUP);
  pinMode(Snext_pin, INPUT_PULLUP);
  pinMode(Sesc_pin, INPUT_PULLUP);

  // inicializar FSMs
  set_state(fsm1, sm1_off);
  set_state(fsm2, sm2_off);
  set_state(fsm3, sm3_off);
  set_state(fsm4, rest);
  set_state(fsm5, Stop);
  set_state(fsm6, dice_idle);

  randomSeed(analogRead(A0));

  set_interval(50e-3); // 100 ms -> 100 Hz

  // IMU
  const int I2C0_SDA = 20;
  const int I2C0_SCL = 21;
  pinMode(I2C0_SDA, INPUT_PULLUP);
  pinMode(I2C0_SCL, INPUT_PULLUP);
  Wire.setSDA(I2C0_SDA);
  Wire.setSCL(I2C0_SCL);
  Wire.begin();
  delay(20);

  MPU6500Setting setting;
  setting.accel_fs_sel = ACCEL_FS_SEL::A16G;
  setting.gyro_fs_sel = GYRO_FS_SEL::G2000DPS;
  setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
  setting.gyro_fchoice = 0x03;
  setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
  setting.accel_fchoice = 0x01;
  setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;

  while (!mpu.setup(0x68, setting)) {
    Serial.println("MPU connection failed.");
    delay(500);
  }

  // OLED
  const int I2C1_SDA = 18;
  const int I2C1_SCL = 19;
  pinMode(I2C1_SDA, INPUT_PULLUP);
  pinMode(I2C1_SCL, INPUT_PULLUP);
  Wire1.setSDA(I2C1_SDA);
  Wire1.setSCL(I2C1_SCL);
  Wire1.begin();

  while(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    delay(500);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

typedef struct {
  Vec3f w;
  Vec3f a;
  uint32_t cycle_time, last_cycle_time;
} imu_values_t;
imu_values_t imu;

void loop() {
  uint8_t b;
  if (Serial.available()) {
    b = Serial.read();
  }

  uint32_t now = micros();
  uint32_t delta = now - last_cycle;
  if (delta >= interval) {
    loop_micros = micros();
    last_cycle = now;
    cycle_count++;

    // ------------------------
    // Read MPU raw values first (do NOT subtract biases here)
    // ------------------------
    float raw_gx = 0, raw_gy = 0, raw_gz = 0;
    float raw_ax = 0, raw_ay = 0, raw_az = 0;
    if (mpu.update()) {
      imu.last_cycle_time = imu.cycle_time;
      imu.cycle_time = micros();

      // raw readings from mpu
      raw_gx = mpu.getGyroX();
      raw_gy = mpu.getGyroY();
      raw_gz = mpu.getGyroZ();

      raw_ax = mpu.getAccX();
      raw_ay = mpu.getAccY();
      raw_az = mpu.getAccZ();

      // apply bias ONLY if calibration already done
      if (calibratedDone) {
        imu.w.x = raw_gx - gyroBias[0];
        imu.w.y = raw_gy - gyroBias[1];
        imu.w.z = raw_gz - gyroBias[2];

        imu.a.x = raw_ax - accelBias[0];
        imu.a.y = raw_ay - accelBias[1];
        imu.a.z = raw_az - accelBias[2];
      } else {
        // before calibration, keep raw values intact (so accumulators use raw)
        imu.w.x = raw_gx;
        imu.w.y = raw_gy;
        imu.w.z = raw_gz;

        imu.a.x = raw_ax;
        imu.a.y = raw_ay;
        imu.a.z = raw_az;
      }
    }

    // Read buttons 
    prevSok = Sok;
    Sok = !digitalRead(Sok_pin);

    prevSnext = Snext;
    Snext = !digitalRead(Snext_pin);

    prevSesc = Sesc;
    Sesc = !digitalRead(Sesc_pin);

    // Update tis for fsm1 and fsm2
    uint32_t cur_time = millis();
    fsm1.tis = cur_time - fsm1.tes;
    fsm2.tis = cur_time - fsm2.tes;

    // fsm1: Sok long-press detection
    if (fsm1.state == sm1_off && Sok) {
      fsm1.new_state = sm1_on;
    } else if (fsm1.state == sm1_on && !Sok) {
      fsm1.new_state = sm1_off;
    }

    // fsm3: Sesc long-press detection
    if (fsm3.state == sm3_off && Sesc) {
      fsm3.new_state = sm3_on;
    } else if (fsm3.state == sm3_on && !Sesc) {
      fsm3.new_state = sm3_off;
    }

    // fsm2: OLED on logic based on long press
    if (fsm2.state == sm2_off && fsm1.state == sm1_on && fsm1.tis > 2000) {
      fsm2.new_state = sm2_on;
      fsm1.new_state = sm1_off;
      //Mostrar logotipo da FEUP ao ligar o ecrã
      showSplashScreen();

      /*menuPage = 0;
      drawMenu();*/
    }

    // Menu navigation FSM (fsm4)
    if (fsm4.state == rest && Snext && !prevSnext && !Sesc) {
      fsm4.new_state = down;
    } else if (fsm4.state == rest && !Snext && Sesc && !prevSesc) {
      fsm4.new_state = up;
    } else if (fsm4.state == rest && Sok && !prevSok && !Snext && !Sesc) {
      fsm4.new_state = sellect;
    }

    if (fsm4.state == down && !Snext && Sesc && !prevSesc) {
      fsm4.new_state = up;
    } else if (fsm4.state == down && !Snext && !Sesc) {
      fsm4.new_state = rest;
    }

    if (fsm4.state == up && Snext && !prevSnext && !Sesc) {
      fsm4.new_state = down;
    } else if (fsm4.state == up && !Snext && !Sesc) {
      fsm4.new_state = rest;
    }

    if (fsm4.state == sellect && !Sok) {
      fsm4.new_state = rest_select;
    }
    if (fsm4.state == rest_select && Sesc) {
      fsm4.new_state = rest;
    }

    // Transições na Calibração (fsm5)
    if (fsm5.state == mensagem_ini) {
      fsm5.new_state = cal_colect;
    }
    if (fsm5.state == cal_colect && contador == samples) {
      fsm5.new_state = cal_finish;
    } else if (fsm5.state == cal_colect) {
      // contador incrementa quando estamos a recolher (realizado mais abaixo)
    }
    if (fsm5.state == cal_finish) {
      contador = 0;
      fsm5.new_state = Stop;
    }

    // actualizar fsm1..fsm5 antes das transições de FSM6 
    set_state(fsm1, fsm1.new_state);
    set_state(fsm2, fsm2.new_state);
    set_state(fsm3, fsm3.new_state);
    set_state(fsm4, fsm4.new_state);
    set_state(fsm5, fsm5.new_state);

    // ------------------------------
    // FSM6 (frente-trás detection -> roll)
    // ------------------------------
    fsm6.tis = millis() - fsm6.tes;

    // Usamos o eixo X como "frente/trás" (ajusta para .y ou .z se necessário)
    float axisX = imu.a.x; // raw or bias-corrected depending on calibratedDone

    // Detect peaks: positivo = frente, negativo = trás
    unsigned long nowMs = millis();

    // Se timeout excedido, reset da contagem
    if (nowMs - lastPeakTime > SEQUENCE_TIMEOUT_MS) {
      forwardCount = 0;
      lastDetectedSign = 0;
    }

    // detect positive (forward) peak
    if (axisX > FORWARD_THRESHOLD) {
      if (nowMs - lastPeakTime > PEAK_DEBOUNCE_MS) {
        // apenas conta um pico positivo se o último sido negativo (alternância)
        if (lastDetectedSign <= 0) {
          forwardCount++;
          lastDetectedSign = 1;
          lastPeakTime = nowMs;
          Serial.printf("Forward peak #%d detected (axisX=%.2f)\n", forwardCount, axisX);
        }
      }
    }
    // detect negative (back) peak
    else if (axisX < BACK_THRESHOLD) {
      if (nowMs - lastPeakTime > PEAK_DEBOUNCE_MS) {
        // atualiza sinal mas não incrementa forwardCount
        if (lastDetectedSign >= 0) {
          lastDetectedSign = -1;
          lastPeakTime = nowMs;
          Serial.printf("Back peak detected (axisX=%.2f)\n", axisX);
        }
      }
    }

    // transições da FSM6 com base no forwardCount
    if (fsm6.state == dice_idle) {
      // Só detecta no menu principal e com ecrã ligado and after calibration done
      if (fsm2.state == sm2_on && menuPage == 0 && calibratedDone) {
        if (forwardCount >= 1 && lastDetectedSign == 1) {
          // comecei a contar, passo para detecting para gerir timeout etc.
          fsm6.new_state = dice_detecting;
          // não zera forwardCount aqui (mantemos)
        }
      }
    }
    else if (fsm6.state == dice_detecting) {
      // Se atingimos 3 forwards alternados com backs -> lançamento
      if (forwardCount >= 3) {
        Serial.println("3 abanos (frente-trás) detetados -> launching");
        forwardCount = 0;
        lastDetectedSign = 0;
        fsm6.new_state = dice_launching;
      }
      // timeout para cancel
      else if (nowMs - lastPeakTime > SEQUENCE_TIMEOUT_MS) {
        forwardCount = 0;
        lastDetectedSign = 0;
        fsm6.new_state = dice_idle;
      }
      // caso contrário permanecemos detecting até completarmos
    }
    else if (fsm6.state == dice_launching) {
      // entramos aqui imediatamente quando new_state foi set; executar animação e resultados
      rollDiceAnimationAndResults(); // sets inRollingAnimation = true internally
      fsm6.new_state = dice_showing;
    }
    else if (fsm6.state == dice_showing) {
      // mostra resultados finais (rollDiceAnimationAndResults já desenhou resultados)
      // aguarda Sesc para voltar ao menu
      if (Sesc && !prevSesc) {
        forwardCount = 0;
        lastDetectedSign = 0;
        fsm6.new_state = dice_idle;
        menuPage = 0;
        inRollingAnimation = false; // libera o menu para redesenhar
      }
    }

    // commit fsm6 state
    set_state(fsm6, fsm6.new_state);

    // --- Ações do menu --- //
    // só redesenha o menu se não estivermos numa animação de roll/show
    if (!inRollingAnimation) {
      if (fsm4.state == down ) {
        menuIndex++;
        if (menuIndex >= menuLength) menuIndex = 0;
      }

      if (fsm4.state == up ) {
        menuIndex--;
        if (menuIndex < 0) menuIndex = menuLength - 1;
      }

      if (fsm4.state == rest_select && fsm4.tis < 100) {
        menuPage = menuIndex + 1; // entra na página correspondente
      }
    }

    // ----- CALIBRATION ACTIONS (fsm5) -----
    if (fsm5.state == mensagem_ini) {
      // show initial message once
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.print("A calibrar...");
      display.setCursor(0, 10);
      display.print("Mantenha o IMU imobilizado.");
      display.display();

      // prepare accumulators (use RAW mpu.get... values)
      cal_wx = cal_wy = cal_wz = 0;
      cal_ax = cal_ay = cal_az = 0;
      contador = 0;
      fsm5.new_state = cal_colect;
    }
    else if (fsm5.state == cal_colect) {
      // collect samples using raw readings (imu holds raw if calibratedDone==false)
      // We must use the raw MPU values (not imu after bias subtraction), but above we preserved raw into imu when not calibrated
      // usa valores crus diretamente do mpu
      cal_wx += mpu.getGyroX();
      cal_wy += mpu.getGyroY();
      cal_wz += mpu.getGyroZ();
      cal_ax += mpu.getAccX();
      cal_ay += mpu.getAccY();
      cal_az += mpu.getAccZ();
      contador++;

      display.setCursor(0, 24);
      display.printf("Amostra %d de %d", contador, samples);
      display.display();

      if (contador >= samples) {
        fsm5.new_state = cal_finish;
      }
    }
    else if (fsm5.state == cal_finish) {
      // compute biases using accumulated sums
      gyroBias[0] = cal_wx / (float)contador;
      gyroBias[1] = cal_wy / (float)contador;
      gyroBias[2] = cal_wz / (float)contador;

      accelBias[0] = cal_ax / (float)contador;
      accelBias[1] = cal_ay / (float)contador;
      accelBias[2] = (cal_az / (float)contador) - 1.0f; // Az ~ 1g at rest

      // show results
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.print("Calibrado!");
      display.setCursor(0, 10);
      display.print("Gyro:");
      display.setCursor(0, 20);
      display.printf("Wx:%.2f Wy:%.2f Wz:%.2f", mpu.getGyroX() - gyroBias[0], mpu.getGyroY() - gyroBias[1], mpu.getGyroZ() - gyroBias[2]);
      display.setCursor(0, 35);
      display.print("Acc:");
      display.setCursor(0, 45);
      display.printf("Ax:%.2f Ay:%.2f Az:%.2f", mpu.getAccX() - accelBias[0], mpu.getAccY() - accelBias[1], mpu.getAccZ() - accelBias[2]);
      display.display();

      delay(2500);

      // return to main menu, ensure fsm6 idle
      menuPage = 0;
      fsm5.new_state = Stop;
      fsm6.new_state = dice_idle;
      // reset accumulators
      cal_wx = cal_wy = cal_wz = 0;
      cal_ax = cal_ay = cal_az = 0;
      contador = 0;

      // mark calibrated
      calibratedDone = true;
    }

    // -- DISPLAY PAGES --
    if (fsm2.state == sm2_on) {

      // Página principal do menu
      if (menuPage == 0) {
        if (!inRollingAnimation) drawMenu();
        // if inRollingAnimation, keep the animation/results on screen
      }
      // Página 1: IMU Data
      else if (menuPage == 1) {
        if (!inRollingAnimation) {
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(0, 0);
          display.printf("Wx: %.2f\n", imu.w.x);
          display.printf("Wy: %.2f\n", imu.w.y);
          display.printf("Wz: %.2f\n", imu.w.z);
          display.setCursor(64, 0);
          display.printf("Ax: %.2f", imu.a.x);
          display.setCursor(64, 8);
          display.printf("Ay: %.2f", imu.a.y);
          display.setCursor(64, 16);
          display.printf("Az: %.2f", imu.a.z);
          display.display();
        }
      }
      // Página 2: Calibração
      else if (menuPage == 2) {
        if (!inRollingAnimation) {
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SSD1306_WHITE);

          if (fsm5.state == Stop) {
            display.setCursor(0, 0);
            display.print("Calib. Acel-Gyro");
            display.setCursor(0, 12);
            display.print("Press. OK p/iniciar");
            display.display();

            if (Sok && !prevSok) {
              set_state(fsm5, mensagem_ini);
            }
          } else if (fsm5.state == mensagem_ini || fsm5.state == cal_colect) {
            // showing happens in the fsm5 actions above (progress)
          } else if (fsm5.state == cal_finish) {
            // already handled above
          }
        }
      }

      // Página 3: Numero de Dados
      else if (menuPage == 3) {
        if (!inRollingAnimation) {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Numero de dados:");
          display.setCursor(0, 12);
          display.printf("< %d >", nDice);
          display.display();

          if (Snext && !prevSnext) {
            nDice++;
            if (nDice > 4) nDice = 1;
          }
        }
      }

      // Página 4: Dice Range
      else if (menuPage == 4) {
        if (!inRollingAnimation) {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Tipo de dado:");
          display.setCursor(0, 12);
          display.printf("< D%d >", diceRange);
          display.display();

          if (Snext && !prevSnext) {
            if (diceRange == 4) diceRange = 6;
            else if (diceRange == 6) diceRange = 10;
            else if (diceRange == 10) diceRange = 20;
            else diceRange = 4;
          }

        }
      }

      // Página 5: Tempo de spin
      else if (menuPage == 5) {
        if (!inRollingAnimation) {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Tempo a rodar:");
          display.setCursor(0, 12);
          display.printf("< %d s >", spinTime);
          display.display();

          if (Snext && !prevSnext) {
            spinTime++;
            if (spinTime > 10) spinTime = 2;
          }
          
        }
      }

      // Botão de voltar (edge)
      if (!inRollingAnimation && Sesc && menuPage != 0 && !prevSesc) {
        menuPage = 0;
      }
    }
    else if (fsm2.state == sm2_off) {
      display.clearDisplay();
      display.display();
    }

    // Serial debug (optional)
    Serial.printf("Sok %d; Snext %d; Sesc %d; fsm1:%d fsm2:%d fsm3:%d fsm4:%d fsm5:%d fsm6:%d cal:%d\n",
      Sok, Snext, Sesc, fsm1.state, fsm2.state, fsm3.state, fsm4.state, fsm5.state, fsm6.state, calibratedDone ? 1 : 0);

  } // end if (delta >= interval)
} // end loop