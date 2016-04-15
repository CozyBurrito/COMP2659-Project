#ifndef ISR_H
#define ISR_H
#include "globals.h"

void do_kbd_isr();
Vector install_vector(int num, Vector vector);

void do_VBL_ISR();

#endif