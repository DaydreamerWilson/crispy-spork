#include <iostream>
#include <cmath>
#include "library.h"
#include "render.h"

using namespace std;

renderer renderer0(100, 150);
string sinput;
int iinput[5];

int main(){
  sinput = "!OKAY";
  while(sinput!="OKAY"){
    cout << "Please enter desired resolution (height width):";
    cin >> iinput[0] >> iinput[1];
    if((iinput[0]>0 && iinput[0]<200) && (iinput[1]>0 && iinput[1]<200)){
      renderer0.resize(iinput[0], iinput[1]);
      renderer0.drawPoint(0, 0, '*');
      renderer0.drawPoint(iinput[1]-1, 0, '*');
      renderer0.drawPoint(0, iinput[0]-1, '*');
      renderer0.drawPoint(iinput[1]-1, iinput[0]-1, '*');
      renderer0.present();
      renderer0.clear();
      cout << "Please make sure you can see this line and all 4 * simultaneously." << endl;
      cout << "Enter 'OKAY' to confirm, anything otherwise to change resolution:";
      cin >> ssinput;
    }
    else{
      cout << "Please only enter integer within range: [0, 200]";
    }
  }
}
