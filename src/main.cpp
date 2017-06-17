#include <iostream>
#include <cassert>
#include "level.h"
#include "maze.h"

int main(int arcg, char** argv){

	Level lvl;

	//Carregar e imprimir fase
	lvl.load(argv[1]);
	lvl.print_lvl();

	Position p;
	p.roll = 1;
	p.col = 1;

	lvl.mark_position( p );

	p.roll = 2;
	p.col = 2;

	lvl.mark_notsolution(p);

	p.col = 3;

	lvl.mark_decision(p);

	lvl.generate_apple();

	p = lvl.get_start_position();

	std::cout << "l: "<< p.roll << " c: " << p.col << std::endl;

	lvl.print_lvl();
	std::cout << "apples restantes: " << lvl.get_apples() << std::endl;

	lvl.next_level();
	lvl.print_lvl();
	lvl.next_level();
	lvl.print_lvl();
	lvl.next_level();
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