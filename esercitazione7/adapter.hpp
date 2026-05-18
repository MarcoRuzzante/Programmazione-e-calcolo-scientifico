#include <list>

template <typename T>
class fifo {
    std::list<T> c;
public:
    fifo() = default;
    
    void put(const T& val) { c.push_back(val); }
    T get() { 
        T val = c.front(); 
        c.pop_front(); 
        return val; 
    }
    bool empty() const { return c.empty(); }
};

template <typename T>
class lifo {
    std::list<T> c;
public:
    lifo() = default;
    
    void put(const T& val) { c.push_front(val); }
    T get() { 
        T val = c.front(); 
        c.pop_front(); 
        return val; 
    }
    bool empty() const { return c.empty(); }
};