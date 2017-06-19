#include <iostream>
#include <cassert>
#include "game.h"
#include "player.h"

int main(int argc, char** argv){

	//!< Retorna erro se não foi passado arquivo
	if (argc < 2 ){
		std::cout << "Arquivo não encontrado! Por favor, tente novamente.\n";
		return EXIT_FAILURE;
	}

	Game game;

	// //!< Validar argumentos
	// Game::Result result = game.validate(argv[1]);
	// if( not result.success){
	// 	//!< Imprime mensagem de erro e encerra programa
	// 	std::cout << result.message <<std::endl;

	// 	return EXIT_FAILURE;
	// }

	//game.initialize( argv[1]);
	//game.render();

	// while( not game.game_over() ){
	// 	game.process_events();
	// 	game.update();
	// 	game.render();
	// }

	Move mv;
	std::stack<Move> teste;
	mv.pos = Position(0,0);
	mv.dir = direction_t::EAST;
	teste.push(mv);

	if(teste.top().dir == direction_t::EAST){
		std::cout <<"ok" << (int) teste.top().dir;
	}


	mv.dir = direction_t::SOUTH;
	teste.push(mv);

	if(teste.top().dir == direction_t::SOUTH){
		std::cout <<"ok" << (int) teste.top().dir;
	}


	return EXIT_SUCCESS;
}