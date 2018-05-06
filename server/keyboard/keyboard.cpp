#include "keyboard.h"
#include "socket.h"

using namespace std;
using namespace cv;

extern int fd_accepted[];
extern int num_connected;
extern int maxfd;
extern fd_set fdsr;

extern Mat img;
extern uchar* img_buf;

int keyboard_init(void)
{
        int keyboard_fd;

        if((keyboard_fd = open("/dev/input/event4",O_RDWR)) == -1)
                cout<<"Keyboard Error! Remember to run in root mode."<<endl;
        fd_accepted[num_connected++] = keyboard_fd;

        if(keyboard_fd > maxfd)
                maxfd = keyboard_fd;

        FD_SET(keyboard_fd, &fdsr);

        return keyboard_fd;
}

int keyboard_detect(int keyboard_fd)
{
        char keyboard_buf[BUFSIZE];
        struct input_event *keyboard_input;

        int readn = read(keyboard_fd, keyboard_buf, sizeof (struct input_event));
        if (readn < 0)
                cout<<"Keyboard read Error!"<<endl;
        keyboard_input=(struct input_event*)keyboard_buf;
       if(keyboard_input->type==EV_KEY)
                cout<<"Get Keyboard Input: "<<keyboard_input->code<<"="<<keyboard_input->value<<endl;

        return keyboard_input->code;
}

void keyboard_proc(int code)
{
        switch (code)
        {
        case 2:                                 //press '1'
                if(!robo_connect(1))
                        message_proc(1, img_buf, img);
                break;

        case 3:                                 //press '2'
                if(!robo_connect(2))
                        message_proc(2, img_buf, img);
                break;

        case 4:                                 //press '3'
                if(!robo_connect(3))
                        message_proc(3, img_buf, img);
                break;

        case 31:                                //press 'S'
                save_img(img);
                break;

        case 16:                                 //press 'Q'
                stop_conn();
                break;

        default:
                cout<<"Invalid Input"<<endl;
                break;
        }

}
