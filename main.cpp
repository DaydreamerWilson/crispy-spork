#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "library.h"
#include "render.h"

using namespace std;

renderer renderer0(100, 150);
map test_map("./res/test_map.txt");
map test_img("./res/test_img.txt");
string sinput;
player playerdata;

// set resolution and calibrate by user
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

// draw screen for character information
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

// choose characters before battle
void choose_character(int f, int e, character * player_c, character * enemy_c){
  int page = 1, chose = 0;
  int max_page = ((playerdata.character_list.size()-1)/(resolution[sel_resol][const_h]-10))+1;;
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
      int temp;
      istringstream iss (sinput);
      iss >> temp;
      bool flag2 = true;
      for(int i = 0; i<playerdata.character_list.size(); i++){
        if(playerdata.character_list[i].id==temp){
          for(int j = 0; j < chose; j++){
            if(player_c[j].id == temp){
              flag2 = false;
              break;
            }
          }
          if(flag2){
            player_c[chose] = playerdata.character_list[i];
            playerdata.character_list[i].flag = true;
            chose++;
            break;
          }
          else{
            cout << "You can't select the same character twice!" << endl;
            cout << "Enter anything to continue: ";
            cin >> sinput;
            break;
          }
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

// draw battle screen
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

// check if chess piece on board is eliminated
int pop_dead(piece * nfor, character * x, int size, int p){
  int counter=0;
  character ctemp;
  piece ptemp;

  if(size==1 && x[0].hp<=0){
    if(p){
      for(int j = 0; j < playerdata.character_list.size(); j++){
        if(playerdata.character_list[j].id==x[0].id){
          playerdata.character_list.erase(playerdata.character_list.begin()+j);
          break;
        }
      }
    }
    return 0;
  }

  for(int i = 0; i < size-counter; i++){
    if(x[i].hp<=0){
      if(p){
        for(int j = 0; j < playerdata.character_list.size(); j++){
          if(playerdata.character_list[j].id==x[i].id){
            playerdata.character_list.erase(playerdata.character_list.begin()+j);
            break;
          }
        }
      }
      counter++;
      ctemp = x[size-counter];
      x[size-counter] = x[i];
      x[i] = ctemp;
      ptemp = nfor[size-counter];
      nfor[size-counter] = nfor[i];
      nfor[i] = ptemp;
    }
  }

  if(size==counter){
    if(p){
      for(int i = 0; i < size-counter; i++){
        for(int j = 0; j < playerdata.character_list.size(); j++){
          if(playerdata.character_list[j].id==x[i].id){
            playerdata.character_list.erase(playerdata.character_list.begin()+j);
            break;
          }
        }
      }
    }
    return 0;
  }
  else{
    return size-counter;
  }
}

// main battle running process
void battle(map min){
  string sinput;
  char cinput;

  // initiate null pointer to store chess piece for both side
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

  // add character to both side
  choose_character(f, e, player_c, enemy_c);

  int tempf=f;
  int tempe=e;

  // placing characters on board
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

  // run battle process
  while(e>0 && f>0){

    // run for each player controlled character
    for(int i = 0; i < f; i++){
      // check which move player what to use
      while(cinput!='M' && cinput!='A'){
        renderer0.clear();

        draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
        renderer0.drawPoint(2, i*5+1, '>');
        renderer0.drawPoint(3*(blufor[i].x+1)+7, blufor[i].y+2, '>');
        renderer0.drawPoint(3*(blufor[i].x+1)+10, blufor[i].y+2, '<');
        renderer0.drawText(8, resolution[sel_resol][const_h]-2, "Enter capital letter to (M)ove or (A)ttack");

        renderer0.present();
        cout << "Please enter your command: ";

        cin >> sinput;
        cinput = sinput[0];
      }

      getline(cin, sinput);
      bool flag=true;
      while(flag){
        int x, y;

        // show player available location for moving or attacking
        // input player decided location

        field_now.add_mark(blufor[i].x, blufor[i].y, cinput=='M'?player_c[i].spd:player_c[i].rgn, 0);
        renderer0.clear();

        draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
        renderer0.drawPoint(2, i*5+1, '>');
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

        cout << "Please enter a coordinate: ";

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

        int counter = 0;
        if(cinput=='A'){
          for(int j=0; j<e; j++){
            if(field_now.grid[redfor[j].y][redfor[j].x]>0){
              counter++;
            }
          }
        }
        else{counter++;}

        // check if player movement or attack is valid
        bool valid = cinput=='M'?true:false;
        int temp, dmg;
        if(x>=0 && x<field_now.width && y>=0 && y<field_now.height){
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

                if(player_c[i].atk > enemy_c[j].def*2){
                  dmg = player_c[i].atk;
                }
                else if(player_c[i].atk*2 < enemy_c[j].def){
                  dmg = 1;
                }
                else{
                  dmg = player_c[i].atk - enemy_c[j].def/2;
                }

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

            // print final product and show what move player did
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
        if(counter==0){flag=false; i--; cinput=' ';}

        field_now.clear_mark();
      }

      // check if game ended and if any enemy died turning this turn
      e = pop_dead(redfor, enemy_c, e, 0);
      if(e == 0){break;}
    }

    // run for each computer controlled characters
    for(int i = 0; i < e; i++){
      renderer0.clear();

      int temp, dmg;
      int x, y;
      int dx, dy;
      field_now.clear_mark();
      field_now.add_mark(redfor[i].x, redfor[i].y, enemy_c[i].rgn, 0);

      // decide move for computer controlled character

      // attack target in range
      bool hasTarget = false;
      for(int j = 0; j < f; j++){
        if(field_now.grid[blufor[j].y][blufor[j].x]>0){
          x = blufor[j].x;
          y = blufor[j].y;
          cinput = 'A';
          hasTarget = true;

          if(enemy_c[i].atk > player_c[j].def*2){
            dmg = enemy_c[i].atk;
          }
          else if(enemy_c[i].atk*2 < player_c[j].def){
            dmg = 1;
          }
          else{
            dmg = enemy_c[i].atk - player_c[j].def/2;
          }

          dmg *= randDouble(0.8, 1.2);
          player_c[j].hp -= dmg;
          temp = j;
        }
      }

      // move to a different position if no target in range
      if(!hasTarget){
        field_now.clear_mark();
        field_now.add_mark(redfor[i].x, redfor[i].y, enemy_c[i].spd, 0);

        while(!hasTarget){
          dx = randInt(0, enemy_c[i].spd+1);
          dy = randInt(0, enemy_c[i].spd-dx+1);
          dx += 2*(randInt(0, 2)*-1)*dx;
          dy += 2*(randInt(0, 2)*-1)*dy;
          if(redfor[i].y+dy >= 0 && redfor[i].y+dy < field_now.height &&
             redfor[i].x+dx >= 0 && redfor[i].x+dx < field_now.width &&
             !(dx == 0 && dy == 0)
             ){
            if(field_now.grid[redfor[i].y+dy][redfor[i].x+dx]>0){
              bool not_occupied = true;
              for(int j = 0; j < e; j++){
                if(redfor[j].x == redfor[i].x+dx && redfor[j].y == redfor[i].y+dy){
                  not_occupied = false;
                }
              }
              for(int j = 0; j < f; j++){
                if(blufor[j].x == redfor[i].x+dx && blufor[j].y == redfor[i].y+dy){
                  not_occupied = false;
                }
              }
              if(not_occupied){
                redfor[i].x += dx;
                redfor[i].y += dy;
                x = redfor[i].x;
                y = redfor[i].y;
                hasTarget = true;
              }
            }
          }
        }

        cinput = 'M';
      }

      field_now.clear_mark();

      draw_battle(field_now, blufor, redfor, player_c, enemy_c, f, e);
      renderer0.drawPoint(resolution[sel_resol][const_w]-5, i*5+1, '>');
      renderer0.drawPoint(3*(redfor[i].x+1)+7, redfor[i].y+2, '>');
      renderer0.drawPoint(3*(redfor[i].x+1)+10, redfor[i].y+2, '<');

      // show what move computer controlled character did
      renderer0.drawText(10, resolution[sel_resol][const_h]-2, enemy_c[i].icon);
      if(cinput == 'M'){
        renderer0.drawText(13, resolution[sel_resol][const_h]-2, "moved to ");
        renderer0.drawInt(22, resolution[sel_resol][const_h]-2, x);
        renderer0.drawInt(25, resolution[sel_resol][const_h]-2, y);
      }
      else{
        renderer0.drawText(13, resolution[sel_resol][const_h]-2, "attacked ");
        renderer0.drawText(22, resolution[sel_resol][const_h]-2, player_c[temp].icon);
        renderer0.drawPoint(3*(blufor[temp].x+1)+7, blufor[temp].y+2, '[');
        renderer0.drawPoint(3*(blufor[temp].x+1)+10, blufor[temp].y+2, ']');
        renderer0.drawText(25, resolution[sel_resol][const_h]-2, "for "+int_to_string(dmg));
      }


      renderer0.present();

      cout << "Enter anything to continue: ";
      cin >> sinput;
      cinput = ' ';

      // check if game ended and if any user controlled character died during this turn
      f = pop_dead(blufor, player_c, f, 1);
      if(f == 0){break;}
    }
  }

  renderer0.clear();
  if(e==0){
    // draw victory screen and add new character for player and auto save
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(2, 2, "Victory");
    renderer0.drawText(2, 3, "You gained a new character!");

    int a = randInt(0, totalchar);
    playerdata.character_list.push_back(characters[a]);
    playerdata.save("./res/playerdata.txt");

    cout << "Please enter anything to view the character: ";
    cin >> sinput;

    for(int i = 0; i<playerdata.character_list.size(); i++){
      renderer0.clear();
      renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
      print_character(characters[a]); // print out character data selected by user
      renderer0.present();
      cout << "Please enter anything to continue: ";
      cin >> sinput;
    }
  }
  else{
    // draw defeated screen and auto save
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(2, 2, "Defeated");
    playerdata.save("./res/playerdata.txt");
  }
  renderer0.present();
  cout << "Enter anything to continue: ";
  cin >> sinput;

  // remove temporary pointer storing chess pieces data
  delete[] player_c;
  delete[] enemy_c;
  delete[] blufor;
  delete[] redfor;
}

int main(){
  // loading all characters
  load_characters("./res/characters");

  // initiate random seeds and auto checking
  init_rand();

  // loading playerdata
  playerdata.load("./res/playerdata.txt");

  renderer0.clear();

  set_resolution();

  while(sinput!="QUIT"){
    // print out main menu and available options
    renderer0.clear();
    renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
    renderer0.drawText(2, 2, "Main menu");
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
    case 'C':
      // initiate battle with map class
      cout << "Default test map: ./res/map/8_8_symmetric.txt" << endl;
      cout << "Please enter map link, or (D) to use default map: ";
      cin >> sinput;
      if(sinput[0]=='D'){
        battle(map("./res/map/8_8_symmetric.txt"));
      }
      else{
        if(sinput.rfind(".txt")!=sinput.length()-4){
          cout << "fatal error loading map: syntax error" << endl;
          cout << "Enter anything to continue: ";
          cin >> sinput;
          break;
        }

        ifstream file;
        file.open(sinput);
        if(file.fail()){
          cout << "fatal error loading map: file failed" << endl;
          cout << "Enter anything to continue: ";
          cin >> sinput;
          break;
        }
        file.close();

        battle(map(sinput));
      }
      sinput = " ";
      break;
    case 'S':
      // saving the player data and print out success message
      playerdata.save("./res/playerdata.txt");
      renderer0.clear();
      renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
      renderer0.drawText(2, 2, "Player data successfully saved");
      renderer0.present();
      cout << "Please enter anything to continue: ";
      cin >> sinput;
      break;
    case 'I':
      // print out character list owned by player
      {
        int page = 1;
        int max_page = ((playerdata.character_list.size()-1)/(resolution[sel_resol][const_h]-10))+1;
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
            int temp;
            istringstream iss (sinput);
            iss >> temp;
            for(int i = 0; i<playerdata.character_list.size(); i++){
              if(playerdata.character_list[i].id==temp){
                renderer0.clear();
                renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
                print_character(characters[playerdata.character_list[i].id-1]); // print out character data selected by user
                renderer0.present();
                cout << "Please enter anything to continue: ";
                cin >> sinput;
                break;
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
      set_resolution(); // call the set_resolution function
      break;
    case 'E':
      // auto save player data, then print out terminating screen
      playerdata.save("./res/playerdata.txt");
      renderer0.clear();
      renderer0.drawRectangle(0, 0, resolution[sel_resol][const_h], resolution[sel_resol][const_w], '*');
      renderer0.drawText(5, 5, "Player data successfully saved");
      renderer0.drawText(5, 6, "Terminating game...");
      renderer0.present();
      sinput = "QUIT"; // exit the game
      break;
    }
  }
}
