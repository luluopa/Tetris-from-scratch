#ifndef Class.h
#define Class.h

#include <vector>
#include <string>

using namespace std;

class Map{
public:
    vector<vector<int>> Mapa;
public:
    // 
    Map();
	bool Check_touch_next(vector<vector<int>> Matriz, int new_pos_x, int new_pos_y);
	void assing(Player* player);
	void Check_score(Player* player);
	bool Check_lose(Player* player);
};

class Player{
	//logica do score
private:
    int type;
	int points;
	short int x,y;
public:
	Block* block_player;
    Player();
	void random();
	void new_pointer();
	void Rotation();
	void Movement(char move);
	int Get_x();
	int Get_y();
	void Increment_x();
	void Add_score(int attempt=1);
};

class Block{
public:
	vector<vector<int>> Matriz;
public:
	Block(bool check = false);
	void control_rotate(int type=0, int* state=NULL);
private:
	void rotate();
	void rotate_negative();
};

class Block_l : public Block{
private:
    int type;
public:
	Block_l(int type);
};

class Block_cloud : public Block{
private:
    int type;
	int state;
public:
    Block_cloud(int type);
	int get_type();
	int* get_adress_state();
};

class Block_square : public Block{
private:
    int type;
public:
    Block_square(int type);
};

class Block_triangle : public Block{
private:
    int type;
public:
    Block_triangle(int type);
};

class Block_stab : public Block{
private:
    int type;
public:
	Block_stab(int type);
};

#endif