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

int main()
{
        int listen_fd, keyboard_fd;

        FD_ZERO(&fdsr);

        keyboard_fd = keyboard_init();
        listen_fd = socket_init();
        connection_init(listen_fd);

        img_buf = new uchar[IMG_BUF_SIZE];
        img.create(IMG_ROW, IMG_COL, CV_8UC3);

        while(1)
        {
                if(FD_ISSET(fd_accepted[0], &fdsr))
                        keyboard_proc(keyboard_detect(keyboard_fd));
        }

        return 0;

}

/*      old implementation of message process
//        while((ret = select(maxfd + 1, &fdsr, NULL, NULL, NULL)) > 0)
//        {
//                for(int i=0; i < num_connected; i++)
//                        if(FD_ISSET(fd_accepted[i], &fdsr))
//                        {
//                                if( !i )
//                                {
//                                        keyboard_proc(keyboard_detect(keyboard_fd));
//                                }
//                                 else
//                                        message_proc(i, img_buf, img);
//
//                        }
//
//                for (int i=0;i<num_connected;i++)
//                        if(fd_accepted[i])
//                                FD_SET(fd_accepted[i], &fdsr);
//        }
*/

//int main()
//{
//        int listen_fd, new_fd, keyboard_fd;
//        struct sockaddr_in server_addr, client_addr;
//        socklen_t sin_size = sizeof(client_addr);
//
//        int i;
//        if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//                cout<<"Creating Error!"<<endl;
//
//        int opt = SO_REUSEADDR;
//        setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
//
//        memset(&(server_addr), 0, sizeof(server_addr));
//        server_addr.sin_family=AF_INET;
//        server_addr.sin_port=htons(PORT);
//        server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
//
//        if(bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) == -1)
//                cout<<"Bind Error!"<<endl;
//
//        if(listen(listen_fd, BACKLOG) == -1)
//                cout<<"Listen Error!"<<endl;
//
//        cout<<"Ready for connection!"<<endl;
//
//        if((keyboard_fd = open("/dev/input/event4",O_RDWR)) == -1)
//                cout<<"Keyboard Error! Remember to run in root mode."<<endl;
//        fd_accepted[num_connected++] = keyboard_fd;
//
//
//        if(keyboard_fd > listen_fd)     maxfd = keyboard_fd;
//        else    maxfd = listen_fd;
//
//        FD_ZERO(&fdsr);
//        FD_SET(listen_fd, &fdsr);
//        FD_SET(keyboard_fd, &fdsr);
//
//        while(num_connected-1<NUM_TARGET)
//        {
//                if(FD_ISSET(listen_fd, &fdsr))
//                {
//                        if((new_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &sin_size)) < 0)
//                                cout<<"Accept Error!"<<endl;
//                        fd_accepted[num_connected++] = new_fd;
//                        cout<<"No."<<num_connected-1<<" connection from IP: "<<inet_ntoa(client_addr.sin_addr)<<endl;
//                        send(new_fd, "Welcome to my server.", 21, 0);
//                        if(new_fd > maxfd)
//                                maxfd = new_fd;
//                }
//        }
//
//        for ( i=0;i<num_connected;i++)
//                if(fd_accepted[i])
//                        FD_SET(fd_accepted[i], &fdsr);
//
//        for( i=0;i<num_connected;i++)
//                cout<<"fd: "<<fd_accepted[i]<<" ";
//        cout<<"All targets connected!"<<endl;
//        cout<<"Client amount: "<<num_connected-1<<endl;
//
//        int ret;
//        Mat img;
//        uchar* img_buf;
//
//        img_buf = new uchar[IMG_BUF_SIZE];
//        img.create(IMG_ROW, IMG_COL, CV_8UC3);
//
//        struct input_event *keyboard_input;
//        char keyboard_buf[BUFSIZE];
//
//        while((ret = select(maxfd + 1, &fdsr, NULL, NULL, NULL)) > 0)
//        {
//                for(int i=0; i < num_connected; i++)
//                {
//                        if(FD_ISSET(fd_accepted[i], &fdsr))
//                        {
//                                if( !i )
//                                {
//                                        cout<<"Keyboard input detected!"<<endl;
//                                        int readn = read(keyboard_fd, keyboard_buf, sizeof (struct input_event));
//                                        if (readn < 0)
//                                                cout<<"Keyboard read Error!"<<endl;
//                                        keyboard_input=(struct input_event*)keyboard_buf;
//                                       if(keyboard_input->type==EV_KEY)
//                                                cout<<"Get Keyboard Input: "<<keyboard_input->code<<"="<<keyboard_input->value<<endl;
//                                }
//                                else
//                                {
//                                        ret = recv(fd_accepted[i], &img_buf[0], IMG_BUF_SIZE, MSG_WAITALL);
//                                        img.data = img_buf;
//                                        imshow("camera", img);
//                                        waitKey(30);
//                                }
//                        }
//                }
//                for (int i=0;i<num_connected;i++)
//                        if(fd_accepted[i])
//                                FD_SET(fd_accepted[i], &fdsr);
//        }
//
//        return 0;
//}
//
//
