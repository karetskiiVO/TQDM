#pragma once

#include <string> 
#include <cstdio>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <type_traits>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/ioctl.h>
#endif // Windows/Linux

void get_terminal_size(int& width, int& height) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
#endif // Windows/Linux
}


std::pair<int, int> getConsolePos () {
    std::cout.flush();

    std::pair<int, int> pos;
        
    struct termios restore;
    tcgetattr(0, &restore);

    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);

    std::string buf;
    write(1, "\e[6n", 4);
    while (true) {
        char ch;
        read(0, &ch, 1);
        buf.push_back(ch);
        if (ch == 'R') break;
    }
    
    tcsetattr(0, TCSANOW, &restore);
    sscanf(buf.c_str(), "\e[%d;%dR", &pos.first, &pos.second);

    return pos;
}

void setConsolePos (std::pair<int, int> pos) {
    std::cout << "\e[" << pos.first << ";" << pos.second << "H";
    std::cout.flush();
}

template <unsigned Len = 40>
class ProgerssBar : protected std::remove_pointer_t<decltype(std::cin.rdbuf())> {
    std::pair<int, int> barPos;

public:
    ProgerssBar () {};

    void init () {
        barPos = getConsolePos();
        std::cout << '[';
        for (unsigned i = 0; i < Len; i++) std::cout << ' '; 
        std::cout << ']' << ' ' << "0%" << '\n';
    }

    void print (double percent) const {
        auto currentPos = getConsolePos();
        setConsolePos(barPos);
        
        std::cout << '[';
        for (unsigned i = 0; i < Len; i++) std::cout << (i < Len * percent ? '=' : ' '); 
        std::cout << ']' << ' ' << static_cast<int>(percent * 100) << "%";


        setConsolePos(currentPos);
    }
};

