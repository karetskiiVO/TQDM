#pragma once

#ifndef TQDM_TOOLS_h
#define TQDM_TOOLS_h

namespace tq {
namespace tools {

#ifdef linux
    #include <cstdio>
    #include <sys/ioctl.h>
#endif
#ifdef WIN_32


#endif

struct TTYRes {
    size_t lines = 0;
    size_t cols = 0; 
};

TTYRes ttyResolution () {
    TTYRes res;

#ifdef linux
    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    res = TTYRes{w.ws_row, w.ws_col};
#endif
#ifdef WIN_32



#endif

    return res;
}






}}

#endif // tqdm_tools.h