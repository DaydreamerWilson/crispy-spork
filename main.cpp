#include <iostream>
#include <cmath>
#include "library.h"
#include "render.h"

using namespace std;

renderer renderer0(100, 150);
map world_map("./res/test.txt");
string sinput;

int main(){
  renderer0.clear();
  sinput = "!OKAY";
  while(sinput!="OKAY"){
    cout << "Please enter desired resolution ( S | M | L ): ";
    char cinput;
    cin >> cinput;

    renderer0.clear();
    switch(cinput){
      case 'S': sel_resol = small;
        break;
      case 'M': sel_resol = medium;
        break;
      case 'L': sel_resol = large;
        break;
      default:
        cout << "Please enter (1) capital letter" << endl;
        break;
    }

    if(cinput == 'S' || cinput == 'M' || cinput == 'L'){
      renderer0.resize(resolution[sel_resol][const_h], resolution[sel_resol][const_w]);
      for(int i = 0; i < resolution[sel_resol][const_w]; i++){
        for(int j = 0; j < resolution[sel_resol][const_h]; j++){
          if((j==0 || j==resolution[sel_resol][const_h]-1)||(i==0 || i==resolution[sel_resol][const_w]-1)){
            renderer0.drawPoint(i, j, '*');
          }
        }
      }

      renderer0.drawText(5, 5, "Make sure you can see these 6 lines");
      renderer0.drawText(5, 6, "a rectangle made of *");
      renderer0.drawText(5, 7, "and a 5 by 5 alphabetic table");
      renderer0.drawText(5, 8, "Resolution:");
      renderer0.drawText(5, 9, "Height:           Characters");
      renderer0.drawInt(15, 9, resolution[sel_resol][const_h]);
      renderer0.drawText(5, 10, "Width:           Characters");
      renderer0.drawInt(15, 10, resolution[sel_resol][const_w]);
      renderer0.drawMap(42, 5, 0, 0, 5, 5, world_map);
      renderer0.present();

      cout << "Make sure you can see the calibration text box" << endl;
      cout << "Enter (OKAY) to confirm, anything otherwise to change resolution: ";
      cin >> sinput;
    }
  }
}
