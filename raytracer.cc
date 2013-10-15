#include "raytracer.h"
#include <cmath>
#include <stdexcept>
#include "raybox.h"
#include "mymatrix.h"
#include <iostream>

mymatrix* raytracer(double x0,double y0,double x1,double y1,double xs,double ys,double xr,double yr,int Nx,int Ny)
{

  // Check bounds
  if(xs<x0||ys<y0||xs>x1||ys>y1){
    throw std::domain_error("Source is not in domain!");
  }
  if(xr<x0||yr<y0||xr>x1||yr>y1){
    throw std::domain_error("Receiver is not in domain!");
  }
 
  // Matrix of lenghts
  mymatrix* L = new mymatrix(Nx,Ny); 

  // Calculating ray angle
  double angle = atan2(yr-ys,xr-xs);

  // Cell sizes
  double dX = (x1-x0)/Nx, dY = (y1-y0)/Ny; 

  // Starting sub-domain (raybox)
  box b; // init struct
  b.ix = floor((xs-x0)/dX), b.iy = floor((ys-y0)/dY); // set starting index
  b.x = xs, b.y = ys; // set statring source
  b.angle = angle; // set angle

  // Aim for index where receiver is located
  int ix_aim = floor((xr-x0)/dX), iy_aim = floor((yr-y0)/dY); // set index
  if (ix_aim == Nx) --ix_aim; // ensure that boundary is covered by subdomains
  if (iy_aim == Ny) --iy_aim; // ensure that boundary is covered by subdomain
  
  int ix_old = b.ix, iy_old = b.iy;

  // While the x-index is still on the grid
  while (b.ix < Nx){
      
    // Check that index is within bounds
    if(b.ix < 0 && b.ix >= Nx && b.iy < 0 && b.iy >= Ny){
      throw std::domain_error("Index is not within domain");
    }
      
    // Get coordinates of current cell
    b.x0 = b.ix*dX+x0, b.x1 = b.x0+dX; // set x coords
    b.y0 = b.iy*dY+y0, b.y1 = b.y0+dY; // set y coords
      
    // Trace box and store result
    ix_old = b.ix, iy_old = b.iy;
    L->write(ix_old,iy_old,tracebox(b));
  }

  return L;

}
