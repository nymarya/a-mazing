/**
 * @file driver_list.cpp
 * @author Gabriel Araújo de Souza
 * @date 02 Jun 2017
 * @brief Arquivo para testes dos métodos das classes list
 *        const_iterator e iterator
 */

#include <iostream>
#include <vector>
#include <string>

#include "list.h"

template <typename T>
void print( ls::list<T> & v )
{
	ls::list<int>::const_iterator b_it = v.begin();
	ls::list<int>::const_iterator e_it = v.end();

	std::cout << "[ ";
	for ( /*empty*/; b_it != e_it; ++b_it )
		std::cout << *b_it << " ";
	std::cout << "]\n";
}

int main ()
{
	// construtores
	{
		ls::list<int> a;
		ls::list<int> b(10);

		assert ( a.size() == 0 );
		assert ( b.size() == 10 );

		std::vector<int> values { 1, 2, 3, 4, 5, 6 };
		ls::list<int> c( values.begin(), values.end() );
		ls::list<int>::const_iterator b_it = c.begin();
		ls::list<int>::const_iterator e_it = c.end();

		for ( auto i = values.begin(); b_it != e_it; ++b_it, ++i )
			assert( *b_it == *i );

		ls::list<int> d(c);
		ls::list<int>::const_iterator b_it2 = d.begin();
		ls::list<int>::const_iterator e_it2 = d.end();

		for ( auto i(1) ; b_it2 != e_it2; ++b_it2, ++i)
			assert( *b_it2 == i);

		ls::list<int> e { 1, 2, 3, 4, 5, 6 };
		ls::list<int>::const_iterator b_it3 = e.begin();
		ls::list<int>::const_iterator e_it3 = e.end();

		for ( auto i(1) ; b_it3 != e_it3; ++b_it3, ++i)
			assert( *b_it3 == i);

		a = d;
		ls::list<int>::const_iterator b_it4 = a.begin();
		ls::list<int>::const_iterator e_it4 = a.end();

		for ( auto i(1) ; b_it4 != e_it4; ++b_it4, ++i)
			assert( *b_it4 == i);

		d = {6, 7, 8, 9, 10 };
		ls::list<int>::const_iterator b_it5 = d.begin();
		ls::list<int>::const_iterator e_it5 = d.end();
		for ( auto i(6) ; b_it5 != e_it5; ++b_it5, ++i)
			assert( *b_it5 == i);

	}

	// membros
	{
		ls::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		ls::list<int> empt;

		//<! size
		assert( a.size() == 10 );
		assert( empt.size() == 0 );

		//<! empty
		assert( a.empty() == false );
		assert( empt.empty() == true );

		//<! clear
		ls::list<std::string> haha = { "aa", "bb", "cc" };
		assert( haha.size() == 3 );
		haha.clear();
		assert( haha.size() == 0 );

		//<! front
		assert( a.front() == 1 );

		//<! back
		assert( a.back() == 10 );

		//<! push_front
		a.push_front(111);
		assert( a.front() == 111 );

		//<! push_back
		a.push_back(222);
		assert( a.back() == 222 );

		//<! pop_front
		a.pop_front();
		assert( a.front() == 1 );

		//<! pop_back
		a.pop_back();
		assert( a.back() == 10 );

	}

	//assigns
	{
		ls::list<int> a {1, 2, 3, 4, 5, 6, 7 };
		a.assign(6);
		auto itb = a.begin();
		auto ite = a.end();

		for (/*empty*/; itb != ite; ++itb )
			assert( *itb == 6 );

		std::cout << ">> TESTE ASSIGNs\n";
		std::vector<int> val {8, 9, 10};
		a.assign( val.begin(), val.end() );
		print(a);

		std::initializer_list<int> ilist { 5, 6, 7, 8, 9, 10, 11, 12 };
		a.assign(ilist);
		print(a);
		std::cout << ">> FIM (ASSIGNs)\n\n";
	}

	//iterators
	{
		ls::list<int> a {1, 2, 3, 4, 5, 6, 7 };
		//<! inserir valor no meio
		std::cout << ">> TESTE INSERT\n";
		std::cout << ">> Antes: - Size: " << a.size() << " ";
		print(a);
		auto it = a.begin();
		for ( auto i(0); i < 3; ++i ) it++;
		a.insert( it, 222 );
		std::cout << ">> Depois: - Size: " << a.size() << " ";
		print(a);

		std::cout << std::endl;

		//<! inserir lista no meio
		std::cout << ">> Antes: - Size: " << a.size() << " ";
		print(a);
		std::initializer_list<int> ilist { 9, 10, 11, 12 };
		a.insert( it, ilist );
		std::cout << ">> Depois: - Size: " << a.size() << " ";
		print(a);

		std::cout << std::endl;

		//<! inserir lista no inicio
		it = a.begin();
		std::cout << ">> Antes: - Size: " << a.size() << " ";
		print(a);
		a.insert( it, ilist );
		std::cout << ">> Depois: - Size: " << a.size() << " ";
		print(a);

		std::cout << std::endl;

		//<! inserir lista no fim
		it = a.end();
		std::cout << ">> Antes: - Size: " << a.size() << " ";
		print(a);
		a.insert( it, ilist );
		std::cout << ">> Depois: - Size: " << a.size() << " ";
		print(a);

		std::cout << ">> FIM (INSERT)\n\n";

	}

	//erase
	{
		std::cout << ">> TESTE ERASE\n";
		
		//eraase no meio
		ls::list<int> aa {1, 2, 3, 4, 5, 6, 7 };
		auto tt = aa.begin();
		for (auto i(0); i < 4; ++i ) ++tt;
		std::cout << ">> Antes: - Size: " << aa.size() << " ";
		print(aa);
		aa.erase( tt );
		std::cout << ">> Depois: - Size: " << aa.size() << " ";
		print(aa);

		//<! remover do inicio
		ls::list<int> a {1, 2, 3, 4, 5, 6, 7 };
		ls::list<int>::iterator it1 = a.begin();
		auto t = a.begin();
		for ( auto i(0); i < 3; ++i ) ++t;
		ls::list<int>::iterator it2 = t;

		std::cout << ">> Antes: - Size: " << a.size() << " ";
		print(a);
		a.erase( it1, it2);
		std::cout << ">> Depois: - Size: " << a.size() << " ";
		print(a);

		// remover do meio
		ls::list<int> b {1, 2, 3, 4, 5, 6, 7 };
		auto it3 = b.begin();
		auto it4 = b.begin();
		for ( auto i(0); i < 2; ++i ) ++it3;
		for ( auto i(0); i < 4; ++i ) ++it4;
		std::cout << ">> Antes: - Size: " << b.size() << " ";
		print(b);
		b.erase( it3, it4);
		std::cout << ">> Depois: - Size: " << b.size() << " ";
		print(b);

		//remover do final
		ls::list<int> c {1, 2, 3, 4, 5, 6, 7 };
		auto it5 = c.begin();
		auto it6 = c.end();
		for ( auto i(0); i < 4; ++i ) ++it5;
				std::cout << ">> Antes: - Size: " << c.size() << " ";
		print(c);
		c.erase( it5, it6 );
		std::cout << ">> Depois: - Size: " << c.size() << " ";
		print(c);
	
		std::cout << ">> FIM (ERASE)\n\n";
	}

	//find
	{
		ls::list<int> a {1, 2, 3, 4, 5, 6, 7 };
		//procurando no inicio
		assert(a.find( 1 ) == a.begin() );
		//procurando no meio
		auto t = a.begin();
		for (auto i(0); i < 3; ++i ) ++t;
		assert(a.find( 4 ) == t );
		//procurando no final
		assert(*(a.find( 7 )) == 7 );
		//procurando elemento que não existe		
		assert(a.find( 12 ) == (a.end())++ );
	}
	
	std::cout << ">>> PASSOU EM TODOS OS TESTES\n";
	return 0;
}