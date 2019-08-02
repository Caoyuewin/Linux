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
  //3. 设置编码格式(客户端与服务端要相同)
  mysql_set_character_set(mysql, "utf8");

  //4. 拼装SQL语句
  //5. 执行SQL
  //6. 获取并遍历结果集合
  //  a. 获取结果中有几行
  //  b. 根据行列遍历结果
  //  c. 断开连接
}
