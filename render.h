#ifndef render
#define render

#include <string>

using namespace std;

class renderer
{
private:
  char ** pixel = 0;
public:
  int height, width;
  renderer(int h, int w);
  void resize(int h, int w);
  bool drawPoint(int x, int y, char c);
  bool drawLine(int x1, int y1, int x2, int y2, char c);
  bool drawRectangle(int x, int y, int h, int w, char c);
  bool drawText(int x, int y, string s);
  bool drawInt(int x, int y, int k);
  bool present();
  void clear();
};

#endif
