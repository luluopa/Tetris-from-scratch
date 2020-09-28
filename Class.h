#ifndef Class.h
#define Class.h

#include <vector>

using namespace std;

class Block{
public:
	vector<vector<int> > Matriz;
	int type;
	int state;
public:
	Block(int state, int type, bool check = false);
	void control_rotate();
	int get_type();
	int* get_adress_state();
private:
	void rotate();
	void rotate_negative();
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
private:
	void random();
	void new_pointer();
public:
	void Rotation();
	void Restart();
	int Get_x();
	int Get_y();
	void Increment_x();
	void Increment_y();
	void Add_score(int attempt=1);
};

class Map{
public:
    vector<vector<int> > Mapa;
public:
    // 
    Map();
	bool Check_touch_next(vector<vector<int> > Matriz, int new_pos_x, int new_pos_y);
	void assing(Player* player);
	void Check_score(Player* player);
	bool Check_lose(Player* player);
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