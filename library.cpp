#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include "library.h"

using namespace std;

int sel_resol = small;
character *characters = 0;
int totalchar = 0;

// loading txt into map file
map::map(string fin){
  cout << "Loading map: " << fin << endl;

  if(fin.rfind(".txt")!=fin.length()-4){cout << "fatal error loading map: syntax error" << endl;}
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
    }
  }

  cout << endl << "Successfully loaded map: " << fin << endl;
}

// constructor for field data
field::field(map min){
  if(min.height==0||min.width%2!=0||min.width==0){
    cout << "fatal error building map: input format error" << endl;
  }

  height = min.height;
  width = min.width/2;

  grid = new int * [height];
  for(int i = 0; i < height; i++){
    grid[i] = new int [width];
  }

  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
        grid[i][j] = min.grid[i][2*j+1]-'0';
        if(grid[i][j]==3){
          grid[i][j]=-1;
        }
    }
  }
}

// clear flood fill check marker
void field::clear_mark(){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      if(grid[i][j]>0){grid[i][j]=0;}
    }
  }
}

// using flood fill algorithm to check tile valdiation
void field::add_mark(int x, int y, int range, int i){
  if(grid[y][x]>i || grid[y][x]==0){
    grid[y][x]=i;
    if(range>0){
      range--;
      i++;
      if(x>0){add_mark(x-1, y, range, i);}
      if(y>0){add_mark(x, y-1, range, i);}
      if(x<width-1){add_mark(x+1, y, range, i);}
      if(y<height-1){add_mark(x, y+1, range, i);}
    }
  }
}

// dummy constructor for declaration of null pointer
character::character(){}

// constructor for character data
character::character(string fin){
  if(fin.rfind(".txt")!=fin.length()-4){cout << "fatal error loading character: syntax error" << endl;}
  ifstream file;
  file.open(fin);
  if(file.fail()){cout << "fatal error loading character: file failed" <<endl;}

  flag = false;

  string temp;
  file >> temp >> id;
  file >> temp;
  getline(file, name);
  name = name.substr(1);
  file >> temp >> icon;
  file >> temp;
  getline(file, info);
  info = info.substr(1);
  file >> temp >> tier;
  file >> temp >> hp;
  file >> temp >> atk;
  file >> temp >> def;
  file >> temp >> spd;
  file >> temp >> rgn;
}

// printing all character data
void character::print(){
  cout << "noid: " << id << endl;
  cout << "name: " << name << endl;
  cout << "icon: " << icon << endl;
  cout << "description: " << info << endl;
  cout << "class: " << tier << endl;
  cout << "hpt: " << hp << endl;
  cout << "atk: " << atk << endl;
  cout << "def: " << def << endl;
  cout << "spd: " << spd << endl;
  cout << "rgn: " <<rgn << endl;
}

// loading characters list
void load_characters(string fin){
  totalchar;
  int id;
  string fin_1;
  ifstream list_file, character_file;
  list_file.open(fin+"/character_list.txt");
  if(list_file.fail()){cout << "fatal error loading character list: file failed" << endl;}
  list_file >> totalchar;
  characters = new character[totalchar];
  for(int i = 0; i < totalchar; i++){
    list_file >> id;
    list_file >> fin_1;
    characters[i] = (fin+"/"+fin_1+".txt");
    if(id != characters[i].id && i!=id){cout << "error loading character: character file id not matching character list id (" << id << ')' << endl;}
    cout << "loading character: " << characters[i].id << endl;
  }
  cout << "finished loading characters!" << endl;
}

// loading playerdata
void player::load(string fin){
  character_list.clear();

  ifstream file;
  if(fin.rfind(".txt")!=fin.length()-4){cout << "fatal error loading playerdata: syntax error" << endl;}
  file.open(fin);
  if(file.fail()){cout << "fatal error loading playerdata: file failed" <<endl;}

  int counter, temp;
  file >> ruby >> counter;
  for(int i = 0; i < counter; i++){
    file >> temp;
    character_list.push_back(characters[temp-1]);
  }
}

// saving playerdata and reloading playerdata
void player::save(string fin){
  int * temp;
  int itemp;
  ofstream file;
  if(fin.rfind(".txt")!=fin.length()-4){cout << "fatal error saving player data: syntax error" << endl;}
  file.open(fin);
  if(file.fail()){cout << "fatal error saving character: file failed" <<endl;}

  temp = new int [character_list.size()];

  for(int i = 0; i < character_list.size(); i++){
    temp[i]=character_list[i].id;
  }

  for(int i = 0; i < character_list.size(); i++){
    for(int j = 0; j < character_list.size()-1; j++){
      if(temp[j]>temp[j+1]){
        itemp = temp[j];
        temp[j] = temp[j+1];
        temp[j+1] = itemp;
      }
    }
  }

  file << ruby << ' ' << character_list.size() << endl;
  for(int i = 0; i < character_list.size(); i++){
    file << temp[i] << ' ';
  }

  file.close();

  load(fin);
}

// dummy constructor for declaration of null pointer
piece::piece(){}

// constructor for piece data
piece::piece(int x, int y, int id){
  this->x = x;
  this->y = y;
  this->id = id;
}

// converting integer to string
string int_to_string(int k){
  if(k < 0){return "KIA";}
  if(k){
    int i = 0;
    string temp = "";
    while(pow(10, i)<=k){
      i++;
    }
    for(int j = i-1; j >= 0; j--){
      temp += '0' + k / pow(10, j);
      k %= (int)pow(10, j);
    }
    return temp;
  }
  else{
    return "0";
  }
}

// converting integer to specific string
string int_to_map(int k){
  switch(k){
  case 0:
    return "   ";
    break;
  case -1:
    return "XX ";
    break;
  default:
    return ".  ";
    break;
  }
}

// initiate random seed and check random function
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

// return a rand integer number etween min and max
int randInt(int min, int max){
  return rand() % (max-min) + min;
}

// return a rand double number between min and max
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
