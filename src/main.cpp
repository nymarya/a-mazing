#include <iostream>
#include <cassert>
#include "game.h"

int main(int argc, char** argv){

	//!< Retorna erro se não foi passado arquivo
	if (argc < 2 ){
		std::cout << "Arquivo não encontrado! Por favor, tente novamente.\n";
		return EXIT_FAILURE;
	}

	Game game;

	//!< Validar argumentos
	Game::Result result = game.validate(argv[1]);
	if( not result.success){
		//!< Imprime mensagem de erro e encerra programa
		std::cout << result.message <<std::endl;

		return EXIT_FAILURE;
	}

	game.initialize( argv[1]);

	return EXIT_SUCCESS;
}