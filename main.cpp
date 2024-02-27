#include <iostream>

#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    
    //void sleep(unsigned milliseconds)
    //{
    //    usleep(milliseconds * 1000); // takes microseconds
    //}
#endif

int main () {
    size_t cnt = 0;

    std::cout << "[";
    for (size_t i = 0; i < 40; i++) {
        std::cout << (i < cnt ? '=' : ' ');
    }
    std::cout << "]\naboba\n";

    while (true) {
        std::cout << "\x1b[s" << "\x1b[2A";
        std::cout << "[";
        for (size_t i = 0; i < 40; i++) {
            std::cout << (i < cnt ? '=' : ' ');
        }
        std::cout << "]\x1b[u";
        
        sleep(1);

        cnt = (cnt + 1) % 40;
        std::cout.flush();
    }
    
    return 0;
}