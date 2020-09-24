#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

const int tam_y = 3;
const int tam_x = 4;

class Block{
public:
	std::vector<std::vector<int>> Matriz;
public:
	Block(bool check = false){
		if (!check){
			Matriz.assign(tam_y, std::vector<int>(tam_x, 0));
		}
	}
	void plot_screen(){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 4; j++){
				cout << Matriz[i][j];
			}
			cout << endl;
		}
	}
};

class Block_l : public Block{
public:
	Block_l() : Block(){
		for (int i = 0; i < tam_y; i++){
			for (int j = 0; j < tam_x; j++){
				if (j == 0)
					Matriz[i][j] = 1;
				else if (j == 1 && i == 2)
					Matriz[i][j] = 1;
				else{
					Matriz[i][j] = 0;
				}
			}
		}
	}
	void rotate(){
		//i am going to do some magic here
		vector<int> vector_vnx(8);
		int index=0;
		int counter=0;
		cout << "rotacionando... \n";
		for (int i = 0; i < tam_y; i++){
			for (int j = 0; j < tam_x-1; j++){
				if (Matriz[i][j] == 1 && counter < 4){
					 vector_vnx[index] = i;
					 vector_vnx[index + 1] = 2-j;
					 index+=2;
					 counter++;
				}
				Matriz[i][j] = 0;
			}
		}
		for(int i=0;i<8;i+=2){
			Matriz[vector_vnx[i+1]][vector_vnx[i]] = 1;
		}
	}
};

void rotate(Block_l *am_pont){
	char ch;
	cout << "deseja rotacionar?";
	cin >> ch;
	if (ch == 's' || ch == 'S'){
		am_pont->rotate();
	}
}

void update_screen(){
	system("cls");
}

int main(){
	Block_l ami;

	while (true){
		ami.plot_screen();
		rotate(&ami);
		update_screen();
	}

	return 0;
}