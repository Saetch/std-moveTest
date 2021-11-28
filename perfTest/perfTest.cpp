// just for clarity

#include <iostream>
#include <chrono>
#include <vector>
#define AMOUNT 10000000
#define TYPE 1

class Iffer {
public:
    bool newLine = true;
    bool decrease = false;
    bool writeHello = false;
    void call(int &val);
};

class Switcher{
public:
    void(*func)(Switcher* sw, int &val);


};

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

void testPerfMove() {
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
                *cp = rand() % 65 + 65;
                a.append(cp, 1);
                *cp = rand() % 65 + 65;
                b.append(cp, 1);
            }

            vec.push_back(a);
            vec.push_back(b);
        }

        {
            auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
            for (int i = 0; i < AMOUNT - 1; i += 2) {
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

void Iffer::call(int &val){
    if (writeHello) {
        std::cout << "Hello! I'm " << this << std::endl;
    }

    if (newLine && decrease) {
        std::cout << val << " decreased to" << std::endl << --val << "!" <<std::endl;

    }
    if(!newLine&&decrease) {
        std::cout << val << " decreased to" << --val << "!" << std::endl;

    }
    if (!newLine && !decrease) {
        std::cout << val << " not decreased" << std::endl;
    }
    if (newLine && !decrease) {
        //std::cout << val << " not decreased " << std::endl << "!!! " << std::endl;
    }

}

void notDecLin(Switcher* sw, int &val) {
   // std::cout << val << " not decreased " << std::endl << "!!! " << std::endl;

}


void testPerfIfElseFnctPointer() {
    using std::vector;

    vector<Iffer> vectIf;
    vector<Switcher> vectSw;
    for (int i = 0; i < AMOUNT; i++) {
        vectIf.push_back(Iffer());
        vectSw.push_back(Switcher());
    }

    int c = AMOUNT;
    {
        auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

        for (Iffer &ob : vectIf) {
            ob.call(c);
        }
        auto endMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

        printf_s("time for Iffer : %d ms\n", endMs - nowMs);
    }
    {
        for (Switcher &sw : vectSw) {
            sw.func = &notDecLin;
            //std::cout << sw.func << std::endl;
        }
        auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

        for (Switcher &sw : vectSw) {
            sw.func(&sw, c);
        }

        auto endMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

        printf_s("time for Switcher : %d ms\n", endMs - nowMs);
    }
}



int main()
{
    switch (TYPE)
    {
    case 0:
        testPerfMove();
        break;
    case 1:
        testPerfIfElseFnctPointer();
        break;
    default:
        break;
    }
    
}

