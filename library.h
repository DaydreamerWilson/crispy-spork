#ifndef library
#define library

#define const_h 0
#define const_w 1

#define small 0
#define medium 1
#define large 2

#include <string>
#include <vector>

using namespace std;

// const resolution preset value
const int resolution[3][2] = {
  {20, 60},
  {32, 96},
  {40, 120}
};

// storing ascii art or map files
class map
{
public:
  int height, width;
  char ** grid;
  map(string fin);
};

// storing the game board
class field
{
public:
  int height, width;
  int ** grid;
  field(map min);
  void clear_mark();
  void add_mark(int x, int y, int range, int i);
};

// storing statistical of characters
class character
{
public:
  int id, hp, atk, def, spd, rgn;
  char tier;
  string icon, name, info;
  character();
  character(string fin);
  void print();
  void render_info();
};

// storing the playerdata, including owned characters
class player{
public:
  int ruby;
  vector<character> character_list;
  void load(string fin);
  void save(string fin);
};

// storing the position and id of chess piece on the board
class piece{
public:
  int x, y, id;
  piece();
  piece(int x, int y, int id);
};

// loading characters data from specific folder
void load_characters(string fin);

// converting integer to string
string int_to_string(int k);

// converting integer input to corresponding map objects
string int_to_map(int k);

// reset seed for random number generation
// test generation randomness
void init_rand();

// generate random integers with minimum value (inclusive) and maximum (exclusive)
// randInt(0,3) will generate three integers 0, 1, 2
int randInt(int min, int max);

// generate random double with minimum value (inclusive) and maximum (exclusive) or 3 decimal places
// randDouble(0, 3) will generate from 0.000 to 2.999
double randDouble(double min, double max);

// store selected resolution
extern int sel_resol;

extern character *characters;
extern int totalchar;

#endif
