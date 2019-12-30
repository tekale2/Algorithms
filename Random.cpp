#include <iostream>
#include <random>

using namespace std;

int main()
{
    std::random_device rd; // starts off with a truly random state
    std::mt19937 eng(rd()); // Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits 
    std::uniform_int_distribution<int> uniform_dist(3, 99); // uniform distribution generator
    
    for(int i = 0; i < 20; ++i)
        std::cout<<uniform_dist(eng)<<std::endl;

    return 0;
}
