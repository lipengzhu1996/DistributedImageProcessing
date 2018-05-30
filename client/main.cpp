#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define SERVER_IP "192.168.1.110"	//IP address for server in the Ethernet
#define SERVER_PORT 8000		//service port in server
#define BUFSIZE 100

#define IMG_ROW 480                     //definition for the size of image captured by camera
#define IMG_COL 640                     //remember to calibrate when using a new camera
#define IMG_CHAN 3                      //image channels
#define IMG_BUF_SIZE IMG_ROW*IMG_COL*IMG_CHAN

#define ID 1

int main()
{
/*****declarations for arguments used in socket communication*****/
        int server_fd;			//file descriptor indicating the communication with server
        struct sockaddr_in server;	        //socket address structure storing the IP&Port info for server
        char buf[BUFSIZE];              //buffer used for sending message
        uint len;

        VideoCapture cap;
        Mat frame,img;
        uchar* img_buf;


/********************************************************/

        cap.open(0);                       //open the camera
        if( !cap.isOpened() )          //camera driver in raspberry pi is /dev/video0
                cout<<"Cannot open camera!"<<endl;

/**********Set up the communication with server****************/
        memset(&server,0,sizeof(server));       //set the structure
        server.sin_family=AF_INET;                      //define the protocol
        server.sin_addr.s_addr=inet_addr(SERVER_IP);
        server.sin_port=htons(SERVER_PORT);

        if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0)         //configure the communication
                cout<<"Socket Error!"<<endl;

        if(connect(server_fd,(struct sockaddr *)&server,sizeof(struct sockaddr))<0)
                cout<<"Connect Error!"<<endl;

        cout<<"Connected to server."<<endl;             //configuration finished

        len=recv(server_fd,buf,BUFSIZE,0);                   //receive some welcome message from server if any
        memset(&buf[len], '\0', 1);
        cout<<buf<<endl;



/*********************************************************/

        img_buf = new uchar[IMG_BUF_SIZE + 1];      //allocate exact memory for the image buffer
		img_buf[0] = ID
		
        while(1)        //information sending loop
        {
                if((len=recv(server_fd,buf,BUFSIZE,0))>0)
                {
                        memset(&buf[len], '\0', 1);
                        cout<<buf<<endl;
                        send(server_fd, "OK", 5, 0);

                        cap >> frame;           //read image information from camera
                        img_buf = frame.data;                           //convert pixel information in Mat into an uchar array

                        frame = imread("/home/pi/zhulipeng/TCP_test/multi_client/lena.jpg",IMREAD_COLOR);
                        resize(frame,img,Size(IMG_COL,IMG_ROW),0,0);
						memcpy(&img_buf[1], img.data, IMG_BUF_SIZE)                    
                        len=send(server_fd,&img_buf[0],IMG_BUF_SIZE + 1,0);         //send the image array to server 
                        if(len < IMG_BUF_SIZE)          //error detection
                                cout<<"Trans Error!"<<endl;
                }

        }

        return 0;
}
