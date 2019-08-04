#include <cstdio>
#include <cstdlib>

#include <mysql/mysql.h>

int main() {
    //1. 创建一个数据库操作句柄
    MYSQL* mysql = mysql_init(NULL);
    //2. 建立句柄和数据库服务器之间的联系（连接服务器）
    if(mysql_real_connect(mysql, "127.0.0.1", "root", "123","order_system2", 3306, NULL, 0) == NULL){
        printf("connect failed! %s\n", mysql_error(mysql));
        return 1;
    }
    //3. 设置编码格式(客户端与服务端要相同)
    mysql_set_character_set(mysql, "utf8");

    //4. 拼装SQL语句
    char sql[1024]  = {0};

    sprintf(sql, "select * from dish_table");
    //5. 执行SQL
    int ret = mysql_query(mysql, sql); 
    if(ret != 0){
        printf("query error %s\n", mysql_error(mysql));
        mysql_close(mysql);
        return 1;
    }
    //6. 获取并遍历结果集合
    //mysql_store_result返回多个结果集合，如果出错返回NULL
    MYSQL_RES* result = mysql_store_result(mysql);
    if(result == NULL) {
        printf("store_result:%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return 1;
    }
    //  a. 获取结果中有几行
    int row = mysql_num_rows(result);
    int field = mysql_num_fields(result);
    //  b. 根据行列遍历结果
    for(int i = 0; i < row; i++) {
        MYSQL_ROW rows = mysql_fetch_row(result);
        for(int j = 0; j < field; j++) {
            printf("%s\t",rows[j]);
        }
            printf("\n");
    }

    //  c. 断开连接
    mysql_close(mysql);
    printf("success!\n");
    return 0;
}
