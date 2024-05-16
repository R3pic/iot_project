// password.h

#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdbool.h>

// 전역 변수 선언
extern bool isHuman;

// 함수 선언
void checkhuman();
void input_password(unsigned int *password);
void getFndData(unsigned int *data1, unsigned int *data2);

#endif // PASSWORD_H
