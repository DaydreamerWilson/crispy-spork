#ifndef render
#define render

class renderer
{
private:
  char ** pixel = NULL;
public:
  void renderer(int h, int w);
  
  void resize(int h, int w);
  
  bool drawPoint(int x, int y, char c);
  
  bool drawLine(int x1, int y1, int x2, int y2, char c);
  
  bool drawRectangle(int x, int y, int h, int w, char c);
  
  bool present();
  
  int[2] size();
}

#endif
