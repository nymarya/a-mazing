#include "player.h"
#include <functional> //<! std::hash


std::vector<Direction> directions = 
{
	Direction(-1, 0), //north
	Direction(1, 0),  //south
	Direction(0, -1), //east
	Direction(0, 1)   //west
};

std::vector<direction_t> movements =
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
		m_solution.erase(m_solution.begin());
		return dir;
	}
	return direction_t::NONE;
}


Player::Player()
{
    std::vector<direction_t> sol;
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
	inicial.dir.push_back(direction_t::STATIC);

	//<! pilha para a possível sólução
	std::stack< Move > possible_sol;

	//<! tabela hash para posições visitadas
	HashTbl<Position, Move, KeyHash, KeyEqual> pos_visit(23);

	//!< Pilha de decisões tomadas
	// std::stack < Position> decisions;

	Move x;
	//<! pilha inicia com a posição inicial
	possible_sol.push( inicial );

	//<! possível solução na tabela hash
	pos_visit.insert( inicial.pos, inicial);	

	while (  not possible_sol.empty() )
	{	
		// desempilha uma possível solução
		x = possible_sol.top();
		std::cout << "Possível solução\n";
		std::cout << "l: " << x.pos.roll << " c: " << x.pos.col << std::endl;
		possible_sol.pop();
		std::cout << "SOLUTION: [ ";
		auto cont(0);
		for ( auto i = x.dir.begin(); i != x.dir.end(); ++i)
		{
			if ( *i == direction_t::NORTH ) std::cout << "N ";
			else if ( *i == direction_t::SOUTH ) std::cout << "S ";
			else if ( *i == direction_t::EAST ) std::cout << "E ";
			else if ( *i == direction_t::WEST ) std::cout << "W ";
			else if ( *i == direction_t::STATIC ) std::cout << "I ";

			cont++;
		}
	std::cout << " ]\n";

		///<! verifica se é a solução
		if ( lvl.is_solution( x.pos ) )
		{
			std::cout << "Solução: l-" << x.pos.roll;
			std::cout << " c-" << x.pos.col << std::endl;
			
			// for ( auto i((x.dir).begin()); i != (x.dir).end(); ++i)
			// 	m_solution = (*i);	
			m_solution = x.dir;		

			return true;
		}
		//<! verifica se já foi visitada e já insere uma possível solução
		else if ( (not pos_visit.insert( x.pos, x)) and (x.pos != inicial.pos))
		{
			/*próximo ciclo*/
			
		} else
		{
			auto cont(0);
			
			for ( auto d  = (int) direction_t::NORTH; d != (int) direction_t::WEST +1; ++d )
			{
				//direction_t index = static_cast<direction_t>(dir);
				Direction de = directions[ d ];

				Position direc;
				direc.roll = de.height + x.pos.roll;
				direc.col  = de.weight  + x.pos.col;
				std::cout << "teste: " << direc.roll << " " << direc.col << std::endl;

				Move mv;
				//<! verificar se não é bloqueado
				if ( !lvl.is_blocked( direc ) and not pos_visit.retrieve( direc, mv) )
				{

					std::cout << "achou possível solução\n";
					std::cout << ">>>OLHA QUEM É D: " << d << std::endl;
					Move ins;
					ins.pos = direc; //de onde veio
					ins.dir = x.dir;
					std::cout << "X.dir: " << x.dir.size() << " ins " << ins.dir.size() << std::endl;
					ins.dir.push_back(movements[ d ]); //direção que tomou
					possible_sol.push( ins ); //adiciona move
					cont++; //conta quantas soluções
					auto test = possible_sol.top().dir;
					std::cout << "ins [ ";
					auto cont(0);
					for ( auto i = ins.dir.begin(); i != ins.dir.end(); ++i)
					{
						if ( *i == direction_t::NORTH ) std::cout << cont << " NORTH,";
						else if ( *i == direction_t::SOUTH ) std::cout << cont << " SOUTH,";
						else if ( *i == direction_t::EAST ) std::cout << cont << " EAST,";
						else if ( *i == direction_t::WEST ) std::cout << cont << " WEST,";
						else if ( *i == direction_t::STATIC ) std::cout << cont << " Inicio,";
						else std::cout << (int) *i << " ," ;

						cont++;
					}
					std::cout << " ]	\n";
					std::cout << "possible_sol [ ";
					auto cont2(0);
					for ( auto i = test.begin(); i != test.end(); ++i)
					{
						if ( *i == direction_t::NORTH ) std::cout << cont2 << " NORTH,";
						else if ( *i == direction_t::SOUTH ) std::cout << cont2 << " SOUTH,";
						else if ( *i == direction_t::EAST ) std::cout << cont2 << " EAST,";
						else if ( *i == direction_t::WEST ) std::cout << cont2 << " WEST,";
						else if ( *i == direction_t::STATIC ) std::cout << cont2 << " Inicio,";
						else std::cout << (int) *i << " ," ;

						cont2++;
					}
					std::cout << " ]	\n";
					std::cout << "x [ ";
					auto cont1(0);
					for ( auto i = x.dir.begin(); i != x.dir.end(); ++i)
					{
						if ( *i == direction_t::NORTH ) std::cout << cont1 << " NORTH,";
						else if ( *i == direction_t::SOUTH ) std::cout << cont1 << " SOUTH,";
						else if ( *i == direction_t::EAST ) std::cout << cont1 << " EAST,";
						else if ( *i == direction_t::WEST ) std::cout << cont1 << " WEST,";
						else if ( *i == direction_t::STATIC ) std::cout << cont1 << " Inicio,";
						else std::cout << (int) *i << " ," ;

						cont1++;
					}
					std::cout << " ]	";
															
					if ( movements[ d ] == direction_t::NORTH ) std::cout << "N \n";
					else if ( movements[ d ] == direction_t::SOUTH ) std::cout << "S \n";
					else if ( movements[ d ]== direction_t::EAST ) std::cout << "E \n";
					else if ( movements[ d ] == direction_t::WEST ) std::cout << "W \n";
					else if ( movements[ d ] == direction_t::STATIC ) std::cout << "I \n";
				}   	
			}

			//<! verifica se é beco sem saída
			// if ( cont == 0 )
			// {
			// 	//<! volta até a ultima decisão tomada
			// 	auto point = Solution_.back();
			// 	while ( point.pos != (decisions.top())) 
			// 	{
			// 		Solution_.pop_back();
			// 		point = Solution_.back();
			// 	}
			// } 
			// else if( cont > 1)
			// {
			// 	//!< Marca na pilha de decisoes
			// 	decisions.push( x.pos);
			// }
			cont = 0;
		}
	}
	return false;
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