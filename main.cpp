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
  renderer0.drawText(2, 6, "Description: ");
  int y=6;
  if(c.info.size()>resolution[sel_resol][const_w]-4){
    for(int i = 0; i < c.info.size(); i++){
      if(i % (resolution[sel_resol][const_w]-4)==0){
        y++;
      }
      renderer0.drawPoint(2+i%(resolution[sel_resol][const_w]-4), y, c.info[i]);
    }
  }
  else{
    y++;
    renderer0.drawText(2, y, c.info);
  }
  renderer0.drawText(2, y+2, "Tier   : "); renderer0.drawPoint(12, y+2, c.tier);
  renderer0.drawText(2, y+3, "Health : "); renderer0.drawInt(12, y+3, c.hp);
  renderer0.drawText(2, y+4, "Attack : "); renderer0.drawInt(12, y+4, c.atk);
  renderer0.drawText(2, y+5, "Defense: "); renderer0.drawInt(12, y+5, c.def);
  renderer0.drawText(2, y+6, "Speed  : "); renderer0.drawInt(12, y+6, c.spd);
  renderer0.drawText(2, y+7, "Range  : "); renderer0.drawInt(12, y+7, c.rgn);
}

void choose_character(int f, int e, character * player_c, character * enemy_c){
  int page = 1, chose = 0;
  int max_page = (playerdata.character_list.size()/(resolution[sel_resol][const_h]-9))+1;
  char cinput='a';
  string sinput=" ";
  while(chose<f){
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
    renderer0.drawText(2, resolution[sel_resol][const_h]-5, "Enter ID to select character");
    renderer0.drawText(2, resolution[sel_resol][const_h]-3, "Enter (<) or (>) to switch page");
    renderer0.present();
    cout << "Please enter your selection, choose " << f-chose << " more characters : ";
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
      //cout << "Num is true!!!";
      int temp;
      istringstream iss (sinput);
      iss >> temp;
      for(int i = 0; i<playerdata.character_list.size(); i++){
        if(playerdata.character_list[i].id==temp){
          player_c[chose] = playerdata.character_list[i];
          chose++;
        }
      }
    }
    else{
      if(cinput == '<'){
        page--;
        if(page < 1){page = 1;}
      }
      if(cinput == '>'){
        page++;
        if(page > max_page){page = max_page;}
      }
    }
  }

  for(int i = 0; i < e; i++){
    enemy_c[i] = characters[randInt(10, 81)];
  }
}

void battle(map min){
  character * player_c = 0;
  character * enemy_c = 0;
  piece * blufor;
  piece * redfor;
  field field_now (min);
  int f = 0, e = 0;
  for(int i = 0; i < field_now.height; i++){
    for(int j = 0; j < field_now.width; j++){
      if(field_now.grid[i][j]==1){
        f++;

      }
      if(field_now.grid[i][j]==2){
        e++;
      }
    }
  }
  player_c = new character[f];
  enemy_c = new character[e];
  blufor = new piece[f];
  redfor = new piece[e];

  if(f==0 || e==0){
    cout << "error starting battle: map does not pass spawn check" << endl;
  }

  choose_character(f, e, player_c, enemy_c);

  for(int i = 0; i < field_now.height; i++){
    for(int j = 0; j < field_now.width; j++){
      if(field_now.grid[i][j]==1){
        f--;
        blufor[f] = piece (j, i, player_c[f].id);
        field_now.grid[i][j] = blufor[f].id;
      }
      if(field_now.grid[i][j]==2){
        e--;
        redfor[e] = piece (j, i, enemy_c[e].id);
        field_now.grid[i][j] = redfor[e].id;
      }
    }
  }

  delete[] player_c;
  delete[] enemy_c;

  renderer0.clear();
  renderer0.drawField(0, 0, field_now);
  renderer0.present();

  delete[] blufor;
  delete[] redfor;
}

int main(){
  load_characters("./res/characters");

  init_rand();
  playerdata.load("./res/playerdata.txt");

  renderer0.clear();

  set_resolution();

  battle(map("./res/map/8_8_symmetric.txt"));

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
          renderer0.drawText(2, resolution[sel_resol][const_h]-5, "Enter ID to enter character info page");
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
            //cout << "Num is true!!!";
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
              if(page < 1){page = 1;}
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
