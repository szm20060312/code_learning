#include <iostream>
using namespace std;
enum Color {RED, GREEN, BLUE};
int main(){
    Color myColor = RED;
    switch (myColor) {
        case RED:
            std::cout << "The color is red." << std::endl;
            break;
        case GREEN:
            std::cout << "The color is green." << std::endl;
            break;
        case BLUE:
            std::cout << "The color is blue." << std::endl;
            break;
        default:
            std::cout << "Unknown color." << std::endl;
    }
    return 0;
}