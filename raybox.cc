#include "raybox.h"
#include <cmath>
#include <stdexcept>

double tracebox(box &b){

  const double pi = 3.14159265359;

  // Save old values of x and y
  double oldx = b.x, oldy = b.y;
  
  // Calc. various quantities
  double dX1 = b.x1-b.x; // x dist from upper right corner
  double dY0 = b.y0-b.y; // y dist from lower left corner
  double dY1 = b.y1-b.y; // y dist from upper right corner
  double rightHitPointY = tan(b.angle)*dX1+b.y;

  // Check bounds
  if(b.x<b.x0||b.y<b.y0||b.x1<b.x||b.y1<b.y){
    throw std::domain_error("Ray is not inside box!");
  }
  if(-pi/2>b.angle||pi/2<b.angle){
    throw std::domain_error("Angle is not in range!");
  }

  // will the ray hit the right wall within box??
  if(b.y0<rightHitPointY&&rightHitPointY<b.y1){
    b.ix++; // apparently yes, so lets increment the x index of the box
    b.x = b.x1; // x coord of hitpoint on right wall
    b.y = rightHitPointY; // y coord of hitpoint on right wall
  }
  else{ // it did not hit right wall, so either it hits upper or lower wall

    if(b.angle>0){ // hit upper
      b.iy++;
      b.x = tan(0.5*pi-b.angle)*dY1+b.x;
      b.y = b.y1;     
    }
    else{ // hit lower
      b.iy--;
      b.x = tan(0.5*pi-b.angle)*dY0+b.x;
      b.y = b.y0;
    }
  }

  // return lenght of ray
  return sqrt(pow(b.x-oldx,2)+pow(b.y-oldy,2));

};
