#include <iostream>
#include "maze.h"

struct Position{
	std::size_t row;
	std::size_t col;
};

bool solve_maze( const Maze& mz, const Position pos){

}

int main(){

	Maze mz;

	//Validar argumentos

	//Caregar labirinto
	mz.load_board(argv[1]);
	if(solve_maze( mz, mz.get_start_position() ) ){
		//soluçao encontrada
	}
}