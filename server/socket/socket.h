#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "config.h"

using namespace std;
using namespace cv;

int socket_init(void);
void connection_init(int listen_fd);
void message_proc(int i, uchar* img_buf, cv::Mat& img);

int robo_connect(int);
int save_img(Mat& img);
int stop_conn(void);

string Int_to_String(int n);

#endif // SOCKET_H_INCLUDED
