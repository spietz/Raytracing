#include <iostream>
#include <cmath>
#include <stdexcept>
#include <boost/timer/timer.hpp>
#include "raybox.h"

using namespace std;

double my_rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(){

  // box domain
  box b;
  b.x0 = 5; b.x1 = 10;
  b.y0 = 8; b.y1 = 20;
  b.ix = 0; b.iy = 0;

  // reference sources and angles
  const int N = 6;
  double xV[N] = {6,7,8,1,6};
  double yV[N] = {12,13,10,2,12};
  double aV[N] = {1.2,0.8,-0.9,0,1.6};

  double* xHit; 
  double l;

  for(int n=0; n<N; n++){
    
    try{

      b.x=xV[n]; b.y=yV[n]; b.angle=aV[n]; // set source and angle

      xHit = tracebox(b); // get hitpoint

      l = sqrt(pow(xHit[0]-xV[n],2)+pow(xHit[1]-yV[n],2)); // calc lenght

      cout<<xV[n]<<"\t"<<yV[n]<<"\t"<<aV[n]<<"\t"<<xHit[0]<<"\t"<<xHit[1]<<"\t"<<l<<"\t"<<b.ix<<"\t"<<b.iy<<endl; // print result
      b.ix = 0; b.iy = 0; // reset index

	}

    catch(domain_error& e){
      cout << e.what() << endl;
    }

  }

  // randomizing input for timing
  const int NN = 1e5;
  double xxV[NN];
  double yyV[NN];
  double aaV[NN];
  // initialize random seed:
  srand (time(NULL));
  for(int n=0; n<NN; n++){
    xxV[n] = my_rand(b.x0, b.x1);
    yyV[n] = my_rand(b.y0, b.y1);
    aaV[n] = my_rand(-3.1415/2, 3.1415/2);
  }

  // create boost cpu timer object -> starts timing immidiately
  boost::timer::auto_cpu_timer timer;
  for(int n=0; n<NN; n++){
    b.x=xxV[n]; b.y=yyV[n]; b.angle=aaV[n]; // set source and angle
    xHit = tracebox(b);
  }
  
return 0;

} 
