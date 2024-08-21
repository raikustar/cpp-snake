#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <conio.h>


struct gameInfo {
	int gridHeight{ 20 }, gridWidth{ 80 }, points{ 0 }, randW{}, randH{};
	int snakeX{ gridWidth / 2 }, snakeY{ gridHeight / 2 };
	bool gameLoop{ true }, swapSnack{ true };
	char direction{ 'd' };
	int snakeTailX[100], snakeTailY[100];
	int snakeTailLength{ 0 };



	bool checkForWalls() {
		if (snakeX <= 0 || snakeX >= gridWidth - 1) {
			return true;
		}
		else if (snakeY < 0 || snakeY >= gridHeight) {
			return true;
		}
		return false;
	}

	char inputToLower(char& c) {
		return tolower(c);
	}

	int generateRandomNumber(int x, int y) {
		std::random_device rand{};
		std::mt19937 gen(rand());

		std::uniform_int_distribution<> distrib(x, y);
		return distrib(gen);
	}

	void swapSnackAfterSnakeHit() {
		if (swapSnack) {
			randW = generateRandomNumber(1, gridWidth - 2);
			randH = generateRandomNumber(1, gridHeight - 2);
			swapSnack = false;
		}

		if (snakeX == randW && snakeY == randH) {
			swapSnack = true;
			points++;
			snakeTailLength++;
		}
		
		std::cout << "x";
	}

	void updateDirection() {
		char input{};
		if (_kbhit()) {
			input = _getch();
			input = inputToLower(input);

			if (input == 'w' ||
				input == 'a' ||
				input == 's' ||
				input == 'd') {
				direction = input;
			}
		}
	}

	void snakeCollisionWithTail() {
		for (int i = 0; i <= snakeTailLength; i++) {
			if (snakeX == snakeTailX[i] && snakeY == snakeTailY[i]) {
				gameLoop = false;
			}
		}
	}


	void moveSnake() {
		for (int i = snakeTailLength; i > 0; i--) {
			snakeTailX[i] = snakeTailX[i - 1];
			snakeTailY[i] = snakeTailY[i - 1];
		}

		snakeTailX[0] = snakeX;
		snakeTailY[0] = snakeY;

		switch (direction) {
		case 'w': snakeY--; break;
		case 'a': snakeX--; break;
		case 's': snakeY++; break;
		case 'd': snakeX++; break;
		}

		if (checkForWalls()) {
			gameLoop = false;
		}
	}
};


int main() {
	gameInfo game{};
	game.randW = game.generateRandomNumber(1, game.gridWidth - 2);
	game.randH = game.generateRandomNumber(1, game.gridHeight - 2);

	while (game.gameLoop) {
		system("cls");
		std::this_thread::sleep_for(std::chrono::milliseconds(30));

		// Points board
		std::cout << "Points: " << game.points << std::endl;

		// Update
		game.updateDirection();
		game.snakeCollisionWithTail();

		// Move snake
		game.moveSnake();
		

		// Upper line
		for (int i = 0; i < game.gridWidth+1; i++) {
			std::cout << "#";
		}
		std::cout << std::endl;

		// Sides and center area
		for (int i = 0; i < game.gridHeight; i++) {
			for (int j = 0; j < game.gridWidth; j++) {
				if (j == 0 || j == game.gridWidth - 1) {
					std::cout << "#";
				}

				if (i == game.randH && j == game.randW) {
					game.swapSnackAfterSnakeHit();
				}
				else if (i == game.snakeY && j == game.snakeX) {
					std::cout << "O";
				}
				else {
					bool tailDrawn = false;
					for (int k = 0; k < game.snakeTailLength; k++) {
						if (i == game.snakeTailY[k] && j == game.snakeTailX[k]) {
							std::cout << "o";
							tailDrawn = true;
							break;
						}
					}
					if (!tailDrawn) {
						std::cout << " ";
					} 
				}
			}
			std::cout << "\n"; 
		}

		// Bottom line
		for (int i = 0; i < game.gridWidth+1; i++) {
			std::cout << "#";
		}
		std::cout << std::endl;
		std::cout << "X: " << game.snakeX << " Y:" << game.snakeY << "\n";
		}
		// game over
		if (!game.gameLoop) {
			system("cls");
			std::cout << "Game over!\n";
			std::cout << "You got: " << game.points << " points.";
		}

	
	return 0;
};



