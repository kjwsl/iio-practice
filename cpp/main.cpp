#include <iostream>

#include "include/GnssListener.h"

int main(){
    auto callback {
        [](ssize_t /* buf_cnt */, char buffer[]) {
            std::cout << "Sensor val: " << buffer << std::endl;
        }
    };

    gnss::impl::GnssListener listener { "/dev/ttyAMA0", callback};
    listener.start();

    return 0;
}
