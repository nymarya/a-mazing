/**
 * @file list.h
 * @author Gabriel Araújo de Souza
 * @date 02 Jun 2017
 * @brief Arquivo contendo as definições das classes list
 *        iterator e const_iterator.
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  //<! cout, endl
#include <iterator>  //<! begin(), end()
#include <cassert>   //<! assert()
#include <algorithm> //<! copy

/**
 * Namespace para as classes definidas
 */
namespace ls {

	/**
	 * @brief      Classe list.
	 *
	 * @tparam     T     Tipo de variável genérica.
	 */
	template <typename T>
	class list {

	private:

		/**
		 * @brief      Definição de um nó para um lista duplamente
		 *             encadeada.
		 */
		struct Node {
		
			T data; 	//<! Campo dados.
			Node *prev; //<! Ponteiro para o nó anterior ao atual.
			Node *next; //<! Ponteiro para o próximo nó da lista.
			
			//<! Construtor básico
			Node( const T & d = T( ), Node * p = nullptr, Node * n = nullptr )
				: data( d ), prev(p), next( n ) { /* Empty */ }
		};

	private:

		int m_size;   //<! Quantidade de nós da lista.
		Node *m_head; //<! Nó para o início da lista.
		Node *m_tail; //<! Nó para o final da lista.

	public:

		class const_iterator; //<! classe do iterador constante
		class iterator; //<! classe do iterador

		/**
		 * @brief      Construtor simples de uma lista.
		 *
		 * @param[in]  sz    O tamanho da lista.
		 */
		list( size_t sz = 0 )
			: m_size( sz )
			, m_head( new Node() )
			, m_tail( new Node() )
		{ 
			m_head->next = m_tail;
			m_tail->prev = m_head;
		}

		/**
		 * @brief      Construtor de um lista cópia de valores
		 *             em um intervalo fechado-aberto.
		 *
		 * @param[in]  first    Inicio do instervalo (fechado).
		 * @param[in]  last     Fim do intervalo (aberto).
		 *
		 * @tparam     Tipo do intervalo.
		 */
		template< typename InputIt >
		list( InputIt first, InputIt last )
		{
			//<! cria lista
			m_size = 0;
			m_head = new Node;
			m_tail = new Node;
			m_head->next = m_tail;
			m_tail->prev = m_head;

			//<! copia conteúdo
			for ( /*empty*/; first != last; ++first )
				push_back(*first);

		}

		/**
		 * @brief      Construtor cópia.
		 *
		 * @param[in]  other  A lista para copiar.
		 */
		list( const list & other)
		{
			//<! cria lista
			m_size = 0;
			m_head = new Node;
			m_tail = new Node;
			m_head->next = m_tail;
			m_tail->prev = m_head;

			//<! copia conteúdo
			for( auto i(other.cbegin()); i != other.cend(); ++i)
	 	    	push_back(*i);
		}

		/**
		 * @brief      Construtor cópia de uma lista.
		 *
		 * @param[in]  ilist  A lista para copiar o conteúdo.
		 */
		list( std::initializer_list<T> ilist )
		{
			//<! cria lista
			m_size = 0;
			m_head = new Node;
			m_tail = new Node;
			m_head->next = m_tail;
			m_tail->prev = m_head;

			//<! copia conteúdo
			for ( auto i = ilist.begin(); i != ilist.end(); ++i )
				push_back(*i);

		}

		/**
		 * @brief      Construtor cópia com lógica de movimento.
		 *
		 * @param[in]  <unnamed>  Lista referência.
		 */
		list( list && other)
		{
			// "movimentar" dados de other
			m_size = other.m_size;
			m_head = new Node;
		    m_tail = other.m_tail;
		    m_head->next = other.m_head->next;
		    
		    // mudar other
		    other.m_tail = new Node;
		    other.m_head->next = other.m_tail;
		    other.m_tail->prev = other.m_head;
		    other.m_size = 0;
		}

		/**
		 * @brief      Destroi o objeto.
		 */
		~list( )
		{
			clear(); //Apaga os outros nós da lista
	        delete m_head;
	        delete m_tail;
		}		
		
		/**
		 * @brief      Sobrecarga do operador '=' para copiar dados
		 *             de uma lista para outra.
		 *
		 * @param[in]  copy  A cópia.
		 *
		 * @return     A lista com os novos valores copiados.
		 */
		list & operator= ( const list & copy )
		{	
			//<! cria nova lista 
			m_size = 0;
			m_head = new Node;
			m_tail = new Node;
			m_head->next = m_tail;
			m_tail->prev = m_head;

			//<! copia o conteúdo
			for ( auto i = copy.cbegin(); i != copy.cend(); ++i )
				push_back(*i);

			return *this;
		}
		
		/**
		 * @brief      Sobrecarga do operador '=' para copiar dados
		 *             de uma lista fornecida.
		 *
		 * @param[in]  ilist  A lista.
		 *
		 * @return     A lista com os novos valores atribuidos.
		 */
		list& operator=( std::initializer_list<T> ilist )
		{
			//<! cria nova lista
			m_size = 0;
			m_head = new Node;
			m_tail = new Node;
			m_head->next = m_tail;
			m_tail->prev = m_head;

			//<! copia conteúdo
			for ( auto i = ilist.begin(); i < ilist.end(); ++i)
				push_back(*i);

			return *this;
		}
		
		/**
		 * @brief      Localiza o primeiro item da lista.
		 *
		 * @return     Retorna um iterador para o primeiro item da lista.
		 */
		iterator begin( );

		/**
		 * @brief      Localiza o primeiro item da lista.
		 *
		 * @return     Retorna um iterador constante para o primeiro item da lista.
		 */
		const_iterator cbegin( ) const;

		/**
		 * @brief      Localiza o nó após o último item válido da lista.
		 *
		 * @return     Retorna um iterador para a posição logo após o último 
		 *             item válido da lista.
		 */
		iterator end( );

		/**
		 * @brief      Localiza o nó após o último item válido da lista.
		 *
		 * @return     Retorna um iterador constante para a posição logo após.
		 *             o último item válido da lista.
		 */
		const_iterator cend( ) const;

		/**
		 * @brief      Informa o atual tamanho da lista.
		 *
		 * @return     Um inteiro com a quantidade de elementos da lista.
		 */
		int size( ) const;
		
		/**
		 * @brief      Verifica se a lista está vazia.
		 *
		 * @return     True caso a lista esteja vazia, False caso contrário.
		 */
		bool empty( ) const;
		
		/**
		 * @brief      Limpa os dados da lista.
		 */
		void clear( );
		
		/**
		 * @brief      Verifica o valor armazenado no primeiro nó da lista.
		 *
		 * @return     O valor no primeiro nó da lista.
		 */
		T & front( );
		
		/**
		 * @brief      Verifica o valor armazenado no primeiro nó da lista.
		 *
		 * @return     O valor constante do primeiro nó da lista.
		 */
		const T & front( ) const;
		
		/**
		 * @brief      Verifica o valor armazenado no último nó da lista.
		 *
		 * @return     O valor no último nó da lista.
		 */
		T & back( );
		
		/**
		 * @brief      Verifica o valor armazenado no último nó da lista.
		 *
		 * @return     O valor constante do último nó da lista.
		 */
		const T & back( ) const;
		
		/**
		 * @brief      Insere um valor no inicio da lista.
		 *
		 * @param[in]  value  O valor.
		 */
		void push_front( const T & value );
		
		/**
		 * @brief      Insere um valor ńo final da lista.
		 *
		 * @param[in]  value  O valor.
		 */
		void push_back( const T & value );
		
		/**
		 * @brief      Remove o primeiro nó da lista.
		 */
		void pop_front( );
		
		/**
		 * @brief      Remove o último nó da lista.
		 */
		void pop_back( );

		/**
		 * @brief      Atribui um valor para todos os nós da lista.
		 *
		 * @param[in]  value  O valor.
		 */
		void assign(const T& value );

		/**
		 * @brief      Atribui valores de um intervalo fechado-aberto
		 *             para todos os nós da lista ( em ordem ).
		 *
		 * @param[in]  first  Início do intervalo.
		 * @param[in]  last   Fim do intervalo.
		 *
		 * @tparam     InItr  Tipo do intervalo.
		 */
		template < class InItr >
		void assign( InItr first, InItr last );
		
		/**
		 * @brief      Atribui valores de uma lista fornecida para 
		 *             todos os nós da lista ( em ordem ).
		 *
		 * @param[in]  ilist  A lista.
		 */
		void assign( std::initializer_list<T> ilist );
		
		/**
		 * @brief      Insere um valor na posição anterior de um iterador
		 *             fornecido.
		 *
		 * @param[in]  itr    O iterador.
		 * @param[in]  value  O valor.
		 *
		 * @return     O iterador para a posição do valor inserido.
		 */
		iterator insert( const_iterator itr, const T & value );
		
		/**
		 * @brief      Insere os valores de uma lista fornecida, na posição
		 *             anterior do iterador fornecido.
		 *
		 * @param[in]  pos    A posição.
		 * @param[in]  ilist  A lista.
		 *
		 * @return     Um iterador para o último elemento inserido.
		 */
		iterator insert( const_iterator pos, std::initializer_list<T> ilist );
		
		/**
		 * @brief      Apaga o nó do iterador fornecido.
		 *
		 * @param[in]  itr   O iterador.
		 *
		 * @return     Um iterador para o nó após o removido.
		 */
		iterator erase( const_iterator itr );
		
		/**
		 * @brief      Remove um intervalo fechado-aberto da lista.
		 *
		 * @param[in]  first  O início do intervalo.
		 * @param[in]  last   O fim do intervalo.
		 *
		 * @return     iterador para o nó após o último removido.
		 */
		iterator erase( iterator first, iterator last );
		
		/**
		 * @brief      Procura por um valor na lista.
		 *
		 * @param[in]  value  O valor.
		 *
		 * @return     Um iterador constante para o primeiro nó encontrado
		 *             com o valor.
		 */
		const_iterator find( const T & value ) const;

	};

	/**
	 * @brief      Classe const_iterator para a classe list.
	 *
	 * @tparam     T     Tipo dos dados.
	 */
	template <typename T>
	class list<T>::const_iterator {

		protected:
			Node *current;
		 	const_iterator( Node * p ) : current( p ) {}
		 	friend class list<T>;

		public:
			/**
			 * @brief      Construtor básico.
			 */
		 	const_iterator( ){ /*empty*/ }

		 	/**
		 	 * @brief      Operador '*'.
		 	 *
		 	 * @return     O valor do nó apontado apontado pelo iterador.
		 	 */
		 	const T & operator* ( ) const;

		 	/**
		 	 * @brief      Operador '++', equivalente à ++it. 
		 	 *
		 	 * @return     Iterador para o próximo nó.
		 	 */
		 	const_iterator & operator++ ( );
		 	
		 	/**
		 	 * @brief      Operador '++', equivalente à it++. 
		 	 *
		 	 * @return     Iterador para o próximo nó.
		 	 */
		 	const_iterator operator++ ( int );

		 	/**
		 	 * @brief      Operador '--', equivalente à --it. 
		 	 *
		 	 * @return     Iterador para a posição anterior.
		 	 */
		 	const_iterator & operator-- ( );

		 	/**
		 	 * @brief      Operador '--', equivalente à it--. 
		 	 *
		 	 * @return     Iterador para a posição anterior.
		 	 */
		 	const_iterator operator-- ( int );

		 	/**
		 	 * @brief      Verifica se dois iteradores são iguais.
		 	 *
		 	 * @param[in]  rhs  Iterador para se comparar.
		 	 *
		 	 * @return     True se iguais, False caso constrário.
		 	 */
		 	bool operator== ( const const_iterator & rhs ) const;

		 	/**
		 	 * @brief      Verifica se dois iteradores são diferentes.
		 	 *
		 	 * @param[in]  rhs  Iterador para se comparar.
		 	 *
		 	 * @return     True se iguais, False caso constrário.
		 	 */
		 	bool operator!= ( const const_iterator & rhs ) const;
		
	};

	/**
	 * @brief      Classe iterator para o list.
	 *
	 * @tparam     T     Tipo do iterador.
	 */
	template <typename T>
	class list<T>::iterator : public list<T>::const_iterator {

		protected:
			iterator( Node *p ) : const_iterator( p ){}
			friend class list<T>;

		public:

			/**
			 * @brief      Construtor básico.
			 */
			iterator( ) : const_iterator() { /* Empty */ }
			
			/**
			 * @brief      Operador '*'.
			 *
			 * @return     O valor constante armazenado no nó apontado
			 */
			const T & operator* ( ) const;

			/**
			 * @brief      Operador '*'.
			 *
			 * @return     O valor armazenado no nó apontado.
			 */
			T & operator* ( );

			/**
			 * @brief      Operador '++', equivalente a ++it.
			 *
			 * @return     O iterado para o próximo nó.
			 */
			iterator & operator++ ( );

			/**
			 * @brief      Operador '++', equivalente a it++.
			 *
			 * @return     O iterado para o próximo nó.
			 */
			iterator operator++ ( int );

			/**
			 * @brief      Operador '--', equivalente a --it.
			 *
			 * @return     O iterado para o nó anterior.
			 */
			iterator & operator--( );

			/**
			 * @brief      Operador '--', equivalente a it--.
			 *
			 * @return     O iterado para o nó anterior.
			 */
			iterator operator--( int );

	};

	/**
	 * impletação do template.
	 */
	#include "list.inl"
}

#endif