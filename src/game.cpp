#include "game.h"

Game::Result Game::validate( std::string filename){
    Result result;

    std::fstream file;
    file.open(filename);

    if(file.is_open()){

        std::size_t rolls(1ul);
        std::size_t cols(1ul);

        auto grid(1); //!< Sinaliza qual labirinto gera erro

        //Guarda os simbolos
        while(!file.eof()){
            std::string line;
            getline(file, line);

            if( not line.empty() ) {
                std::stringstream stream(line);

                stream >> rolls;
                stream >> cols;

                //!< Checa de dimensões são válidas
                if( rolls < Game::MIN_SIZE or cols < Game::MIN_SIZE 
                    or rolls > Game::MAX_SIZE or cols > Game::MAX_SIZE){
                    
                    result.success = false;
                    result.message = "Nivel "+ std::to_string(grid) +": Dimensões fora do intervalo permitido!";
                    return result;
                }
                

                while( rolls > 0){
                    getline(file, line);

                    //!< Se houver menos caracteres por linha
                    //do que o número de colunas, retorna erro
                    if( line.size() < cols){
                        result.success = false;
                        result.message = "Nivel " + std::to_string(grid) + ": Labirinto inválido!";
                        return result;
                    }
                    rolls--;
                }
                grid++;
            }
        }
    }

    file.close();

    return result;
}


void Game::initialize (std::string filename){

    Result result;

    //!< Preenche levels
    level.load( filename );

    //!< Gera maçã
    level.generate_apple();

    //!< Gera snake
    snake.grow( level.get_start_position() );

}