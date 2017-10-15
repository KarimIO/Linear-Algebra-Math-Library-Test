#include <stdexcept>
#include <iostream>
#include "game.hpp"

int main() {
	try {
		Game game;
		game.Run();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what();
	}

	return 0;
}
