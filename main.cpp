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
    enemy_c[i] = characters[randInt(10, 80)];
  }
}

void draw_battle(field field_now, piece * blufor, piece * redfor, character * player_c, character * enemy_c, int f, int e){
  renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
  renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], 7, '*');
  renderer0.drawRectangle(resolution[sel_resol][const_w]-7, 0, resolution[sel_resol][const_h], 7, '*');
  renderer0.drawField(7, 0, field_now);

  for(int i = 0; i < f; i++){
    renderer0.drawText(3, 1+i*5, player_c[i].icon);
    renderer0.drawText(2, 2+i*5, int_to_string(player_c[i].hp));
    renderer0.drawText(2, 3+i*5, int_to_string(player_c[i].atk));
    renderer0.drawText(2, 4+i*5, int_to_string(player_c[i].def));
    renderer0.drawText(3*(blufor[i].x+1)+8, blufor[i].y+2, player_c[i].icon);
  }

  for(int j = 0; j < e; j++){
    renderer0.drawText(resolution[sel_resol][const_w]-4, 1+j*5, enemy_c[j].icon);
    renderer0.drawText(resolution[sel_resol][const_w]-5, 2+j*5, int_to_string(enemy_c[j].hp));
    renderer0.drawText(resolution[sel_resol][const_w]-5, 3+j*5, int_to_string(enemy_c[j].atk));
    renderer0.drawText(resolution[sel_resol][const_w]-5, 4+j*5, int_to_string(enemy_c[j].def));
    renderer0.drawText(3*(redfor[j].x+1)+8, redfor[j].y+2, enemy_c[j].icon);
  }
}

int pop_dead(piece * nfor, character * x, int size){
  int counter=0;
  character ctemp;
  piece ptemp;

  if(size==1 && x[0].hp<=0){return 0;}

  for(int i = 0; i < size-counter; i++){
    if(x[i].hp<=0){
      counter++;
      ctemp = x[size-counter];
      x[size-counter] = x[i];
      x[i] = ctemp;
      ptemp = nfor[size-counter];
      nfor[size-counter] = nfor[i];
      nfor[i] = ptemp;
    }
  }

  if(size==counter){return 0;}
  else{
    return size-counter;
  }
}

void battle(map min){
  string sinput;
  char cinput;

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

  int tempf=f;
  int tempe=e;

  for(int i = 0; i < field_now.height; i++){
    for(int j = 0; j < field_now.width; j++){
      if(field_now.grid[i][j]==1){
        tempf--;
        blufor[tempf] = piece (j, i, player_c[tempf].id);
      }
      if(field_now.grid[i][j]==2){
        tempe--;
        redfor[tempe] = piece (j, i, enemy_c[tempe].id);
      }
    }
  }

  field_now.clear_mark();

  while(e>0 && f>0){

    for(int i = 0; i < f; i++){
      while(cinput!='M' && cinput!='A'){
        //field_now.add_mark(blufor[i].x, blufor[i].y, player_c[i].spd, 0);
        renderer0.clear();

        draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
        renderer0.drawPoint(2, i*5+1, '>');
        renderer0.drawPoint(3*(blufor[i].x+1)+7, blufor[i].y+2, '>');
        renderer0.drawPoint(3*(blufor[i].x+1)+10, blufor[i].y+2, '<');
        renderer0.drawText(8, resolution[sel_resol][const_h]-2, "Enter capital letter to (M)ove or (A)ttack");

        renderer0.present();
        //field_now.clear_mark();

        cin >> sinput;
        cinput = sinput[0];
      }

      getline(cin, sinput);
      bool flag=true;
      while(flag){
        int x, y;

        field_now.add_mark(blufor[i].x, blufor[i].y, cinput=='M'?player_c[i].spd:player_c[i].rgn, 0);
        renderer0.clear();

        draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
        renderer0.drawPoint(2, i*4+1, '>');
        renderer0.drawPoint(3*(blufor[i].x+1)+7, blufor[i].y+2, '>');
        renderer0.drawPoint(3*(blufor[i].x+1)+10, blufor[i].y+2, '<');
        renderer0.drawText(8, resolution[sel_resol][const_h]-2, "Enter coordinate (X Y) to ");
        renderer0.drawText(34, resolution[sel_resol][const_h]-2, cinput=='M'?"move":"attack");

        if(cinput=='A'){
          for(int j=0; j<e; j++){
            if(field_now.grid[redfor[j].y][redfor[j].x]>0){
              renderer0.drawPoint(3*(redfor[j].x+1)+7, redfor[j].y+2, '[');
              renderer0.drawPoint(3*(redfor[j].x+1)+10, redfor[j].y+2, ']');
            }
          }
        }

        renderer0.present();

        getline(cin, sinput);
        istringstream iss (sinput);
        bool num = true;
        for(int i=0; i<sinput.size(); i++){
          if((sinput[i]<'0' || sinput[i]>'9') && (sinput[i] != ' ')){
            num = false;
            break;
          }
        }

        iss >> x >> y;
        //cout << x << y;

        int counter = 0;
        if(cinput=='A'){
          for(int j=0; j<e; j++){
            if(field_now.grid[redfor[j].y][redfor[j].x]>0){
              counter++;
            }
          }
        }
        else{counter++;}

        bool valid = cinput=='M'?true:false;
        int temp, dmg;
        if(x>=0 && x<field_now.width && y>=0 && y<field_now.height){
          //cout << "Checking";
          if(cinput=='M'){
            for(int j=0; j<f; j++){
              if(x==blufor[j].x && y==blufor[j].y){valid = false; break;}
            }
            for(int j=0; j<e; j++){
              if(x==redfor[j].x && y==redfor[j].y){valid = false; break;}
            }
            if(field_now.grid[y][x]<=0){valid = false;}
            if(valid){
              blufor[i].x=x;
              blufor[i].y=y;
            }
          }
          else{
            for(int j=0; j<e; j++){
              if(field_now.grid[redfor[j].y][redfor[j].x]>0 && x==redfor[j].x && y==redfor[j].y){
                dmg = player_c[i].atk - enemy_c[j].def / 2;
                dmg *= randDouble(0.8, 1.2);
                enemy_c[j].hp -= dmg;
                temp = j;
                valid=true;
                break;
              }
            }
          }
          if(valid){
            flag = false;
            field_now.clear_mark();

            renderer0.clear();

            draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
            renderer0.drawText(10, resolution[sel_resol][const_h]-2, player_c[i].icon);
            if(cinput == 'M'){
              renderer0.drawText(13, resolution[sel_resol][const_h]-2, "moved to ");
              renderer0.drawInt(22, resolution[sel_resol][const_h]-2, x);
              renderer0.drawInt(25, resolution[sel_resol][const_h]-2, y);
            }
            else{
              renderer0.drawText(13, resolution[sel_resol][const_h]-2, "attacked ");
              renderer0.drawText(22, resolution[sel_resol][const_h]-2, enemy_c[temp].icon);
              renderer0.drawText(25, resolution[sel_resol][const_h]-2, "for "+int_to_string(dmg));
            }

            renderer0.present();

            cout << "Enter anything to continue: ";
            cin >> sinput;

            cinput = ' ';
          }
        }

        //cout << counter;
        if(counter==0){flag=false; i--; cinput=' ';}

        field_now.clear_mark();
      }

      e = pop_dead(redfor, enemy_c, e);
    }

    for(int i = 0; i < e; i++){
      renderer0.clear();

      draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
      renderer0.drawPoint(2, i*4+1, '>');
      renderer0.drawPoint(3*(redfor[i].x+1)+7, redfor[i].y+2, '>');
      renderer0.drawPoint(3*(redfor[i].x+1)+10, redfor[i].y+2, '<');

      renderer0.present();

      f = pop_dead(blufor, player_c, f);
    }
  }

  renderer0.clear();
  if(e==0){
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(2, 2, "Victory");
    renderer0.drawText(2, 3, "You gained a new character!");
    playerdata.character_list.push_back(characters[randInt(0, 80)]);
    playerdata.save("./res/playerdata.txt");
  }
  else{
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(2, 2, "Defeated");
    playerdata.save("./res/playerdata.txt");
  }
  renderer0.present();
  cout << "Enter anything to continue: ";
  cin >> sinput;

  delete[] player_c;
  delete[] enemy_c;
  delete[] blufor;
  delete[] redfor;
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
      battle(map("./res/map/8_8_symmetric.txt"));
      sinput = " ";
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
