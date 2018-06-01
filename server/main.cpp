#include "config.h"
#include "keyboard.h"
#include "socket.h"

using namespace std;
using namespace cv;

int fd_accepted[BACKLOG];
int num_connected = 0;
int maxfd = 0;
fd_set fdsr;

Mat img;
uchar* img_buf;
int ind = 1;

int main()
{
        int listen_fd;
//        int keyboard_fd;
        int ret;

        FD_ZERO(&fdsr);

   //     keyboard_fd = keyboard_init();
        listen_fd = socket_init();
        connection_init(listen_fd);

        img_buf = new uchar[IMG_BUF_SIZE + 1];
        img.create(IMG_ROW, IMG_COL, CV_8UC3);

        while((ret = select(maxfd + 1, &fdsr, NULL, NULL, NULL)) > 0)
        {
                for(int i=0; i < num_connected; i++)
                        if(FD_ISSET(fd_accepted[i], &fdsr))
                        {
                                message_proc(i, img_buf, img, ind);
                                ind ++;
                                cout<<ind<<endl;
                                if(ind == 10)
                                        return 0;
                        }

                for (int i=0;i<num_connected;i++)
                        if(fd_accepted[i])
                                FD_SET(fd_accepted[i], &fdsr);
        }
        return 0;
}
