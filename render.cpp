#include "render.h"
#include <iostream>

using namespace std;

/*
class renderer
{
private:
  char ** pixel
  int height, width;
}
*/

renderer::renderer(int h, int w){
  height = h;
  width = w;
  
  pixel = new char * [height];
  for(int i = 0; i < height; i++){
    pixel[i] = new char[width];
  }
}

void renderer::resize(int h, int w){
  for(int i = 0; i < height; i++){
    delete[] pixel[i];
  }
  delete[] pixel;
  
  height = h;
  width = w;
  
  pixel = new char * [height];
  for(int i = 0; i < height; i++){
    pixel[i] = new char[width];
  }
  
  clear();
}
  
bool renderer::drawPoint(int x, int y, char c){
  if(x>=0 && x<width && y>=0 && y<height){
    pixel[y][x]=c;
    return true;
  }
  else{
    return false;
  }
}
  
bool renderer::drawLine(int x1, int y1, int x2, int y2, char c){
  return false;
}
  
bool renderer::drawRectangle(int x, int y, int h, int w, char c){
  return false;
}
  
bool renderer::present(){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      cout << pixel[i][j];
    }
    cout << endl;
  }
  return true;
}

void renderer::clear(){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j]=' ';
    }
  }
}
