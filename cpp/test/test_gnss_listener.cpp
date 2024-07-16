#include <iostream>
#include <unistd.h>
#include <ctime>

#include "../include/GnssListener.h"
using namespace gnss::impl;



int main(int argc, char *argv[]){

    auto callback {
        [](const GnssEvent& event) {
            std::cout << "Timestamp: " << event.timeMs << endl;
            std::cout << "Sentence: " << event.sentence << endl;
        }
    };

    if (argc < 2) {
        throw invalid_argument{"Too few arguments"};
    }
    if (argv[1] == nullptr) {
        throw invalid_argument{"Invalid path"};
    }

    char *path { argv[1] };

    GnssListener listener { path, callback, 2048 };
    listener.start();

    sleep(15);

    listener.stop();

    return 0;
}
