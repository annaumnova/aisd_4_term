#pragma once
#include <stdio.h>
#include <iostream>
#include <stdexcept>

template<typename VALUE>
class List {

	private:
		class Node//L-1 list
		{
		public:
			VALUE inf{}; //the information part of the beginning element
			Node* next{}; //the pointer to the next element
			
		};
		size_t size;//size of list
		Node* head;//the pointer of the beginning
		Node* end;//the pointer of the end

		Node* getNode(size_t index)//getting pointer to the List's Node with index
		{
			if (index <= get_size() && index >= 0)
			{
				Node* node = head;
				for (int i = 0; i < (int)index; i++)
					node = node->next;
				return node;
				node = NULL;
			}
		}

	public:
		
		void push_back(VALUE node)//add to the end
		{
			Node* temp = new Node(node);
			if (isEmpty())//empty list??
			{
				head = temp;
				end = temp;
			}
			else
			{
				end->next = temp;
				end = temp;
			}
			size++;//after adding the size increases
		}

		void push_front(VALUE node)//add to the beginning
		{
			Node* temp = new Node(node);
			if (isEmpty())//empty??
				push_back(node);
			else
			{
				temp->next = head;
				head = temp;
			}
			size++;
		}

		void pop_back()//detele the last element
		{
			if (!isEmpty())
			{
				if (head->next == NULL)//only 1 element
				{
					Node* temp = head;
					delete temp;
					head = NULL;
					size--;
				}
				else//more than one element
				{
					Node* first_elem = head;
					Node* next_elem = head->next;
					while (next_elem->next != NULL)//not equavelent "end"
					{
						next_elem = next_elem->next;
						first_elem = first_elem->next;
					}
					first_elem->next = NULL;//the end
					delete next_elem;//the delete element
					size--;
				}
			}
			else throw std::invalid_argument("out_of_range");//unexpected
		}

		void pop_front()//delete the first element
		{
			if (!isEmpty())
			{
				if (head->next == NULL)//only 1 element
				{
					Node* temp = head;
					delete temp;
					head = NULL;
					size--;
				}
				else//more than one element
				{
					Node* first_elem = head;
					head = head->next;
					delete first_elem;//the delete element
					size--;
				}
			}
			else throw std::invalid_argument("out_of_range");//unexpected
		}

		void insert(VALUE node_with_index, size_t index_position)//add with index (before the available element's index)
		{
			if (index_position >= 0 && index_position < get_size())
			{
				if (index_position == 0)//beginning?
					push_front(node_with_index);
				else if (index_position == get_size())//end?
					push_back(node_with_index);
				else//middle?
				{
					Node* tmp_next_elem = getNode(index_position);
					Node* temp_curr = new Node(tmp_next_elem->inf, tmp_next_elem->next);
					tmp_next_elem->inf = node_with_index;
					tmp_next_elem->next = temp_curr;
					if (end == tmp_next_elem)//seems end
						end = temp_curr;
					size++;
				}
			}
			else throw std::invalid_argument("out_of_range");//unexpected
		}

		int at(size_t index_position)//get the element with index
		{
			if (index_position >= 0 && index_position < get_size())
			{
				return getNode(index_position)->inf;
			}
			else throw std::invalid_argument("out_of_range");//unexpected
		}

		void remove(size_t index_position)//delete the element with index
		{
			if (index_position >= 0 && index_position < get_size())
			{
				if (index_position == 0)//beggin
					pop_front();
				else if (index_position == get_size() - 1)//end
					pop_back();
				else//middle 
				{
					Node* previous_the_del_tmp = getNode(index_position - 1);//before the needed element
					Node* the_del_tmp = previous_the_del_tmp->next;
					previous_the_del_tmp->next = the_del_tmp->next;
					delete the_del_tmp;
					size--;
				}
			}
			else throw std::invalid_argument("out_of_range");//unexpected
		}

		size_t get_size() const {
			if (size >= 0)
				return size;
			else throw std::logic_error("Index is out of range");//unexcepted
		}

		void clear()//delete all elements
		{
			Node* current = head;
			while (head)
			{
				current = head;
				head = head->next;
				delete current;
			}
		}

		void set(size_t index_position, VALUE node_with_index)//replacing an element by index with the transmitted element
		{
			if (index_position >= 0 && index_position < get_size())
			{
				getNode(index_position)->inf = node_with_index;
			}
			else throw std::invalid_argument("out_of_range");//unexpected
		}

		bool isEmpty()//check the emptiness
		{
			return get_size() == 0;
		}

		void printl1()//the outputting result
		{
			if (isEmpty())
			{
				std::cout << "List is empty at this moment. " << std::endl;
				return;
			}
			else if (!isEmpty())
			{
				Node* temp = head;
				while (temp)
				{
					std::cout << temp->inf << " ";
					temp = temp->next;
				}
				std::cout << std::endl;
			}
		}


		~List()//destructor
		{
			clear();
		}

};