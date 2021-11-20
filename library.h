#ifndef library
#define library

#define const_h 0
#define const_w 1

#define small 0
#define medium 1
#define large 2

#include <string>

using namespace std;

extern int sel_resol;

const int resolution[3][2] = {
  {20, 60},
  {32, 96},
  {40, 120}
};

class map
{
public:
  int height, width;
  char ** grid;
  map(string fin);
};

string int_to_string(int k);

#endif
