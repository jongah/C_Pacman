#include "main.h"

#ifndef _KEY_a
#define _KEY_

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define PICK 4

#endif

int keyControl();
void titleText();
int menuSet();
void menuPick();
void mapSet();
void move();
void wayCheck(struct creature *c);
int xyPick(struct creature *c);
int gostCheck(struct creature *c);
int gostWay(int y, int x);