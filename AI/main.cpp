#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "mtrand.h"
#include "Board.h"
#include <time.h>
#include "MoveGenerator.h"

/*
Initializes the Board object from the input file.
*/
Board loadBoard(std::ifstream &in)
{
	unsigned int height, width, numShips, shipLength;
	std::string terminate;

	in >> height >> width >> numShips; // Board info
	Ship** ships = new Ship*[numShips]; // Ships list
	Board b(height, width, numShips, ships); // Board object
	
	// Places each ship on the board and assigns nodes to them
	for (unsigned int i = 0; i < numShips; i++)
	{
		in >> shipLength;
		unsigned int x[shipLength];
		unsigned int y[shipLength];
		Ship* s = new Ship(shipLength, "temp");
		for (unsigned int j = 0; j < shipLength; j++)
			in >> y[j] >> x[j];
		b.addShip(x, y, s, shipLength, i);
	}

	in >> terminate;
	assert(terminate == "end"); // Ensure that we are at the end of the input file.
	return b;
}

/*
Takes an input file of board data and an output file for move guesses.
*/
int main(int argc, char** argv)
{
	if(argc != 7) // input, output, type of move generator, time per each move calculation (results are returned after hitting the time in seconds), and whether or not to enable debugging output to std::cout
	{
		std::cerr << "Proper usage is: " << argv[0] << " input_file.txt output_file.txt generator_type(1=random, 2=deterministic, 3=machine_learning) time_per_calculation debugging_toggle(true=output_on, false=output_off), number_of_iterations." << std::endl;
		return -1;
	}

	unsigned long int iterations = 0;
	unsigned long int numTurns[100] = {};
	unsigned long int n = atoi(argv[6]);
	bool debuggingOutput = false;

	while (iterations < n)
	{
		std::ifstream boardInput(argv[1]);
		if (!boardInput)
		{
			std::cerr << "Couldn't open " << argv[1] << " for reading." << std::endl;
			return -1;
		}

		std::ofstream moveOutput(argv[2]);
		if (!moveOutput)
		{
			std::cerr << "Couldn't open " << argv[2] << " for writing." << std::endl;
			return -1;
		}

		Board b = loadBoard(boardInput);

		std::string out_put = argv[5];
		if (out_put == "true")
			debuggingOutput = true;

		if (debuggingOutput)
			std::cout << b << std::endl;

		unsigned int generatorType = atoi(argv[3]); // 1 is for a random generator, 2 is for a deterministic generator, and 3 is for the AI
		unsigned int timePerCalculation = atoi(argv[4]); // Time is in seconds

		MoveGenerator g(timePerCalculation, generatorType, &b);
		
		setvbuf(stdout, NULL, _IONBF, 0);

		while (!g.solved())
		{
			unsigned int i, j;
			g.findNextMove(i, j);
			//moveOutput << i << " " << j << std::endl;
			
			std::cout << i << " " << j << std::endl;
		}
		if (debuggingOutput)
			g.Win();

		iterations++;
		numTurns[b.getTurn()-1]++;
	}
	if (debuggingOutput)
	{
		for (unsigned int i = 16; i < 100; i++)
			std::cout << "Games that ended in " << i+1 << " turn(s): " << numTurns[i] << std::endl;
		std::cout << "Total Simulations: " << n << std::endl;
	}

	return 0;
}