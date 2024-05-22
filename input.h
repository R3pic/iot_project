#ifndef INPUT_H
#define INPUT_H

// Button pins
#define BTN1_PIN 12
#define BTN2_PIN 16
#define BTN3_PIN 20
#define BTN4_PIN 21

#define BOUNCE_TIME 100

unsigned long lastInterruptTime;

void input_init();
void check_buttons();
void button1_pressed();
void button2_pressed();
void button3_pressed();
void button4_pressed();
void input_clear();
int get_plain_int();
void parseToFnd(unsigned int *fndData);

#endif // INPUT_H