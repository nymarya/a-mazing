#include "player.h"
#include <functional> //<! std::hash


ls::vector<Direction> directions = 
{
	Direction(-1, 0), //north
	Direction(1, 0),  //south
	Direction(0, -1), //east
	Direction(0, 1)   //west
};

ls::vector<direction_t> movements =
{
	direction_t::NORTH,
	direction_t::SOUTH,
	direction_t::EAST,
	direction_t::WEST
};

//Functor para a dispersão
struct KeyHash {
    std::size_t operator()( const Position & k_ ) const
    {

    return (std::hash < int >()( k_.roll )  xor
        std::hash < int >()( k_.col )) ;
    }
};

//Functor para a comparação
struct KeyEqual{
    bool operator()( const Position &lhs, const Position &rhs) const{
        return (lhs.roll == rhs.roll and lhs.col == rhs.col);
    }
};

direction_t Player::next_move()
{
	if( not m_solution.empty() ){
		auto dir = m_solution.front();
		m_solution.pop_front();
		return dir;
	}
	return direction_t::NONE;
}


Player::Player()
{
    ls::vector<direction_t> sol;
    m_solution = sol;
  
}

bool Player::find_solution ( std::vector<std::string> & map )
{
	Level lvl;
	lvl.load( map );
	auto start = lvl.get_start_position(); //<! posição inicial da cobra

	//<! Declarar movimento inicial
	Move inicial;
	inicial.pos = start;
	inicial.dir = direction_t::STATIC;

	//<! pilha para a possível sólução
	std::stack< Move > possible_sol;

	//<! vector de soluções
	ls::vector< Move > Solution_;

	//<! tabela hash para posições visitadas
	HashTbl<Position, Move, KeyHash, KeyEqual> pos_visit(23);

	//!< Pilha de decisões tomadas
	std::stack < Position> decisions;

	Move x;
	//<! pilha inicia com a posição inicial
	possible_sol.push( inicial );
	while (  not possible_sol.empty() )
	{
		// desempilha uma possível solução
		x = possible_sol.top();
		possible_sol.pop();

		///<! verifica se é a solução
		if ( lvl.is_solution( x.pos ) )
		{
			Solution_.push_back( x );
			std::cout << "Solução: l-" << x.pos.roll;
			std::cout << " c-" << x.pos.col << std::endl;
			for ( auto i = Solution_.begin(); i != Solution_.end(); ++i )
				m_solution.push_back( (*i).dir );
			return true;
		}
		// verifica se já foi visitada
		else if ( not pos_visit.insert( x.pos, x) )
		{
			/*próximo ciclo*/
			if( x.pos == decisions.top() ){
				decisions.pop();
			} else{
				auto point = Solution_.back();
				while ( point.pos != (decisions.top())) 
				{
					Solution_.pop_back();
					point = Solution_.back();
				}
			}
			
		} else
		{
			Solution_.push_back( x );

			auto cont(0);
			auto i = directions.begin();


			for ( auto dir  = (int) direction_t::NORTH; dir != (int) direction_t::WEST +1; ++dir )
			{
				direction_t index = static_cast<direction_t>(dir);
				Direction d = directions[(int) index];

				Position direc;
				direc.roll = d.height + x.pos.roll;
				direc.col  = d.weight  + x.pos.col;

				Move mv;
				//<! verificar se não é bloqueado
				if ( !lvl.is_blocked( direc ) and not pos_visit.retrieve( direc, mv) )
				{
					
					Move ins;
					ins.pos = direc; //de onde veio
					ins.dir = movements[(int) index]; //direção que tomou
					possible_sol.push( ins ); //adiciona move
					cont++; //conta quantas soluções
				}   	
			}

			//<! verifica se é beco sem saída
			if ( cont == 0 )
			{
				//<! volta até a ultima decisão tomada
				auto point = Solution_.back();
				while ( point.pos != (decisions.top())) 
				{
					Solution_.pop_back();
					point = Solution_.back();
				}
			} 
			else if( cont > 1)
			{
				//!< Marca na pilha de decisoes
				decisions.push( x.pos);
			}
			cont = 0;
		}
	}
	if ( Solution_.empty() ) return false;
	
	return true;
}

void Player::print ()
{
	std::cout << ">>>SOLUTION<<<\n";
	auto cont(0);
	for ( auto i = m_solution.begin(); i != m_solution.end(); ++i)
	{
		if ( *i == direction_t::NORTH ) std::cout << cont << " NORTH\n";
		else if ( *i == direction_t::SOUTH ) std::cout << cont << " SOUTH\n";
		else if ( *i == direction_t::EAST ) std::cout << cont << " EAST\n";
		else if ( *i == direction_t::WEST ) std::cout << cont << " WEST\n";
		else if ( *i == direction_t::STATIC ) std::cout << cont << " Inicio\n";

		cont++;
	}
	std::cout << ">>>FIM DA SOLUÇÂO<<<\n";
}