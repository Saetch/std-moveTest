// just for clarity

#include <iostream>
#include <chrono>
#include <vector>
#define AMOUNT 1000000


template <typename T>
void swap( T& a,  T& b) {
    T t = std::move(a);
    a = std::move(b);
    b = std::move(t);
}
template <typename T>
void swapOld(T& a, T& b) {
    T t = a;
    a = b;
    b = t;
}
int main()
{
     std::string a;
     std::string b;
    std::vector< std::string> vec;
    char* cp = new char;
    srand(100);
    {
 
 

        for (int i = 0; i < AMOUNT; i++) {
            a = "";
            b = "";
            for (int c = 0; c < 30; c++) {
                * cp = rand() % 65 + 65;
                a.append(cp,1);
                * cp = rand() % 65 + 65;
                b.append(cp,1);
            }

            vec.push_back(a);
            vec.push_back(b);
        }

        {
        auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
        for (int i = 0; i < AMOUNT-1; i+=2) {
            swapOld(vec[i], vec[i + 1]);
        }

        auto endMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

        printf_s("time for regular swap : %d ms\n", endMs - nowMs);
        }
        {
            auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
            for (int i = 0; i < AMOUNT - 1; i += 2) {
                swap(vec[i], vec[i + 1]);
            }

            auto endMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

            printf_s("time for move swap : %d ms\n", endMs - nowMs);

        }

        
    }
    
}

