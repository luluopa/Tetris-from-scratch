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

void Print_screen(Map* mapa, Player* player){
	for(int i=0;i<24; i++){
		for(int j=0;j<20;j++){
			if(mapa->Mapa[i][j] == 1){
				cout << "#";
			}
			else if((i >= player->Get_y() && i <= player->Get_y()+4) &&
			(j >= player->Get_x() && j <= player->Get_x()+4)){
				if(player->block_player->Matriz[i-player->Get_y()][j-player->Get_x()] == 1){
					cout << "#";
				}
				else{
					cout << " ";
				}
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}
}

//implementação do get char para pegar uma entrada teclado e fazer o movimento 
//implementação do check lines e check lose
//implementação do score

void Rotation(Player* player){
    player->Rotation();
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
		update_screen();
		Print_screen(&mapa_do_jogo, &player);
		Movement(&mapa_do_jogo, &player);
		Check_lines(&mapa_do_jogo, &player);
	}

	return 0;
}