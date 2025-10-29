#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

class AnimalUtil {
public:
    enum Animal { DOG = 1, CAT, BIRD, FISH };

    static const char* toStr(Animal a) {

        switch (a) {
            case DOG:  return "Dog";
            case CAT:  return "Cat";
            case BIRD: return "Bird";
            case FISH: return "Fish";
            default:   return "Unknown";
        }
    }
};

const std::string staticWelcomeMessage = "Welcome to the Animal Guesser!";

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << staticWelcomeMessage << "\n";

    std::cout << "\n Address of welcome message: " << &staticWelcomeMessage << "\n";

    std::cout << "Guess the Animal! (1: Dog, 2: Cat, 3: Bird, 4: Fish)\n";
    std::cout << "Enter 0 to quit.\n";

    AnimalUtil::Animal* mysteryAnimal;

    // Error #1 - see question #1
    // std::cout << "The animal is initialized to: " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
    
    // Error #2 - see question #2
    mysteryAnimal = nullptr;
    // std::cout << "The animal should initally be nothing: " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
    
    // Error #3 - Figure it out.
    while (true) {
        delete mysteryAnimal; // Added this line into the code to fix memory leak.
        mysteryAnimal =
            new AnimalUtil::Animal(static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));
        std::cout << "\n mysteryAnimal pointer address:        " << &mysteryAnimal;
        std::cout << "\n Address mysteryAnimal is pointing to: " << mysteryAnimal;
        std::cout << "\n Value located at address pointed to:  " << *mysteryAnimal;
        std::cout << "\nYour guess: ";
        int guess = -1;
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; try again.\n";
            continue;
        }
        if (guess == 0) {
            std::cout << "Bye!\n";
            break;
        }

        if (*mysteryAnimal == static_cast<AnimalUtil::Animal>(guess)) {
            std::cout << "Correct! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        } else {
            std::cout << "Wrong! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        }

    }
    delete mysteryAnimal; 
    return 0;
}
