/*! \sllist.h
 * Brief description: Class to handle linked list.
 *
*/
#include <iterator>

template <typename T>
class list
{
	private:
	    struct node
	    {
			node(T val)
				: next(NULL), value(val)
			{}

			node* next;
			T     value;
	    };

	    node* _head;
	    node* _tail;
	    int _size;

  	public:
		class const_iterator
		  : public std::iterator<std::forward_iterator_tag, T, size_t, T const*, T const&>
		{
			public:
				typedef std::forward_iterator_tag iterator_category;
				typedef T         value_type;
				//typedef ptrdiff_t difference_type;
				typedef T const*  pointer;
				typedef T const&  reference;

				const_iterator(node* cur_node = NULL)
					: _curpos(cur_node)
				{}

				reference operator*()
				{
					return _curpos->value;
				}

				pointer operator ->()
				{
				  return &(**this);
				}

				// The lack of arguments indicates that this is prefix ++
				const_iterator& operator++()
				{
				  _curpos = _curpos->next;
				  return *this;
				}

				// The dummy argument indicates that this is the postfix ++
				const_iterator operator++(int)
				{
				  const_iterator old_it = *this;
				  ++(*this);
				  return old_it;
				}

				bool operator ==(const_iterator const& rhs)
				{
				  return _curpos == rhs._curpos;
				}

				bool operator !=(const_iterator const& rhs)
				{
				  return !(*this == rhs);
				}
			      protected:
			        node* _curpos;
	    };

	    class iterator
	      : public const_iterator
	    {
			public:
			iterator(node* iter_node = NULL)
				: const_iterator(iter_node)
			{}

			typedef std::forward_iterator_tag iterator_category;
			typedef T      value_type;
			typedef size_t difference_type;
			typedef T*     pointer;
			typedef T&     reference;

			using const_iterator::_curpos;

			reference operator*()
			{
			  return _curpos->value;
			}

			pointer operator ->()
			{
			  return &(**this);
			}

			iterator& operator++()
			{
			  _curpos = _curpos->next;
			  return *this;
			}

			iterator operator++(int)
			{
			  iterator old_it = *this;
			  ++(*this);
			  return old_it;
			}
	    };

	    /*!
	     * Functions definition
		*/
	    list(); // constructor
	    list(list<T> const& rhs); // constructor overload
	    ~list(); // destructor
	    iterator begin(); // return head
	    iterator end(); // return tail
	    const_iterator begin() const; // return head (const)
	    const_iterator end() const; // return tail (const)
	    void push_front(T const& elt); // insertion in the beginning
	    void push_back(T const& elt); // insertion in the ending
	    void insert_after(iterator where, T const& elt); // insertion after node
	    iterator erase_after(iterator it); // deletion after node
	    void clear(); // clear list
	    void pop_front(); // remove front
	    void print_list(list<T> const& rhs); // print list
	    void get_list(list<T> const& rhs); // get list
	    list& operator =(list<T> const& rhs); // handle = operator

	    size_t size() const; // list size
	    bool empty() const; // is list empty?
	    friend class list<T>::iterator;
};

#include "sllist.hpp"
