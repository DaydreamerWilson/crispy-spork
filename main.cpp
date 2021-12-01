#include <iostream>
#include <cmath>
#include "library.h"
#include "render.h"

using namespace std;

renderer renderer0(100, 150);
map test_map("./res/test_map.txt");
map test_img("./res/test_img.txt");
string sinput;

void set_resolution(){
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
      renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');

      renderer0.drawText(5, 5, "Make sure you can see these 6 lines");
      renderer0.drawText(5, 6, "a rectangle made of *");
      renderer0.drawText(5, 7, "and two 5 by 5 alphabetic table");
      renderer0.drawText(5, 8, "Resolution:");
      renderer0.drawText(5, 9, "Height:           Characters");
      renderer0.drawInt(15, 9, resolution[sel_resol][const_h]);
      renderer0.drawText(5, 10, "Width:           Characters");
      renderer0.drawInt(15, 10, resolution[sel_resol][const_w]);
      renderer0.drawMap(42, 5, 0, 0, test_map.height, test_map.width, test_map);
      renderer0.drawImage(42, 11, 0, 0, test_img.height, test_img.width, test_img);
      renderer0.present();

      cout << "Make sure you can see the calibration text box" << endl;
      cout << "Enter (OKAY) to confirm, anything otherwise to change resolution: ";
      cin >> sinput;
    }
  }
}

int main(){
  load_characters("./res/characters");

  init_rand();
  renderer0.clear();

  set_resolution();

  while(sinput == "OKAY"){
    renderer0.clear();
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(5, 5, "Main menu");
    renderer0.drawText(5, 7, "(T)utorial");
    renderer0.drawText(5, 8, "(C)ampaign");
    renderer0.drawText(5, 9, "(S)kirmish");
    renderer0.drawText(5, 10, "(I)nventory");
    renderer0.drawText(5, 11, "(R)esolution");
    renderer0.drawText(5, 12, "(E)xit");
    renderer0.present();

    char cinput;
    cout << "Please enter the capital letter for you choice: " <<endl;
    cin >> cinput;
    switch(cinput){
    case 'T':
      break;
    case 'C':
      break;
    case 'S':
      break;
    case 'I':
      break;
    case 'R':
      set_resolution();
      break;
    case 'E':
      sinput = "";
      break;
    }
  }
}
