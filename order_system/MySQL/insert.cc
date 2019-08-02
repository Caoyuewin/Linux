//c++ 源代码文件
//cpp cxx
#include <cstdio>
#include <cstdlib>

#include <mysql/mysql.h>

int main() {
  //1. 创建一个数据库操作句柄
  MYSQL* mysql = mysql_init(NULL);
  //2. 建立句柄和数据库服务器之间的联系（连接服务器）
  if(mysql_real_connect(mysql, "127.0.0.1", "root", "","order_system2", 3306, NULL, 0) == NULL){
    printf("connect failed! %s\n", mysql_error(mysql));
    return 1;
  }
  //设置编码格式(客户端与服务端要相同)
  mysql_set_character_set(mysql, "utf8");
  //4. 拼装一个插入数据的SQL
  char* sql[1024] = {0};
  int price = 2000;
  sprintf(sql, "insert into  dish_table values(null, '京酱肉丝', %d)",price);
  //5. 执行SQL语句
  int ret = mysql_query(mysql, sql);
  if(ret != 0) {
    printf("sql执行失败！%s\n", mysql_error(mysql));
    mysql_close(mysql);
  }
  return 0;
}
