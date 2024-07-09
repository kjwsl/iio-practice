#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>

// TODO: Make these paths more generic

#define MAX_EVENTS 10
#define BUFF_SIZE  64

static int epoll_fd = -1;
static int sensor_fd = -1;

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
