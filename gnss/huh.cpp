#include <cassert>
#include <ios>
#include <stdexcept>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
#include <sys/epoll.h>
#include <initializer_list>

#include "include/huh.h"



namespace gnss::impl {
    using namespace std; 

    GnssListener::GnssListener(string_view gnss_path, const int& buf_size, const int& max_events) {
        if (buf_size < 1) {
            throw invalid_argument("Buffer size must be at least `1`");
        }

        if (max_events < 1) {
            throw invalid_argument("Max events must be at least `1`");
        }

        m_buf_size = buf_size;
        m_max_events = max_events;

        _setup(gnss_path);
    }

    void GnssListener::start() {
        if (!m_epoll_fd || !m_gnss_fd) {
            assert("somehow, epoll fd or gnss fd is empty");
        }

        epoll_event epoll_evt{
            .events = EPOLLIN,
            .data.fd = m_gnss_fd
        };

    }

    void GnssListener::set_path(string_view new_path){
        if (new_path.empty()){
            throw invalid_argument("Path is empty");
        }

        m_epoll_fd = 0;
        m_gnss_fd = 0;
        _setup(new_path);
    }

    void GnssListener::_setup(string_view path){
        int gnss_path { open(path.data(), O_RDONLY | O_NOCTTY | O_NDELAY | O_NOCTTY) };
        if (m_gnss_fd == -1) {
            throw ios_base::failure("Failed to open GNSS path");
        }
        int epoll_fd { epoll_create1(0) };
        if (epoll_fd == -1) {
            throw ios_base::failure("Failed to create epoll");
        }

        m_gnss_fd = gnss_path;
        m_epoll_fd = epoll_fd;
    }
}



int init() {
    
        
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return -1;
    }

    const char *sensor_path = argv[1];

    int sensor_fd = open(sensor_path, O_RDONLY | O_NONBLOCK | O_NOCTTY);
    if (sensor_fd == -1) {
        perror("Failed to open sensor data");
        return -1;
    }

    int epoll_fd = epoll_create1(0) ;
    if (epoll_fd == -1) {
        perror("Failed to create epoll instace");
        close(sensor_fd);
        return -1;
    }

    struct epoll_event event = {
        .events = EPOLLIN,
        .data.fd = sensor_fd
    };

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sensor_fd, &event) == -1) {
        perror("Failed to add file descriptor to epoll");
        close(sensor_fd);
        close(epoll_fd);
        return -1;
    }

    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, 1000);
        if (num_events == -1) {
            perror("epoll_wait() failed");
            break;
        }

        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == sensor_fd) {
                lseek(sensor_fd, 0, SEEK_SET);

                char buffer[BUFF_SIZE];

                ssize_t bytes_read = read(sensor_fd, buffer, sizeof(buffer) - 1);
                buffer[bytes_read] = '\0';

                printf("Sensor value: %s\n", buffer);
            }
        }

    }

    close(sensor_fd);
    close(epoll_fd);

    return 0;
}
