// Example program
#include <iostream>
#include <string>
#include <vector>

template <class T>
class CQ{

public:
    CQ (size_t const &size) : capacity(size) {
        objs.resize(size);
    }

    bool pop_front(T &data) { 
        if(isEmpty())
            return false;
        data = objs[front];
        front = (front+1) % capacity;
        current_size--;
        if (current_size == 0)
            front = back = 0;
        std::cout<<data<<std::endl;
        return true;
    }

    bool push_back(T const &data) {
        if(isFull())
            return false;
        if(isEmpty())
            back = front = 0;
        else
            back = (back + 1) % capacity;
        current_size++;
        objs[back] = data;
        return true;    
        
    }

    bool isFull() {
        return current_size == capacity;
    }

    bool isEmpty() {
        return current_size == 0;
    };
    

private:
    std::vector<T> objs;
    size_t capacity;
    size_t current_size = 0;
    int front = 0;
    int back  = 0;
};
int main()
{
    int a = 10;
    CQ <int> q(3);
    q.push_back(1);
    q.pop_front(a);
    q.push_back(2);
    q.push_back(3);
    std::cout<<q.push_back(4)<<std::endl;
    //std::cout<<std::hex<<&a<<std::dec<<std::endl;
    auto lambda = [=] () -> double {int b = a;
                           b--;
                          //std::cout<<std::hex<<&b<<std::dec<<std::endl;
                          return static_cast<double>(10*b);};
    //std::cout<<lambda()<<std::endl;
    //std::cout<<a<<std::endl;
    int result;
    q.pop_front(result);
    q.pop_front(result);
    q.pop_front(result);
    std::cout<<q.pop_front(result)<<std::endl;

}

