#pragma once

#include <cstdio>
#include <cstdio>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>


namespace order_system{
  static MYSQL* MYSQLInit() {
    //创建句柄
    MYSQL* mysql = mysql_init(NULL);
    //建立连接
    //设置编码格式
  }

  static void MYSQLRelease(MYSQL* mysql) {
    mysql_close(mysql); 
  }


}//end order_system
