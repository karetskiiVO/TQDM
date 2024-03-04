#include "tqdm.h"
#include "tqdm_tools.h"

using namespace tq;
using namespace tq::tools;

ProgressWriter::ProgressWriter () {
    if (writers.size() == 0) {
        displayed = 0;
    }

    startTime = std::chrono::system_clock::to_time_t(TQClock.now());
    writers[startTime] = this;
}

void ProgressWriter::display () {
    auto ttyHeight = ttyResolution().lines;

    std::cerr << "\es";
    while (displayed < ttyHeight && displayed < writers.size()) {
        std::cerr << "\n";
    }


    std::cerr << "\eu";
    // scroll up
}

void ProgressWriter::printProgress () {

}


ProgressWriter::~ProgressWriter () noexcept {
    writers.erase(startTime);
}

