#include <iostream>
#include "maze.h"

struct Position{
	std::size_t row;
	std::size_t col;
};

// bool solve_maze( const Maze& mz, const Position pos){

// }

int main(int arcg, char** argv){

	Maze mz;

	//Validar argumentos

	//Caregar labirinto
	mz.load(argv[1]);
	//if(solve_maze( mz, mz.get_start_position() ) ){
		//soluçao encontrada
	//}
	auto pos = mz.get_start_position();
	std::cout << pos.roll << std::endl;
	std::cout << pos.col << std::endl;

	pos.col+=1;
	pos.roll-=1;

	mz.mark_cell(pos);

	mz.render();

	return 0;
}