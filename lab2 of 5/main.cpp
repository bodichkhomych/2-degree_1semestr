#include <conio.h>
#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;

int main(){
float x,y,dx,dy;
int x1,y1,x2,y2,i,length, color;
float d = 500;
initwindow(d, d);
setfillstyle(1, WHITE);
bar(0, 0, d, d);
cout<<"Enter co-ordinates of point 1(0 to "<< d <<"):  ";
cin>>x1>>y1;
cout<<"Enter co-ordinates of point 2(0 to "<< d <<"): ";
cin>>x2>>y2;
cout<< "Choose the color (1-Black, 2-Red, 3-Blue): ";
cin>> color;
switch (color){
case 1 : color = BLACK;
break;
case 2 : color = RED;
break;
case 3 : color = BLUE;
break;
}
dx = abs(x2-x1);
dy = abs(y2-y1);
if(dx>=dy) length = dx;
else length = dy;
dx = dx/length;
dy = dy/length;
x=x1;
y=y1;
i=1;
while(i<=length){
putpixel(x,y, color);
x = x + dx;
y = y + dy;
i++;
}
getch();
}

