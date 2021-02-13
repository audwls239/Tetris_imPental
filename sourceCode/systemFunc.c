#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

struct termios save;

void set_ioconfig(){
    struct termios custom;      // termios 구조체 변수 custom 선언
    int fd = fileno(stdin);
    
    tcgetattr(fd, &save);
    custom = save;
    custom.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fd, TCSANOW, &custom);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}