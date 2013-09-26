#include <iostream>
#include <stdexcept>
#include <boost/timer/timer.hpp>
#include "mymatrix.h"
#include "raytracer.h"

using namespace std;

int main(){
 
  // Square domain height and width
  double H = 20;
  double W = 15;
  
  // Set corner coordinates
  double x0 = 0, y0 = 0;
  double x1 = W, y1 = H;

  // Source
  double xs = 0;
  
  // Receiver
  double xr = W;

  // Number of cells in each axis direction
  int Nx = 3, Ny = 3;

  const int N = 5;
  double ys[N] = {1,8,19,-3,0};
  double yr[N] = {1,14,1,10,25};

  // create boost cpu timer object -> starts timing immidiately -> output results in destructor
  boost::timer::auto_cpu_timer timer;


  // Use raytracer to get path through domain and lenght of rays within subdomains
  for(int n=0; n<N; n++){

    try{
      mymatrix* L = raytracer(x0,y0,x1,y1,xs,ys[n],xr,yr[n],Nx,Ny);
      L->print();
    }

    catch(domain_error& e){
      cout << e.what() << endl;
    }
  }

  return 0;
}
