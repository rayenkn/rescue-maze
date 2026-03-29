#ifndef DFS_H
#define DFS_H

#include <Arduino.h>


struct Tile {
    bool visited = false; 
};


extern Tile maze[40][40];


extern int currentX;
extern int currentY;
extern int heading; 


extern int stackX[1600];
extern int stackY[1600];
extern int stackTop;


void iniitDfs();
void CalcMove();
void backtrack();


#endif