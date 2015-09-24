/*! \sllist.cpp
 * Brief description: Implements list class functions.
 *
*/

 /********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline typename list<T>::iterator list<T>::begin()
{
    return iterator(_head);
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline typename list<T>::iterator list<T>::end()
{
    return iterator(NULL);
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline typename list<T>::const_iterator list<T>::begin() const
{
    return const_iterator(_head);
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline typename list<T>::const_iterator list<T>::end() const
{
    return const_iterator(NULL);
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline void list<T>::insert_after(typename list<T>::iterator where, T const& elt)
{
    node* newnode = new node(elt);
    newnode->next = where._curpos->next;
    where._curpos->next = newnode;
    _size++;
    if (newnode->next == NULL)
    {
        _tail = newnode;
    }
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline void list<T>::push_front(T const& elt)
{
    node* newnode = new node(elt);
    newnode->next = _head;
    _head = newnode;
    if (_tail == NULL)
    {
        _tail = newnode;
    }
    _size++;
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline void list<T>::push_back(T const& elt)
{
    if (_tail != NULL)
        insert_after(iterator(_tail), elt);
    else
        push_front(elt);
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline typename list<T>::iterator list<T>::erase_after(typename list<T>::iterator it)
{
    node* todelete = it._curpos->next;
    it._curpos->next = it._curpos->next->next;
    _size--;

    if (it._curpos->next == NULL)
    {
        _tail = it._curpos;
    }
    delete todelete;
    return iterator(it._curpos->next);
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline void list<T>::pop_front()
{
    node* todelete = _head;
    _head = _head->next;
    if (_head == NULL) {
        _tail = NULL;
    }
    _size--;
    delete todelete;
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline void list<T>::clear()
{
    while (begin() != end())
    {
        pop_front();
    }
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
list<T>& list<T>::operator=(list<T> const& rhs)
{
    clear();

    const_iterator rhs_it = rhs.begin();
    for (rhs_it = rhs.begin(); rhs_it != rhs.end(); ++rhs_it)
    {
        push_back(*rhs_it);
    }

    return *this;
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline size_t list<T>::size() const
{
  return _size;
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline bool list<T>::empty() const
{
  return _size == 0;
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline list<T>::list()
  : _head(NULL), _tail(NULL), _size(0)
{}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline list<T>::list(list<T> const& rhs)
  : _head(NULL), _tail(NULL), _size(0)
{
    *this = rhs;
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
inline list<T>::~list()
{
    clear();
}

/********************************************//**
 *  ... text
 ***********************************************/
template <typename T>
void print_list(list<T> const& rhs)
{
  typename list<T>::const_iterator it;
  for (it = rhs.begin(); it != rhs.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
}
