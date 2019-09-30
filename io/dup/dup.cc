#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

#include "common.h"

void dup(const char* file);
void dup2();
void fcntl_dup();


int main() {

    dup("../resource/read_text");

    dup2();

    fcntl_dup();

    return 0;
}

void dup(const char* file) {

    print_line("dup");

    char c;

    int fd = open(file, O_RDONLY);
    read(fd, &c, 1);
    printf("%c", c);

    int cfd = dup(fd);
    read(cfd, &c, 1);
    printf("%c", c);

    close(fd);
    close(cfd);
}


void dup2() {

    print_line("dup2");

    int cfd = dup(STDOUT_FILENO);
    write(cfd, "hello\n", 5);

    close(cfd);
}

void fcntl_dup() {

    print_line("fcntl_dup");

    //复制STDOUT_FILENO描述符给一个大于等于0(第三参数指定)且未使用的文件描述符
    int cfd = fcntl(STDOUT_FILENO, F_DUPFD, 0);

    write(cfd, "hello\n", 5);

    close(cfd);

}