#include <cmath>
#include <string>
#include "library.h"

using namespace std;

int sel_resol = small;

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
