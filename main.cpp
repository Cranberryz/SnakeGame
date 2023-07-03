// V1
#include <iostream>
#include <conio.h>
#include <windows.h>

// Variables
bool gameOver; // Is the game over or not
const int width = 40; // An unchanging(constant) variable
const int height = 20;
int x, y, fruitX, fruitY, score; // 5 different variables with integer values
int tailX[100], tailY[100]; // An array of type integer from 0-100
int nTail; // Integer type variable
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN}; // enumeration with only available directions
eDirection dir;

void Setup() // Function to store necessary variables to use through out the program
{
	gameOver = false; // Set bool to false to allow game to play
	dir = STOP; // Set direction to stop to initialize it
	x = width / 2; // Set inital position to be the center of the screen
	y = height / 2;
	fruitX = rand() % width; // Set position of the fruit
	fruitY = rand() % height;
	score = 0; // Set value of score
}

void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Built in windows function to set cursor postion(purpose is to stop windows terminal from flickering)
	
	for (int i = 0; i < width + 2; i++) // loop to add # to variable i and print it equal to the value of variable width + 2
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++) // Nested loop to count the length of height, and the length of width in order to print Player, Walls, and Fruit
	{
		for (int j = 0; j < width; j++) 
		{
			if (j == 0) // Add the left wall
				std::cout << "#";
			if (i == y && j == x) // Add the player using variables y and x 
				std::cout << "O";
			else if (i == fruitY && j == fruitX) // Add the fruit using variables fruitY and fruitX
				std::cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) // Check if there is tail in position k
				{
					if (tailX[k] == j && tailY[k] == i) // Print tail if the poisition is correct
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print) // Otherwise, if there is no player, tail, wall, or fruit, print a blank space
					std::cout << " ";
			}
			
			if (j == width - 1) // Print right side wall
				std::cout << "#";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 2; i++) // Print bottom floor
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl; // Print score
}

void Input() // Function to get the user input
{
	if (_kbhit()) // Conio function to get keyboard hits
	{
		switch (_getch()) // Switch is a better alternative to if statements to test the conio function _getch against the 'case'
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() // Function to code the logic of every input and positioning
{
	int prevX = tailX[0]; // define and set values to variables
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) // For loop to set position to new tail values added behind the player
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) // Add the movement to the player using the player's direction
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	// if (x > width || x < 0 || y > height || y < 0)
		// gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1; // If statements to change position of player and tail when interacts with a wall or floor or ceiling
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++) // If statement to end the game if player interacts with tail
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY) // If statement to add tail and set position of fruit as well as add score
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main() // Call functions to start the game
{
	Setup();
	while (!gameOver) 
	{
		Draw();
		Input();
		Logic();
		Sleep(100); // Windows function to slow down the speed of the terminal fps 
	}
	return 0;
}
