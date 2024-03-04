#pragma once

#ifndef TQDM_h
#define TQDM_h

#include <map>
#include <chrono>
#include <cstdint>
#include <iostream>

namespace tq {

std::chrono::system_clock TQClock;

using LenType = uint32_t;

class ProgressWriter {
    static size_t displayed; 
    static std::map<std::time_t, ProgressWriter*> writers;
    std::time_t startTime;
public:
    ProgressWriter ();

    void display ();
    virtual void printProgress ();

    ProgressWriter (ProgressWriter&&)                = delete;
    ProgressWriter (const ProgressWriter&)           = delete;
    ProgressWriter operator= (ProgressWriter&&)      = delete;
    ProgressWriter operator= (const ProgressWriter&) = delete;

    ~ProgressWriter () noexcept;
};







}

#endif // tqdm.h