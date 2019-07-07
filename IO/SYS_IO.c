/*系统调用接口
 *  open
 *      int open(const cahr *pathname, int flags, mode_t mode)
 *      pathname  文件名
 *      flags 选项标志
 *          三选一选项
 *          O_RDONLY
 *          0_WRONLY
 *          O_RDWR
 *          可选
 *          O_CREAT   文件不存在则创建，存在则打开
 *          0_TRUNC   打开文件时清空原有内容
 *          O_APPEND  写数据是追加在文件末尾
 *      mode    文件权限
 *          S_IWUSR | S_IXUSR | S_IRWXG
 *      返回值：文件描述符(正整数)   失败：-1
 *  write
 *  read
 *  lseek
 *  close
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>



