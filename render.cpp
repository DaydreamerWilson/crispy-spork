#include <string>
#include <iostream>
#include "render.h"
#include "library.h"

using namespace std;

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
//New
bool renderer::drawLine(int x1, int y1, int x2, int y2, char c){
  if ((x1!=x2)&&(y1!=y2)){
    cout << "error drawing line: line not vertical or horizontal" << endl;
    return false;
  }
  else if (x1>=0 && x2>=0){
    if (x1>=resolution[sel_resol][const_h]||x2>=resolution[sel_resol][const_h]) || (y1>=resolution[sel_resol][const_w]||y2>=resolution[sel_resol][const_w])){
      cout << "error drawing line: line out of bound" << endl;
      return false;
      }
    }
  else if (x1<0 && x2>0){
    if (x1<=resolution[sel_resol][const_h]||x2>=resolution[sel_resol][const_h]) || (y1>=resolution[sel_resol][const_w]||y2>=resolution[sel_resol][const_w])){
      cout << "error drawing line: line out of bound" << endl;
      return false;
    }
  else if (x1>0 && x2<0){
    if (x1>=resolution[sel_resol][const_h]||x2<=resolution[sel_resol][const_h]) || (y1>=resolution[sel_resol][const_w]||y2>=resolution[sel_resol][const_w])){
      cout << "error drawing line: line out of bound" << endl;
      return false;
    }
  else{
    if (x1<=resolution[sel_resol][const_h]||x2<=resolution[sel_resol][const_h]) || (y1>=resolution[sel_resol][const_w]||y2>=resolution[sel_resol][const_w])){
      cout << "error drawing line: line out of bound" << endl;
      return false;
      }
    }
  }
  else{
    if (y1==y2){
      for (int i; i<x2; i++){
        drawPoint(i, y1, c);
      }
    }
    else if (x1==x2){
      for (int j; j<y2; j++){
        drawPoint(x1, j, c);
      }
    }
  }
}
//New
bool renderer::drawRectangle(int x, int y, int h, int w, char c){
  double x_left=x, x_right=x_left+w;
  double y_lower=y, y_higher=y_lower+h;
  double height = resolution[sel_resol][const_h];
  double width = resolution[sel_resol][const_w];
  if ((h>height)||(w>width)){
    cout << "error drawing rectangle: rectangle out of bound";
    return false;
  }
  else{
    drawLine(x_left, y_lower, x_right, y_higher, c);
  }
}

bool renderer::drawText(int x, int y, string s){
  if(s.length()+x > resolution[sel_resol][const_w]){
    return false;
  }
  else{
    for(int i = 0; i < s.length(); i++){
      drawPoint(x+i, y, s[i]);
    }
  }
  return true;
}

bool renderer::drawInt(int x, int y, int k){
  return drawText(x, y, int_to_string(k));
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

bool renderer::drawMap(int x1, int y1, int x2, int y2, int h, int w, map tar_map){
  if(x1+w*2 > resolution[sel_resol][const_w] || y1+h > resolution[sel_resol][const_h]){
    return false;
  }
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      if(x2+j >=0 && y2+i >=0){
        drawPoint(x1+j*2, y1+i, tar_map.grid[y2+i][x2+j]);
      }
    }
  }
  return true;
}

bool renderer::drawImage(int x1, int y1, int x2, int y2, int h, int w, map tar_map){
  if(x1+w > resolution[sel_resol][const_w] || y1+h > resolution[sel_resol][const_h]){
    return false;
  }
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      if(x2+j >=0 && y2+i >=0){
        drawPoint(x1+j, y1+i, tar_map.grid[y2+i][x2+j]);
      }
    }
  }
  return true;
}

void renderer::clear(){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      pixel[i][j]=' ';
    }
  }
  for(int i = 0; i < 100; i++){
    cout << endl;
  }
}
