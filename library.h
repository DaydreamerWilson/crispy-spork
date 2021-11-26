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
// storing ascii art or map files

string int_to_string(int k);
// converting integer to string

void init_rand();
// reset seed for random number generation
// test generation randomness

int randInt(int min, int max);
// generate random integers with minimum value (inclusive) and maximum (exclusive)
// randInt(0,3) will generate three integers 0, 1, 2

double randDouble(double min, double max);
// generate random double with minimum value (inclusive) and maximum (exclusive) or 3 decimal places
// randDouble(0, 3) will generate from 0.000 to 2.999

#endif
