#ifndef _raybox_h
#define _raybox_h

struct box{
  double x0,y0; // lower left corner
  double x1,y1; // upper right corner  
  double angle; // angle of ray
  int ix, iy; // box index
  double x, y;  // source of ray
};

double* tracebox(box &box);

#endif
