#include <stdlib.h>
#include <iostream>
#include "Class.h"
#include <conio.h>
#include <windows.h>

using namespace std;

const short int Up = 72;
const short int Down = 80;
const short int Right = 77;
const short int Left = 75;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void update_screen(){
	system("cls");
}

void Print_player(Player* player){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(player->block_player->Matriz[i][j] == 1){
				gotoxy(j+player->Get_x()+1,i+player->Get_y());
				cout << "#";
			}
		}
	}
}

void Erase_old(vector<vector<int> > antigo,int x_antigo,int y_antigo){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(antigo[i][j] == 1){
				gotoxy(j+x_antigo+1,i+y_antigo);
				cout << " ";
			}
		}
	}
}

void Print_screen(Map* mapa, Player* player){
	for(int i=0;i<24; i++){
		for(int j=0;j<20;j++){
			if(mapa->Mapa[i][j] == 1){
				cout << "#";
				if(i == 0 && j == 19){
					cout << " Score: " << player->Get_points();
				}
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}
}

void Rotation(Player* player){
    player->Rotation();
}

void Get_char(Map* mapa, Player* player, int i){
		if(_kbhit() && _getch() == 'z'){
			Rotation(player);
		}
		else if(GetAsyncKeyState(VK_LEFT) && i % 2 == 0){
			if(mapa->Check_touch_next(player->block_player->Matriz, player->Get_x()-1, player->Get_y())){
		    	player->Increment_x(-1);
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT) && i % 2 == 0){
			if(mapa->Check_touch_next(player->block_player->Matriz, player->Get_x()+1, player->Get_y())){
		    	player->Increment_x(1);
			}
		}
		else if(GetAsyncKeyState(VK_DOWN) && i % 2 == 0){
			if(mapa->Check_touch_next(player->block_player->Matriz, player->Get_x(), player->Get_y()+1)){
		    	player->Increment_y();
			}
		}
	}
 
void Movement(Map* mapa, Player* player){
	static float next_y=0;
	if(mapa->Check_touch_next(player->block_player->Matriz, player->Get_x(), player->Get_y()+1)){
		if(next_y == 1){
			player->Increment_y();
			next_y=0;
		}
		else
		    next_y+=0.25;
	}
	else{
		mapa->assing(player);
		update_screen();
		Print_screen(mapa, player);
		player->Restart();
	}
}

void Check_lines(Map* mapa, Player* player){
	mapa->Check_score(player);
}

void Control_player_output(Player* player, vector<vector<int> >* antigo, int* antigo_x, int* antigo_y){
	*antigo = player->block_player->Matriz;
	*antigo_x = player->Get_x();
	*antigo_y = player->Get_y();
	Erase_old(*antigo, *antigo_x, *antigo_y);
}

void voce_perdeu(Player* player)
{
	system("cls");
	gotoxy(17,10);
	cout << " ";
	std::cout << "voce perdeu, sua pontuacao foi: "  << player->Get_points() << std::endl;
	gotoxy(20,11);
	cout << " ";
	std::cout << " deseja continuar[s/n]";
	gotoxy(30,13);
	cout << " ";
	std::cout << "[Sim]";
	gotoxy(30,14);
	cout << " ";
	std::cout << "[Nao]";
}

bool check_if_want_continue(Player* player)
{
	//primeiramente apago a tela depois coloca a posi��o do ponteiro
	//e fica um gui bonitinho 
	system("cls");
	voce_perdeu(player);
	int pos_y = 13;
	bool check_while = 1;
	while(check_while)
	{
		char keyboard_char;
		gotoxy(37,pos_y);
		cout << "<";	
		if(kbhit())
		{	
			//se o usuario mexer no teclado a seta eu mudo a posi��o dela
			//dependendo do y em que o usuario der enter no caso s� dois
			//y, eu dou reset no jogo ou acabo o jogo
		    keyboard_char = int(getch());
			switch(keyboard_char)
			{
			case Down:
				if(pos_y == 13)
				{
					pos_y++;
					gotoxy(37,pos_y-1);
					cout << " ";
				}
				break;
			case Up:
				if(pos_y == 14)
				{
					pos_y--;
					gotoxy(37,pos_y+1);
					cout << " ";						
				}
				break;
			case 13:
				if(pos_y == 13)
				{
					return true;			
				}
				else if(pos_y == 14)
				{
					return false;
				}
				break;
			}
		}
	  }
}

bool Check_lose_n(Map* mapa, Player* player){
	return(mapa->Check_lose(player));
}

void Check_if_lost(Map** mapa_do_jogo, Player** player, int& continue_ck){
	if(Check_lose_n(*mapa_do_jogo, *player)){
			cout << "entrou";
			if(check_if_want_continue(*player)){
				*mapa_do_jogo = new Map;
				*player = new Player;
				system("cls");
				Print_screen(*mapa_do_jogo, *player);
			}
			else{
				continue_ck = 0;
			}
		}
}

int main(){

	Map* mapa_do_jogo;
	Player* player;
	mapa_do_jogo = new Map;
	player = new Player;
	//loop do jogo
	Print_screen(mapa_do_jogo, player);
	vector<vector<int> > antigo;
	int antigo_x,antigo_y,i=0;
	int continue_ck = 1;
	while(continue_ck){
		Sleep(30);
		Control_player_output(player, &antigo, &antigo_x, &antigo_y);
        Get_char(mapa_do_jogo, player, i);
        Check_lines(mapa_do_jogo, player);
		Movement(mapa_do_jogo, player);
		Print_player(player);
		i++;
		Check_if_lost(&mapa_do_jogo, &player, continue_ck);
	}
	cout << "\n\n\n\n";
	return 0;
}