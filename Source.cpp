#include <iostream>
#include <stdio.h>
#include "Map.cpp"

int main()
{
	Map <int, int> mapint;
	std::cout << "Map before:"; 
	mapint.insert(1, 2);
	mapint.insert(3, 4);
	mapint.insert(0, 5);
	mapint.insert(7, 9);
	mapint.print();
	std::cout << "Map after:";
	mapint.remove(3);
	mapint.print();
	
	return 0;
}