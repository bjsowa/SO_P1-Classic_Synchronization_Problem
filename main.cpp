#include <iostream>

#include "table.h"

int main(int argc, char** argv) 
{
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " [philosophers] [bottles] [min sessions]\n";
		return 1;
	}

	srand(time(NULL));
	
	table tab(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	tab.run();

	return 0;
}