#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "common.h"

void create_file(const char* file);
void open_file(const char* file);
void read_file(const char* file);

int main() {

    //重新创建文件并写入
    create_file(out_file_path("io_simple_01"));

    //打开并写入
    open_file(out_file_path("io_simple_02"));

    //读取文件内容
    read_file("read_text");

    return 0;
}



/**
 * 打开并写入
 * @param file 文件名
 */
void open_file(const char* file) {

    //O_CREAT 文件不存在则创建
    //O_RDWR 读写文件
    //O_TRUNC 打开时将文件长度置为0，即读写会从0位置开始
    int fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
    fchmod(fd, 0666);       //重新设置权限，open对已存在文件并不会修改其mode

    char buff[] = "open_file\n";
    int result = write(fd, buff, strlen(buff));
    if(result < 0) {
        //写入失败打印错误信息
        printf("%s", strerror(errno));
        return;
    }

    printf("%s\n", "写入成功");

    fsync(fd);
    close(fd);
}




/**
 * 使用creat系统调用创建文件并写入信息
 * @param file 文件名
 */
void create_file(const char* file) {

    //存在则删除
    int exists = access(file,F_OK);
    if(exists >= 0) {
        remove(file);
    }

    //creat等价于open(path, O_CREAT | O_TRUNC | O_WRONLY, mode)
    int fd = creat(file, 0666);
    char buff[] = "create_file\n";
    int result = write(fd, buff, strlen(buff));
    if(result < 0) {
        //写入失败打印错误信息
        printf("%s", strerror(errno));
        return;
    }

    printf("%s\n", "写入成功");

    fsync(fd);
    close(fd);
}

/**
 * 读取文件内容
 * @param file
 */
void read_file(const char* file) {

    int fd = open(file, O_RDONLY);
    if(fd < 0) {
        printf("%s", strerror(errno));
        return;
    }

    int length = 10;
    int len = 0;
    int max = 0;
    int pos = 0;
    char* buff = NULL;
    for (;;) {
        if(pos >= max) {
            max = max + length;     //不考虑溢出

            //realloc:
            //  1.若第一个参数可为NULL则会开始分配一个地址
            //  2.分配失败返回值为NULL,此时应该考虑用free回收原来的内存
            char* new_buff = (char *) realloc(buff, max * sizeof(char));
            if(!new_buff) {
                free(buff);
                printf("%s", strerror(errno));
                return;
            }
            buff = new_buff;
        }

        len = read(fd, buff + pos, max - pos);
        pos += len;
        if(len <= 0) {
            break;
        }
    }

    printf("%s\n", buff);
    free(buff);
    close(fd);
}