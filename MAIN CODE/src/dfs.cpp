#include "dfs.h"
#include "navigation.h"
#include "PID_40cm.h"
#include "TOF.h"
Tile maze[40][40];
int currentX=20;
int currentY=20;
int heading=0; //1=GODAM 2=YMIN 3=LTELI 4=YSAR
int stackX[1600];
int stackY[1600];
int stackTop=-1;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};

void iniitDfs(){
    maze[currentX][currentY].visited=true;
}
void backtrack(){
    if(stackTop<0){
        //stopmotors;
        while(1);

    }
    int targetX=stackX[stackTop];
    int targetY=stackY[stackTop];
    stackTop--;

    int backheading=-1;
    for(int i; i<4 ;i++){
        if(currentX +dx[i]==targetX && currentY + dy[i]==targetY){
            backheading=i;
            break;
        }
    }
    int diff=(backheading-heading +4)%4;
    if(diff==1) turnRight();
    else if(diff==2) turnAround();
    else if(diff==3) turnLeft();

    currentX=targetX;
    currentY=targetY;
    heading=backheading;


}
void CalcMove(){
maze[currentX][currentY].visited=true;

int leftDr=(heading+3)%4;
int rightDr=(heading+1)%4;

int fx=currentX + dx[heading]; int fy=currentY + dy[heading];
int Lx=currentX + dx[heading]; int Ly=currentY + dy[heading];
int Rx=currentX + dx[heading]; int Ry=currentY + dy[heading]; 

if(distLeft>30 && !maze[Lx][Ly].visited){
    stackTop++;
    stackX[stackTop]=currentX;
    stackY[stackTop]=currentY;

    currentX=Lx;
    currentY=Ly;
    heading=leftDr;

    turnLeft();
}
else if(distRight>30 && !maze[Rx][Ry].visited){
    stackTop++;
    stackX[stackTop]=currentX;
    stackY[stackTop]=currentY;

    currentX=Rx;
    currentY=Ry;
    heading=rightDr;                                                                  

    turnRight();
}
else if(distFront>30 && !maze[fx][fy].visited){
    stackTop++;
    stackX[stackTop]=currentX;
    stackY[stackTop]=currentY;

    currentX=fx;
    currentY=fx;

    error1 = 9 - distLeft;
    integral1 += error1 * dt;
    integral1 = constrain(integral1, -100, 100);
    Xderivative1 = (error1 - lasterror1) / dt;
    Yderivative1 = filter * Xderivative1 + (1 - filter) * Yderivative1;
    correction1  = (error1 * Kp1) + (integral1 * Ki1) + (Yderivative1 * Kd1);
    lasterror1   = error1;

    error2 = 9 - distRight;
    integral2 += error2 * dt;
    integral2 = constrain(integral2, -100, 100);
    Xderivative2 = (error2 - lasterror2) / dt;
    Yderivative2 = filter * Xderivative2 + (1 - filter) * Yderivative2;
    correction2  = (error2 * Kp2) + (integral2 * Ki2) + (Yderivative2 * Kd2);
    lasterror2   = error2;
}
else backtrack();

}