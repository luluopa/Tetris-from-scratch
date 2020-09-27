#include <stdlib.h>
#include <iostream>
#include "Class.h"

using namespace std;

const short int Up = 38;
const short int Down = 40;
const short int Right = 39;
const short int Left = 37;

void update_screen(){
	system("clear");
}

void Print_screen(Map* mapa){
	for(int i=0;i<mapa->Mapa.size(); i++){
		for(int j=0;j<mapa->Mapa[i].size();i++){
			if(mapa->Mapa[i][j] == 1){
				cout << "#";
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}
}

void Rotation(Map* mapa, Player* player){
    player->Rotation();
	mapa->assing(player);
}
 
void Movement(Map* mapa, Player* player){
	if(mapa->Check_touch_next(player->block_player->Matriz, player->Get_x(), player->Get_y()+1)){
		player->Increment_y();
	}
	else{
		mapa->assing(player);
		player->Restart();
	}
}

void Check_lines(Map* mapa, Player* player){
	mapa->Check_score(player);
}

int main(){

	Map mapa_do_jogo;
	Player player;
	//loop do jogo
	while(true){
		Print_screen(&mapa_do_jogo);
		Movement(&mapa_do_jogo, &player);
		Check_lines(&mapa_do_jogo, &player);
		update_screen();
	}

	return 0;
}