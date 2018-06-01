#include "socket.h"

extern int errno;

extern int fd_accepted[];
extern int num_connected;
extern int maxfd;
extern fd_set fdsr;

string str="image";
int num=0;

int socket_init(void)
{
        int listen_fd;
        struct sockaddr_in server_addr;

        if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
                cout<<"Creating Error!"<<endl;

        int opt = 1;
        setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        memset(&(server_addr), 0, sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(PORT);
        server_addr.sin_addr.s_addr = htonl (INADDR_ANY);

        if(bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) == -1)
                cout<<"Bind Error!"<<errno<<endl;

        if(listen(listen_fd, BACKLOG) == -1)
                cout<<"Listen Error!"<<endl;

        cout<<"Ready for connection!"<<endl;

        if(listen_fd > maxfd)
                maxfd = listen_fd;

        FD_SET(listen_fd, &fdsr);

        return listen_fd;
}

void connection_init(int listen_fd)
{
        int new_fd;
        struct sockaddr_in client_addr;
        socklen_t sin_size = sizeof(client_addr);

        while(num_connected<NUM_TARGET)
        {
                if(FD_ISSET(listen_fd, &fdsr))
                {
                        if((new_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &sin_size)) < 0)
                                cout<<"Accept Error!"<<endl;
                        fd_accepted[num_connected++] = new_fd;
                        cout<<"No."<<num_connected-1<<" connection from IP: "<<inet_ntoa(client_addr.sin_addr)<<endl;
                        send(new_fd, "Welcome to my server", 20, 0);

                        if(new_fd > maxfd)
                                maxfd = new_fd;
                }
        }

        for (int i=0;i<num_connected;i++)
                if(fd_accepted[i])
                        FD_SET(fd_accepted[i], &fdsr);

        for(int i=0;i<num_connected;i++)
                cout<<"fd: "<<fd_accepted[i]<<" ";
        cout<<"All targets connected!"<<endl;
        cout<<"Client amount: "<<num_connected-1<<endl;

}

void message_proc(int i, uchar* img_buf, Mat& img, int ind)
{
        int ret;
        char* s = new char[IMG_BUF_SIZE];

       ret = recv(fd_accepted[i], img_buf, IMG_BUF_SIZE +  1, MSG_WAITALL);
        if(ret < IMG_BUF_SIZE + 1)
                cout<<"Image receive error!"<<endl;

         cout<<"Image from No."<<int(img_buf[0])<<" Robot!"<<endl;

        memcpy(img.data, &img_buf[1], IMG_BUF_SIZE);
        sprintf(s, "/home/hadoop/workspace/imgs/%d.jpg", ind);
        imwrite(s, img);

//        imshow("camera", img);
 //       waitKey(0);
}

int robo_connect(int num)
{
        char buf[20];

        send(fd_accepted[num],"Connection Request",18,0);
        recv(fd_accepted[num], &buf, 5, MSG_WAITALL);
        if(strcmp(buf, "Ready"))
        {
                cout<<"Connection with Robot"<<num<<" is OK"<<endl;
                return 0;
        }
        else
        {
                cout<<"Connection error!"<<endl;
                return 1;
        }

}

int save_img(Mat& img)
{
        string img_name;
        img_name = str + Int_to_String(++num);

        imwrite(img_name, img);
        return 0;
}

int stop_conn(void)
{
        return 0;
}

string Int_to_String(int n)
{
        ostringstream stream;
        stream<<n;
        return stream.str();

}
