#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "library.h"

using namespace std;

int sel_resol = small;

map::map(string fin){
  cout << "Loading map: " << fin << endl;

  if(fin.rfind(".txt")!=fin.length()-4){cout << "fatal error loading map (0x1)" << endl;}
  ifstream file;
  file.open(fin);
  if(file.fail()){cout << "fatal error loading map (0x2)" << endl;}

  file >> height >> width;

  grid = new char * [height];

  for(int i = 0; i < height; i++){
    grid[i] = new char [width];
    for(int j = 0; j < width; j++){
      file >> grid[i][j];
    }
  }

  cout << "Successfully loaded map: " << fin << endl;
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
