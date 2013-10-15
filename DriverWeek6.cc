#include <iostream>
#include <stdexcept>
#include <boost/timer/timer.hpp>
#include "mymatrix.h"
#include "raytracer.h"

#include <fstream>
#include <algorithm>

using namespace std;

int main(){
 
  // Square domain height and width
  double H = 100;
  double W = 100;
  
  // Set corner coordinates
  double x0 = 0, y0 = 0;
  double x1 = W, y1 = H;
  
  // Number of cells in each axis direction
  int Nx = 20, Ny = 20;

  // Source & receiver
  double xs = 0;
  double xr = W;
  vector<double> Ys, Yr;
  ifstream infile1("rays.txt");
  string s;
  double ys, yr;
  while ( infile1 >> ys >> yr ){ // read from file
    Ys.push_back(ys);
    Yr.push_back(yr);
  }

  // Velocity field
  mymatrix V(Nx, Ny);
  ifstream infile2("velocity.txt");
  double v;

  for(int i=0; i<Nx; ++i)
    {
      for(int j=0; j<Ny; ++j)
	{
	  infile2 >> v;
	  V.write(i,j,v);
	}
    }    

  /* // create boost cpu timer object -> starts timing immidiately -> output results in destructor */
  /* boost::timer::auto_cpu_timer timer; */

  double T; // travel time
  ofstream outfile("raytime.txt");
  for(int n=0; n<Ys.size(); ++n)
    {

      try{
	// matrix of travel lenghts
	mymatrix* L = raytracer(x0,y0,x1,y1,xs,Ys[n],xr,Yr[n],Nx,Ny);

	// compute travel times
	T = 0;
	for(int i=0; i<Nx; ++i)
	  {
	    for(int j=0; j<Ny; ++j)
	      {
		T = T + L->read(i,j)/V.read(i,j);
	      }
	  }

	outfile << T << endl;

      }
      
      catch(domain_error& e){
	cout << e.what() << endl;
      }
    }

  return 0;
}
