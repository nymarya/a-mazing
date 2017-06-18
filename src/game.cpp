#include "game.h"
ls::vector<Direction> direction = 
{
	Direction(-1, 0), //north
	Direction(1, 0),  //south
	Direction(0, -1), //east
	Direction(0, 1)   //west
};

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
    level.next_level();
    level.next_level();
    level.generate_apple();
    

    //!< Gera snake
    snake.update_state( Snake::SnakeState::RUN );
    snake.grow( level.get_start_position() );

    auto map = level.get_level();
    bool yes = player.find_solution( map );
    if (yes){
        player.print();
    }
    else std::cout << "Tem solução não!\n";
}

/// Processa eventos do jogo
void Game::process_events( void ){

    //player.find

    //Se comeu todas as maças, passa de Nivel, acha nova soluçao
    if( level.get_apples() == 0 and 
        level.get_current_lvl() != level.get_total_lvls() )
    {

        level.next_level();     //!< Muda de nível
        level.generate_apple(); //!< Gera nova maçã
        //player.find_solution(); //!< Busca a solução do novo nível
    } 
    //Se não tem mais maçãs nem níveis, fim de jogo
    else if ( level.get_apples() == 0 and 
              level.get_current_lvl() == level.get_total_lvls() )
    {
        snake.update_state( Snake::SnakeState::WIN );
    }
    //Se a cobra 
    else if( snake.get_state() == Snake::SnakeState::CRASH ) 
    {
        //Se o jogador ainda tiver vidas, muda de Nivel
        // Caso contrario, cobra morre
    } 
    else
    {

    }

}

/// Atualiza elementos do jogo
void Game::update()
{
    auto dir = player.next_move();

    //Se a nova posição for a mação, cresce
    // se for parede, CRASH
    //Caso contrário, movimenta cobra
    auto pos = snake.get_position() + direction[(int)dir];
    while( not level.is_solution( pos ) ){
        snake.move( pos);
        dir = player.next_move();
        pos = snake.get_position() + direction[(int)dir];
        render();
    }
    snake.move( pos);
    render();


}

void Game::render()
{
    std::this_thread::sleep_for (std::chrono::milliseconds(150)); //!< Delay

    auto map = level.get_level();
    auto snake_body = snake.get_body();
    auto size_snake(0ul);
    for( auto roll(0ul); roll < level.get_rolls() ; ++roll){
        for(auto col(0ul); col < level.get_cols(); ++col){
            if( size_snake < snake.size() ){
                auto pos = std::find(snake_body.begin(), snake_body.end(), Position(roll, col));
                if( pos == snake_body.begin() )
                {
                    std::cout << snake.get_head();
                    size_snake++;
                }
                else if ( pos != snake_body.end())
                {
                    std::cout << "\u25C8";
                    size_snake++;
                } else{
                    if( level.is_solution( Position(roll, col) ))
                        std::cout << "*";
                    else if( map[roll][col] == '#')
                        std::cout << "\u22A0";
                    else 
                        std::cout << " ";
                }
            } 
            else{
                if( level.is_solution( Position(roll, col) ))
                    std::cout << "*";
                else if( map[roll][col] == '#')
                    std::cout << "\u22A0";
                else 
                    std::cout << " ";
            }
      }
      std::cout << std::endl;
  }
}

bool Game::game_over(){
    return ( (snake.get_state() == Snake::SnakeState::DEAD )
                or (snake.get_state() == Snake::SnakeState::WIN ) );
}