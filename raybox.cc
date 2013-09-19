#include "raybox.h"

#include <cmath>
#include <stdexcept>

double* tracebox(box &box){

  const double pi = 3.14159265359;

  double* xHit = new double[2];
  double dX = box.x1-box.x; // x dist from upper right corner
  double dY = box.y1-box.y; // y dist from upper right corner

  if(box.x<box.x0||box.y<box.y0||box.x1<box.x||box.y1<box.y){
    throw std::domain_error("Ray is not inside box!");
  }

  if(-pi/2>box.angle||pi/2<box.angle){
    throw std::domain_error("Angle is not in range!");
  }

  double topHitPointX = tan(0.5*pi-box.angle)*dY+box.x; // hit point top wall . x coord
  double rightHitPointY = tan(box.angle)*dX+box.y; // hit point with right wall . y coord
  
  // will the ray hit the right wall within box??
  if(box.y0<rightHitPointY&&rightHitPointY<box.y1){
    box.ix++; // apparently yes, so lets increment the x index of the box
    xHit[0] = box.x1; // x coord of hitpoint
    xHit[1] = rightHitPointY; // y coord of hitpoint
  }
  else{ // it did not hit right wall, so we either it hits upper or lower wall
    if(box.angle>0){ // hit upper
      box.iy++;
      xHit[0] = topHitPointX;
      xHit[1] = box.y1;     
    }
    else{ // hit lower
      box.iy--;
      xHit[0] = box.x1-topHitPointX;	
      xHit[1] = box.y0;
    }
  }

  return xHit;

};
