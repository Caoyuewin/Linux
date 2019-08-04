#pragma once

#include <cstdio>
#include <cstdio>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>


namespace order_system{
    static MYSQL* MYSQLInit() {
        //创建句柄
        MYSQL* mysql = mysql_init(NULL);
        if(mysql_real_connect(mysql, "127.0.0.1", "root", "123", "order_system2", 3306, NULL,0) == NULL){
            printf("connect failed: %s\n", mysql_error(mysql));
            return NULL;
        }
        //设置字符集
        mysql_set_character_set(mysql, "utf8");
        return mysql;
    }

    static void MYSQLRelease(MYSQL* mysql) {
        mysql_close(mysql); 
    }

    class DishTable{
        public:
            DishTable(MYSQL* mysql):mysql_(mysql)
            {}

        private:
            MYSQL* mysql_;
    };

}//end order_system
