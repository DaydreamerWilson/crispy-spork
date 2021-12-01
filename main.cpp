#include <iostream>
#include <cmath>
#include <sstream>
#include "library.h"
#include "render.h"

using namespace std;

renderer renderer0(100, 150);
map test_map("./res/test_map.txt");
map test_img("./res/test_img.txt");
string sinput;
player playerdata;

void set_resolution(){
  sinput = "!OKAY";
  while(sinput!="OKAY"){
    cout << "Please enter desired resolution ( S | M | L ): ";
    char cinput;
    cin >> sinput;
    cinput = sinput[0];

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

void print_character(character c){
  renderer0.drawText(2, 2, "ID  : "); renderer0.drawInt(8, 2, c.id);
  renderer0.drawText(2, 3, "Name: "); renderer0.drawText(8, 3, c.name);
  renderer0.drawText(2, 4, "Icon: "); renderer0.drawText(8, 4, c.icon);
  renderer0.drawText(2, 6, "Description: "); renderer0.drawText(2, 7, c.info);
  renderer0.drawText(2, 9, "Tier   : "); renderer0.drawPoint(12, 9, c.tier);
  renderer0.drawText(2, 10, "Health : "); renderer0.drawInt(12, 10, c.hp);
  renderer0.drawText(2, 11, "Attack : "); renderer0.drawInt(12, 11, c.atk);
  renderer0.drawText(2, 12, "Defense: "); renderer0.drawInt(12, 12, c.def);
  renderer0.drawText(2, 13, "Speed  : "); renderer0.drawInt(12, 13, c.spd);
  renderer0.drawText(2, 14, "Range  : "); renderer0.drawInt(12, 14, c.rgn);
}

int main(){
  load_characters("./res/characters");

  init_rand();
  playerdata.load("./res/playerdata.txt");

  renderer0.clear();

  set_resolution();

  while(sinput!="QUIT"){
    renderer0.clear();
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(2, 2, "Main menu");
    renderer0.drawText(2, 4, "(T)utorial");
    renderer0.drawText(2, 5, "(C)ombat");
    renderer0.drawText(2, 6, "(S)ave");
    renderer0.drawText(2, 7, "(I)nventory");
    renderer0.drawText(2, 8, "(R)esolution");
    renderer0.drawText(2, 9, "(E)xit");
    renderer0.present();

    char cinput='S';
    cout << "Please enter your command: ";
    cin >> sinput;
    cinput = sinput[0];
    switch(cinput){
    case 'T':
      break;
    case 'C':
      break;
    case 'S':
      playerdata.save("./res/playerdata.txt");
      renderer0.clear();
      renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
      renderer0.drawText(2, 2, "Player data successfully saved");
      renderer0.present();
      cout << "Please enter anything to continue: ";
      cin >> sinput;
      break;
    case 'I':
      {
        int page = 1;
        int max_page = (playerdata.character_list.size()/(resolution[sel_resol][const_h]-9))+1;
        while(cinput!='M'){
          renderer0.clear();
          renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
          renderer0.drawText(2, 2, "Owned Character List");
          renderer0.drawText(34, 2, "Page: ");
          renderer0.drawInt(40, 2, page);
          renderer0.drawText(41, 2, "/");
          renderer0.drawInt(42, 2, max_page);
          for(int i = 0; (i<(resolution[sel_resol][const_h]-10)) && (i+(page-1)*(resolution[sel_resol][const_h]-10)<playerdata.character_list.size()); i++){
            renderer0.drawText(2, i+4, "(");
            renderer0.drawInt(3, i+4, playerdata.character_list[i+(page-1)*(resolution[sel_resol][const_h]-10)].id);
            renderer0.drawText(5, i+4, ")");
            renderer0.drawText(7, i+4, playerdata.character_list[i+(page-1)*(resolution[sel_resol][const_h]-10)].name);
            renderer0.drawPoint(30, i+4, playerdata.character_list[i+(page-1)*(resolution[sel_resol][const_h]-10)].tier);
          }
          renderer0.drawText(2, resolution[sel_resol][const_h]-5, "Enter (I) to enter ID selection mode");
          renderer0.drawText(2, resolution[sel_resol][const_h]-3, "Enter (<) or (>) to switch page, (M) to return menu");
          renderer0.present();
          cout << "Please enter your command: ";
          cin >> sinput;
          cinput=sinput[0];

          bool num = true;
          for(int i=0; i<sinput.size(); i++){
            if(sinput[i]<'0' || sinput[i]>'9'){
              num = false;
              break;
            }
          }
          if(num == true){
            cout << "Num is true!!!";
            int temp;
            istringstream iss (sinput);
            iss >> temp;
            for(int i = 0; i<playerdata.character_list.size(); i++){
              if(playerdata.character_list[i].id==temp){
                renderer0.clear();
                renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
                print_character(characters[temp-1]);
                renderer0.present();
                cout << "Please enter anything to continue: ";
                cin >> sinput;
              }
            }
            sinput="!QUIT";
          }
          else{
            if(cinput == '<'){
              page--;
              if(page <= 0){page = 0;}
            }
            if(cinput == '>'){
              page++;
              if(page > max_page){page = max_page;}
            }
          }
        }
      }
      break;
    case 'R':
      set_resolution();
      break;
    case 'E':
      playerdata.save("./res/playerdata.txt");
      renderer0.clear();
      renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
      renderer0.drawText(5, 5, "Player data successfully saved");
      renderer0.drawText(5, 6, "Terminating game...");
      renderer0.present();
      sinput = "QUIT";
      break;
    }
  }
}
