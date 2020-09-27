#include <vector>
#include <iostream>
#include "Class.h"
#include <random>

using namespace std;

const int tam_y = 5;
const int tam_x = 5;

//tamanho do mapa
const short int map_y = 10;
const short int map_x = 10;

Map::Map()
{
	Mapa.assign(map_y, vector<int>(map_x, 0));
	for (int i = 0; i < map_y; i++)
	{
		for (int j = 0; j < map_x; j++)
		{
			if (i == 0 || i == map_y - 1 || j == 0 || j == map_x - 1)
			{
				Mapa[i][j] = 1;
			}
			else
			{
				Mapa[i][j] = 0;
			}
		}
	}
}
bool Map::Check_touch_next(vector<vector<int>> Matriz, int new_pos_x, int new_pos_y)
{
	vector<int> vector_vnx;
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (Matriz[i][j] == 1)
			{
				vector_vnx.push_back(i + new_pos_y);
				vector_vnx.push_back(j + new_pos_x);
			}
		}
	}
	for (int i = 0; i < vector_vnx.size(); i += 2)
	{
		if (Mapa[vector_vnx[i] - 1][vector_vnx[i + 1]] == 1)
		{
			return false;
		}
	}
	return true;
}

void Map::assing(Player *player)
{
	vector<int> vector_vnx;
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (player->block_player->Matriz[i][j] == 1)
			{
				vector_vnx.push_back(i + player->Get_y());
				vector_vnx.push_back(j + player->Get_x());
			}
		}
	}
	for (int i = 0; i < vector_vnx.size(); i += 2)
	{
		Mapa[vector_vnx[i]][vector_vnx[i + 1]] = 1;
	}
}

void Map::Check_score(Player* player){
		vector<int> vector_ipos;
		for(int i=0;i<map_y;i++){
			int counter=0;
			for(int j=0;j<map_x;j++){
				if(Mapa[i][j] == 1){
					counter++;
				}
			}
			if(counter == map_x){
				vector_ipos.push_back(i);
			}
		}
		int aux=-1;
		for(int i=0;i<vector_ipos.size();i++){
			for(int j=0;j<map_x;j++){
				aux = Mapa[vector_ipos[i]-vector_ipos.size()][j];
				Mapa[vector_ipos[i]-vector_ipos.size()][j] = 0;
				Mapa[vector_ipos[i]][j] = 1;
			}
		}
		player->Add_score(vector_ipos.size()*4);
	}

	bool Map::Check_lose(Player* player){
		int x = player->Get_x();
		int y = player->Get_y();
		if(x == 3 && y == 3 && !Check_touch_next(player->block_player->Matriz,x,y)){
			return true;
		}  
		return false;
	}

//player

Player::Player()
{
	random();
	new_pointer();
	x = 3;
	y = 3;
}
void Player::random()
{
	//muda o type entre 0 e 6
	type = rand() % 7;
}
void Player::new_pointer()
{
	if (type == 0)
	{
		block_player = new Block_l(type);
	}
	else if (type == 1)
	{
		block_player = new Block_l(type);
	}
	else if (type == 2)
	{
		block_player = new Block_cloud(type);
	}
	else if (type == 3)
	{
		block_player = new Block_cloud(type);
	}
	else if (type == 4)
	{
		block_player = new Block_stab(type);
	}
	else if (type == 5)
	{
		block_player = new Block_triangle(type);
	}
	else
	{
		block_player = new Block_square(type);
	}
}
void Player::Rotation()
{
	if (type == 2 || type == 3)
	{
		block_player->control_rotate();
	}
	else
	{
		block_player->control_rotate();
	}
}

void Player::Restart(){
	random();
	new_pointer();
	x = 3;
	y = 3;
}

int Player::Get_x()
{
	return x;
}

int Player::Get_y()
{
	return y;
}

void Player::Increment_x()
{
	x++;
}

void Player::Increment_y(){
	y++;
}

void Player::Add_score(int attempt){
	points+=attempt;
}

//Block

Block::Block(int state, int type, bool check)
{
	this->state = state;
	this->type = type;
	if (!check)
	{
		Matriz.assign(tam_y, std::vector<int>(tam_x, 0));
	}
}

int Block::get_type(){
	return type;
}
int* Block::get_adress_state(){
	return &state;
}

void Block::control_rotate()
{
	if (type == 2 || type == 3)
	{
		if (state == 0)
		{
			rotate();
			state++;
		}
		else
		{
			rotate_negative();
			state--;
		}
	}
	else
	{
		rotate();
	}
}
void Block::rotate()
{
	//i am going to do some magic here
	vector<int> vector_vnx;
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (Matriz[i][j] == 1)
			{
				vector_vnx.push_back(4 - j);
				vector_vnx.push_back(i);
			}
			Matriz[i][j] = 0;
		}
	}
	for (int i = 0; i < vector_vnx.size(); i += 2)
	{
		Matriz[vector_vnx[i]][vector_vnx[i + 1]] = 1;
	}
}
void Block::rotate_negative()
{
	//i am going to do some magic here
	vector<int> vector_vnx;
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (Matriz[i][j] == 1)
			{
				vector_vnx.push_back(j);
				vector_vnx.push_back(4 - i);
			}
			Matriz[i][j] = 0;
		}
	}
	for (int i = 0; i < vector_vnx.size(); i += 2)
	{
		Matriz[vector_vnx[i]][vector_vnx[i + 1]] = 1;
	}
}

//Block_l

Block_l::Block_l(int type) : Block::Block(type, -1)
{
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (i == 2 && j >= 1 && j <= 3 && (type == 0))
				Matriz[i][j] = 1;
			else if (j == 1 && i == 1 && (type == 0))
				Matriz[i][j] = 1;
			else if (i == 2 && j >= 1 && j <= 3 && (type == 1))
				Matriz[i][j] = 1;
			else if (j == 3 && i == 1 && (type == 1))
				Matriz[i][j] = 1;
			else
			{
				Matriz[i][j] = 0;
			}
		}
	}
}

//Block_cloud

Block_cloud::Block_cloud(int type) : Block::Block(type, 0)
{
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (i == 2 && j >= 1 && j <= 2 && (type == 2))
				Matriz[i][j] = 1;
			else if (i == 1 && j >= 2 && j <= 3 && (type == 2))
				Matriz[i][j] = 1;
			else if (i == 2 && j >= 2 && j <= 3 && (type == 3))
				Matriz[i][j] = 1;
			else if (i == 1 && j >= 1 && j <= 2 && (type == 3))
				Matriz[i][j] = 1;
			else
			{
				Matriz[i][j] = 0;
			}
		}
	}
}

//Block_square

Block_square::Block_square(int type) : Block::Block(type, -1)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Matriz[i][j] = 1;
		}
	}
}

//Block_triangle

Block_triangle::Block_triangle(int type) : Block::Block(type, -1)
{
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (i == 2 && j >= 1 && j <= 3)
				Matriz[i][j] = 1;
			else if (j == 2 && i == 1)
			{
				Matriz[i][j] = 1;
			}
			else
			{
				Matriz[i][j] = 0;
			}
		}
	}
}

//Block_stab

Block_stab::Block_stab(int type) : Block::Block(type,-1)
{
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			if (i == 2)
				Matriz[i][j] = 1;
			else
			{
				Matriz[i][j] = 0;
			}
		}
	}
}