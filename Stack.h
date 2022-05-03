#pragma once
#include <stdio.h>
#include <iostream>
#include <stdexcept>

template <typename KEY>
class stack
{
private:

	class Element
	{
	public:
		KEY data;
		Element* previous; //pointer to the previous element

		Element(KEY element) //constructor
		{ 
			this->data = element;
			previous = NULL;
		}
	};
	Element* top_element;//pointer to the top (last element)
	size_t size;

public:

	stack()//constructor
	{
		top_element = NULL;
		size = 0;
	}
	~stack()//destructor
	{
		while (top_element)
			pop();
	}

	KEY getTop() //get top
	{
		return top_element->data;
	}

	bool isEmpty()//check the emptiness
	{
		return (size == 0);
	}

	size_t getSize()//get size
	{
		return size;
	}
	
	void push_back(const KEY element)//add to the end
	{
		Element* buffer = top_element;
		top_element = new Element(element);
		top_element->previous = buffer;
		size++;
	}
	
	void pop() //remove top
	{
		if (size) {
			Element* temp = top_element->previous;
			delete top_element;
			top_element = temp;
			size--;
		}
		else
			throw std::out_of_range("Empty!");
	}
};