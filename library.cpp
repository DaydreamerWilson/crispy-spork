#include <cmath>
#include "library.h"

int sel_resol = small;

string int_to_string(int k){
  int i = 0;
  string temp;
  while(pow(10, i)<k){
    i++;
  }
  for(int j = i; j > 0; j--){
    temp[j-i] = k / pow(10, j);
    k %= pow(10, j);
  }
  return temp;
}
