#include <iostream>
#include <cassert>
#include "maze.h"
#include "game.h"



int main(int arcg, char** argv){

	Game game;

	//!< Validar argumentos
	Game::Result result = game.validate(argv[1]);
	if( not result.success){
		//!< Imprime mensagem de erro e encerra programa
		std::cout << result.message <<std::endl;

		return EXIT_FAILURE;
	}

	return 0;
}