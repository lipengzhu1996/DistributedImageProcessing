#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <linux/input.h>

#include <opencv2/opencv.hpp>

#define NUM_TARGET 2

#define PORT 8000       //use 'sudo lsof -i:8000' to find process using port and 'sudo kill -9 pid' to release port
#define BACKLOG 10
#define BUFSIZE 100

#define IMG_ROW 480
#define IMG_COL 640
#define IMG_CHAN 3
#define IMG_BUF_SIZE IMG_ROW*IMG_COL*IMG_CHAN

#endif // CONFIG_H_INCLUDED
