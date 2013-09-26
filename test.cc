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
  double l;

  for(int n=0; n<N; n++){
    
    try{

      b.x=xV[n]; b.y=yV[n]; b.angle=aV[n]; // set source and angle

      l = tracebox(b); // get hitpoint

      cout<<xV[n]<<"\t"<<yV[n]<<"\t"<<aV[n]<<"\t"<<b.x<<"\t"<<b.y<<"\t"<<l<<"\t"<<b.ix<<"\t"<<b.iy<<endl; // print result
      b.ix = 0; b.iy = 0; // reset index

	}

    catch(domain_error& e){
      cout << e.what() << endl;
    }

  }

  // randomizing input for timing
  const int NN = 5e3;
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

  // create boost cpu timer object -> starts timing immidiately -> output results in destructor
  boost::timer::auto_cpu_timer timer;

  // do NN² runs
  for(int i=0; i<NN; i++){
    for(int j=0; j<NN; j++){
      b.x=xxV[j]; b.y=yyV[j]; b.angle=aaV[j]; // set source and angle
      l = tracebox(b);
    }
  }
  
return 0;

} 
