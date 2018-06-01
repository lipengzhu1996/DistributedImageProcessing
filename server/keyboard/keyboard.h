#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "config.h"

int keyboard_init(void);
int keyboard_detect(int keyboard_fd);
void keyboard_proc(int code);

#endif // KEYBOARD_H_INCLUDED
