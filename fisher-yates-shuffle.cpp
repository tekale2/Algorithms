#include <iostream>
#include <random>
#include <cstdlib>
using namespace std;

// generates a random number within range
int GenRandomNumRange(int const start, int const end) {
    int range = end - start + 1;
    return std::rand() % range + start;
}

class FisherYates {
public:
    FisherYates(std::vector<int> const &input) {
        original = input;
        shuffled = input;
    }
    
    void Reset() {
        original = shuffled;
    }
    
    std::vector<int> Shuffle() {
        for (int i = 0; i < shuffled.size() - 1; ++i) {
            int j = GenRandomNumRange(i, shuffled.size() - 1);
            std::swap(shuffled[i], shuffled[j]);
        }
        return shuffled;
    }
private:
    std::vector<int> original;
    std::vector<int> shuffled;
};
int main()
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::srand(rd());
    std::uniform_int_distribution<int> uniform_dist(3, 99);
    std::vector<int> input(20,0);
    
    for(int i = 0; i < 20; ++i)
        input[i] = uniform_dist(eng);

    for(int const &i: input) {
        std::cout<<i<<" ";
    }
     std::cout<<std::endl;
    FisherYates fy(input);
    std::vector<int> output = fy.Shuffle();
    for(int const &i: output) {
        std::cout<<i<<" ";
    }
     std::cout<<std::endl;
    
    output = fy.Shuffle();
    for(int const &i: output) {
        std::cout<<i<<" ";
    }
     std::cout<<std::endl;
    return 0;
}
