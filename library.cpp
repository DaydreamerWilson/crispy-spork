#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include "library.h"

using namespace std;

int sel_resol = small;

map::map(string fin){
  cout << "Loading map: " << fin << endl;

  if(fin.rfind(".txt")!=fin.length()-4){cout << "fatal error loading map: file not found" << endl;}
  ifstream file;
  file.open(fin);
  if(file.fail()){cout << "fatal error loading map: file failed" << endl;}
  string temp;

  getline(file, temp);
  istringstream sin (temp);
  sin >> height >> width;
  cout << temp << ' ';

  grid = new char * [height];

  for(int i = 0; i < height; i++){
    grid[i] = new char [width];
    getline(file, temp);
    cout << temp << ' ';
    for(int j = 0; j < width; j++){
      grid[i][j]=temp[j];
      //cout << grid[i][j];
    }
    //cout << endl;
  }

  cout << endl << "Successfully loaded map: " << fin << endl;
}

string int_to_string(int k){
  int i = 0;
  string temp = "";
  while(pow(10, i)<k){
    i++;
  }
  for(int j = i-1; j >= 0; j--){
    temp += '0' + k / pow(10, j);
    k %= (int)pow(10, j);
  }
  return temp;
}

void init_rand(){
  srand(time(0));
  int sumi, tempi;
  double sumd, tempd, vi, vd;

  sumi = 0;
  sumd = 0;
  vi = 0;
  vd = 0;
  cout << "testing random number generation" << endl;

  for(int i=0; i<1000; i++){
    tempd = randDouble(0, 1);
    sumd += tempd;
    vd += pow(tempd-0.5, 2);
  }
  cout << "mean(0.5)/variance(m=0.5)(0.083) of 1000 double generation:" << sumd/1000 << '/' << vd/999 << endl;

  for(int i=0; i<1000; i++){
    tempi = randInt(0, 11);
    sumi += tempi;
    vi += pow((double)tempi-5, 2);
  }
  cout << "mean(5)/variance(m=5)(10.000) of 1000 integer generation:" << (double)sumi/1000 << '/' << vi/999 << endl;
}

int randInt(int min, int max){
  return rand() % (max-min) + min;
}

double randDouble(double min, double max){
  double temp = 0;
  double range = max-min;
  int i=0;
  while(pow(10, i)<range){
    i++;
  }
  for(int j = -3; j<i; j++){
    temp+=randInt(0,10)*pow(10, j);
  }
  while(temp>=range){
    temp-=range;
  }
  return temp+min;
}
