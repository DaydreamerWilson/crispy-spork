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
    cout << "error drawing point: point out of bound" << endl;
  }
}
//New_2
bool renderer::drawLine(int x1, int y1, int x2, int y2, char c){
  if(((x1!=x2)&&(y1!=y2))||((x1==x2) && (y1==y2))){
    cout << "error drawing line: line not vertical or horizontal" << endl;
    return false;
  }
  if((x1<0)||(x1>resolution[sel_resol][const_w]-1)||
     (x2<0)||(x2>resolution[sel_resol][const_w]-1)||
     (y1<0)||(y1>resolution[sel_resol][const_h]-1)||
     (y2<0)||(y2>resolution[sel_resol][const_h]-1)){
    cout << "error drawing line: line out of bound" << endl;
  }
  int temp=0;
  if(x1==x2){
    if(y1>y2){
      temp=y2;
      y2=y1;
      y1=temp;
    }
    for(int i = y1; i < y2+1; i++){
      drawPoint(x1, i, c);
    }
  }
  if(y1==y2){
    if(x1>x2){
      temp=x2;
      x2=x1;
      x1=temp;
    }
    for(int i = x1; i < x2+1; i++){
      drawPoint(i, y1, c);
    }
  }
  return 0;
}

//New_2
bool renderer::drawRectangle(int x, int y, int h, int w, char c){
  if((y+h>resolution[sel_resol][const_h])||(x+w>resolution[sel_resol][const_w])||(x<0)||(y<0)){
    cout << "error drawing rectangle: rectangle out of bound" << endl;
    return false;
  }
  else{
    drawLine(x, y, x+w-1, y, c);
    drawLine(x, y, x, y+h-1, c);
    drawLine(x+w-1, y+h-1, x, y+h-1, c);
    drawLine(x+w-1, y+h-1, x+w-1, y, c);
  }
  return 0;
}

bool renderer::drawText(int x, int y, string s){
  if((int)s.length()+x > resolution[sel_resol][const_w]){
    return false;
  }
  else{
    for(int i = 0; i < (int)s.length(); i++){
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

bool renderer::drawField(int x, int y, field tar_fin){
  x++;
  y++;
  for(int i = 0; i < tar_fin.height; i++){
    drawText((i+1)*3+x, y, int_to_string(i));
  }
  for(int j = 0; j < tar_fin.width; j++){
    drawText(x, j+y+1, int_to_string(j));
  }
  for(int i = 0; i < tar_fin.height; i++){
      for(int j = 0; j < tar_fin.width; j++){
          drawText(3*(j+1)+x, i+y+1, int_to_map(tar_fin.grid[i][j]));
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
  cout << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n' << '\n';
}
