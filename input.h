#ifndef INPUT_H
#define INPUT_H


#define BTN1_PIN  12
#define BTN2_PIN  16
#define BTN3_PIN  20
#define BTN4_PIN  21

void input_init();
void input_with_button(unsigned int *arrayPointer);
void button1_pressed();
void button2_pressed();
void button3_pressed();
void button4_pressed();
void input_clear();
unsigned int get_plain_int();
void parseToFnd(unsigned int *fndData, unsigned int password);

#endif // INPUT_H