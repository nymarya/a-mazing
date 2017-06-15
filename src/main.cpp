#include <iostream>
#include <cassert>
#include "level.h"
#include "maze.h"

int main(int arcg, char** argv){

	Level lvl;

	//Caregar e imprimir fase
	lvl.load(argv[1]);
	lvl.print_lvl();
	
	//if(solve_maze( mz, mz.get_start_position() ) ){
	// 	//soluçao encontrada
	// //}
	// auto pos = mz.get_start_position();
	// std::cout << pos.roll << std::endl;
	// std::cout << pos.col << std::endl;

	// pos.col+=1;
	// pos.roll-=1;

	// mz.mark_cell(pos);

	// mz.render();

	// Maze::Position p;
	// p.roll = 0;
	// p.col = 2;

	// Maze::Direction d;
	// d.height = 0;
	// d.weight = 0;

	// assert ( mz.is_blocked(p, d));

	// pos.roll-=1;
	// pos.col+=1;
	// mz.mark_cell(pos);

	// assert( mz.is_marked(pos) == false);

	// mz.unmark_cell(pos);

	// assert( mz.is_marked(pos) == false);

	return 0;
}