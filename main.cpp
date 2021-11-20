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
      for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          if((j==0 || j==4)||(i==0 || i==4)){
            renderer0.drawPoint(resolution[sel_resol][const_w]/4*i-1, resolution[sel_resol][const_h]/4*j-1;
          }
        }
      }
      renderer0.present();
      renderer0.clear();

      cout << "Please make sure you can see this line and all 16 * simultaneously." << endl;
      cout << "Enter 'OKAY' to confirm, anything otherwise to change resolution:";
      cin >> sinput;
    }
  }
}
