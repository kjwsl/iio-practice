#include <iostream>
#include <unistd.h>

#include "../include/GnssListener.h"
using namespace gnss::impl;



int main(int argc, char *argv[]){

    auto callback {
        [](ssize_t /* buf_cnt */, string_view buffer) {
            std::cout << "Sensor val: " << buffer << std::endl;
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
