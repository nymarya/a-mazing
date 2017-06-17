/**
 * @file list.inl
 * @author Gabriel Araújo de Souza
 * @date 02 Jun 2017
 * @brief Arquivo contendo as implementações das classes list
 *        const_iterator e iterator.
 */

// [I] const iterator

//<! Retorna o valor do nó apontado.
template <typename T>
const T
& ls::list<T>::const_iterator::operator* ( ) const
{
	assert( current != nullptr );
	return current->data;
}

//<! Avança o iterador.
template <typename T>
typename ls::list<T>::const_iterator
& ls::list<T>::const_iterator::operator++ ( ) // ++it;
{
	current = current->next;
	return *this;
}

//<! Avança o iterador
template <typename T>
typename ls::list<T>::const_iterator
ls::list<T>::const_iterator::operator++ ( int ) // it++;
{
	const_iterator temp = *this;
	current = current->next;
	return temp;
}

//<! Iterador vai para o nó anterior
template <typename T>
typename ls::list<T>::const_iterator
& ls::list<T>::const_iterator::operator-- ( ) // --it;
{
	current = current->prev;
	return *this;
}

//<! Iterador vai para o nó anterior
template <typename T>
typename ls::list<T>::const_iterator
ls::list<T>::const_iterator::operator-- ( int ) // it--;
{
	const_iterator temp = *this;
	current = current->prev;
	return temp;
}

//<! Compara se dois iteradores são iguais
template <typename T>
bool ls::list<T>::const_iterator::operator==
( const const_iterator & rhs ) const
{
	return current == rhs.current;
}

//<! Compara se dois iteradores são diferentes
template <typename T>
bool ls::list<T>::const_iterator::operator!=
( const const_iterator & rhs ) const
{
	return current != rhs.current;
}

//[II] iterator

//<! Retorna o valor constante apontado pelo iterador
template <typename T>
const T & ls::list<T>::iterator::operator* ( ) const
{
	assert( const_iterator::current != nullptr );
	return const_iterator::current->data;
}

//<! Retorna o valor apontado pelo iterador
template <typename T>
T & ls::list<T>::iterator::operator* ( )
{
	assert( const_iterator::current != nullptr );
	return const_iterator::current->data;
}

//<! Avança o iterador para a próxima posição
template <typename T>
typename ls::list<T>::iterator
& ls::list<T>::iterator::operator++ ( )
{
	const_iterator::current = const_iterator::current->next;
    return *this;
}

//<! Avança o iterador para a próxima posição
template <typename T>
typename ls::list<T>::iterator
ls::list<T>::iterator::operator++ ( int )
{
	iterator temp = *this;
	const_iterator::current = const_iterator::current->next;
    return temp;

}

//<! O iterador vai para a posição anterior
template <typename T>
typename ls::list<T>::iterator
& ls::list<T>::iterator::operator--( )
{
	const_iterator::current = const_iterator::current->prev;
	return *this;
}

//<! O iterador vai para a posição anterior
template <typename T>
typename ls::list<T>::iterator 
ls::list<T>::iterator::operator--( int )
{
	iterator temp = *this;
	const_iterator::current = const_iterator::current->prev;
	return temp;
}

// [III] list

//<! Retorna iterador para o primeiro nó da lista
template <typename T>
typename ls::list<T>::iterator
ls::list<T>::begin( )
{
	return iterator(m_head->next);
}

//<! Retorna iterador constante para o primeiro nó da lista
template <typename T>
typename ls::list<T>::const_iterator
ls::list<T>::cbegin( ) const
{
	return const_iterator(m_head->next);
}

//<! Retorna iterador para a posição logo após o último nó
template <typename T>
typename ls::list<T>::iterator
ls::list<T>::end( )
{
	return iterator(m_tail);
}

//<! Retorna iterador constante para a posição logo após o último nó
template <typename T>
typename ls::list<T>::const_iterator
ls::list<T>::cend( ) const
{
	return const_iterator(m_tail);
}

//<! Retorna o tamanho da lista
template <typename T>
int ls::list<T>::size( ) const
{
	return m_size;
}

//<! Verifica se a lista está vazia
template <typename T>
bool ls::list<T>::empty( ) const
{
	return m_size == 0;
}

//<! Apaga a lista
template <typename T>
void ls::list<T>::clear( )
{
	Node * current = m_head->next;

	while ( current != m_tail )
	{
		Node * temp = current;
		current = current->next;
		delete temp;
	}

	m_size = 0;
	m_head->next = m_tail;
	m_tail->prev = m_head;
}

//<! Retorna o valor do primeiro nó
template <typename T>
T & ls::list<T>::front( )
{
	auto aux = m_head->next;
	return aux->data;
}

//<! Retorna o valor constante do primeiro nó
template <typename T>
const T & ls::list<T>::front( ) const
{
	auto aux = m_head->next;
	return aux->data;
}

//<! Retorna o valor do último nó da lista
template <typename T>
T & ls::list<T>::back( )
{
	auto aux = m_tail->prev;
	return aux->data;
}

//<! Retorna o valor constante do último nó da lista
template <typename T>
const T & ls::list<T>::back( ) const
{
	auto aux = m_tail->prev;
	return aux->data;
}

//<! Insere valor no inicio da lista
template <typename T>
void ls::list<T>::push_front
( const T & value )
{
	insert(begin(), value);
}

//<! Insere valor no final da lista
template <typename T>
void ls::list<T>::push_back
( const T & value )
{
	insert(end(), value);
}

//<! Remove valor do inicio da lista
template <typename T>
void ls::list<T>::pop_front( )
{
	erase(cbegin());
}

//<! Remove valor do final da lista
template <typename T>
void ls::list<T>::pop_back( )
{
	auto it = end();
	erase(--it);
}

//<! Atribui um valor para a lista toda
template <typename T>
void ls::list<T>::assign(const T& value )
{
	auto current = m_head;
	while ( current->next != m_tail )
	{
		current = current->next;
		current->data = value;
	}
}

//<! Atribui valores do intervalo a uma lista
template <typename T>
template <class InItr>
void ls::list<T>::assign( InItr first, InItr last )
{
	auto current = m_head;
	auto fixed = first;

	while ( current->next != m_tail )
	{
		if ( first == last ) first = fixed;
		current = current->next;
		current->data = *first; 

		first++;
	}
}

//<! Atribui valores de uma lista fornecida para a lista
template <typename T>
void ls::list<T>::assign( std::initializer_list<T> ilist )
{
	auto current = m_head;
	auto fixed = ilist.begin();
	auto _nfixed = ilist.begin();

	while ( current->next != m_tail )
	{
		if ( _nfixed == ilist.end() ) _nfixed = fixed;
		current = current->next;
		current->data = *_nfixed;

		_nfixed++;

	}
}

//<! Insere valor uma posição antes do iterador 
template <typename T>
typename ls::list<T>::iterator
ls::list<T>::insert( const_iterator itr, const T & value )
{
	//<! atualiza tamanho
	m_size++;
	//<! cria novo nó com o valor
	auto new_node = new Node(value);
	//<! next do novo nó igual a itr
	new_node->next = itr.current;
	//<! prev do novo nó recebe prev do itr
	new_node->prev = (itr.current)->prev;
	//<! anterior a itr aponta para novo nó
	((itr.current)->prev)->next = new_node;
	//<! itr aponta para novo nó
	(itr.current)->prev = new_node;

	return iterator(new_node);
}

//<! Insere valores de uma lista, uma posição antes da fornecida
template <typename T>
typename ls::list<T>::iterator ls::list<T>::insert
( const_iterator pos, std::initializer_list<T> ilist )
{
	for (auto i = ilist.begin(); i != ilist.end(); ++i )
	{
		insert(pos, *i );
	}

	return iterator(pos.current);
	

}

//<! Apaga um nó
template <typename T>
typename ls::list<T>::iterator
ls::list<T>::erase( const_iterator itr )
{
	if (itr.current != m_tail)
	{
		auto before( (itr.current)->prev ); //anterior ao removido
		auto after( (itr.current)->next ); //posterior ao rmeovido
		
		//Avança para poder excluir o no
		before->next = after;
		after->prev = before;
		m_size--;

		delete itr.current;	
		return iterator( (itr.current)->next);
	}

	return iterator( itr.current );
	
}

//<! Apaga um intervalo da lista
template <typename T>
typename ls::list<T>::iterator
ls::list<T>::erase( iterator first, iterator last )
{

	if ( empty() ) return ( first.current);
	while ( first != last )
	{
		first++;
		erase( first.current->prev);
	}

	return last;
}

//<! Procura elementos na lista
template <typename T>
typename ls::list<T>::const_iterator 
ls::list<T>::find( const T & value ) const
{
	auto curr = m_head;
	while ( curr->next != m_tail )
	{
		curr = curr->next;
		if( curr->data == value )
			return const_iterator( curr );
	}

	return const_iterator( m_tail );
}



