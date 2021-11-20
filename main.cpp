#include <iostream>
#include <cmath>
#include "library.h"
#include "render.h"

using namespace std;

renderer renderer0(100, 150);
string sinput;

int main(){
  sinput = "!OKAY";
  while(sinput!="OKAY"){
    cout << "Please enter desired resolution (S|M|L):";
    char cinput;
    cin >> cinput;
    
    switch(cinput){
      case 'S': sel_resol = small;
        break;  
      case 'M': sel_resol = medium;
        break;
      case 'L': sel_resol = large;
        break;
      default:
        cout << "Please enter capital letters";
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
      renderer0.drawText(5, 5, "Make sure you can see this two lines");
      renderer0.drawText(5, 6, "and a rectangle made of * with ease");
      renderer0.present();
      renderer0.clear();

      cout << "Enter 'OKAY' to confirm, anything otherwise to change resolution:";
      cin >> sinput;
    }
  }
}
