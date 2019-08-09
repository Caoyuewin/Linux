#pragma once

#include <cstdio>
#include <cstdlib>
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
            //新增菜
            bool Insert( Json::Value& dish) {
                char sql[1024 * 4] = {0};
                sprintf(sql, "insert into dish_table values(null,'%s',%d)",dish["name"].asCString(),dish["price"].asInt());
                int ret  = mysql_query(mysql_, sql);
                if(ret != 0) {
                    printf("执行sql失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                return true;
            }
            //查看所有菜品
            bool SelectAll(Json::Value* dishes) {
                char sql[1024 * 4] = {0};
                sprintf(sql, "select * from dish_table");
                int ret  = mysql_query(mysql_, sql);
                if(ret != 0) {
                    printf("执行sql失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                MYSQL_RES* result = mysql_store_result(mysql_);
                if(result == NULL) {
                    printf("获取结果失败！%s\n", mysql_error(mysql_));
                    return false;
                }
                int rows = mysql_num_rows(result);
                for(int i = 0; i < rows; ++i) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    Json::Value dish;
                    dish["dish_id"] = atoi(row[0]);
                    dish["name"] = row[1];
                    dish["price"] = atoi(row[2]);
                    dishes->append(dish);
                }
                return true;
            }  

            //查看某个菜品
            bool SelectOne(int32_t dish_id,Json::Value* dish) {
                char sql[1024 * 4] = {0};
                sprintf(sql, "select * from dish_table where dish_id = %d",dish_id);
                int ret  = mysql_query(mysql_, sql);
                if(ret != 0) {
                    printf("执行sql失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                MYSQL_RES* result = mysql_store_result(mysql_);
                if(result == NULL) {
                    printf("获取结果失败！%s\n", mysql_error(mysql_));
                    return false;
                }
               int rows = mysql_num_rows(result);
               if(rows != 1) {
                    printf("查找结果不唯一 rows = %d\n", rows);
                    return false;
               }
               for(int i = 0; i < rows; ++i) {
                   MYSQL_ROW row = mysql_fetch_row(result);
                   (*dish)["dish_id"] = atoi(row[0]);
                   (*dish)["name"] = row[1];
                   (*dish)["price"] = atoi(row[2]);
                    break;
               }
               return true;
            }
            //更新菜品
            bool Update(const Json::Value& dish) {
                char sql[1024 * 4] = {0};
                sprintf(sql,"update dish_table set name = '%s', price = %d where dish_id = %d", dish["name"].asCString(), dish["price"].asInt(), dish["dish_id"].asInt());
                int ret  = mysql_query(mysql_, sql);
                if(ret != 0) {
                    printf("执行sql失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                return true;
            }
            //删除菜品
            bool Delete(int dish_id) {
                char sql[1024 * 4] = {0};
                sprintf(sql,"delete from dish_table where dish_id = %d", dish_id);
                int ret  = mysql_query(mysql_, sql);
                if(ret != 0) {
                    printf("执行sql失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                return true;
                
            }

        private:
            MYSQL* mysql_;
    };

    class OrderTable{
        public:
            OrderTable(MYSQL* mysql) : mysql_(mysql) {}
            //查看所有订单
            bool SelectAll(Json::Value* orders) {
                char sql[1024 * 4] = {0};
                sprintf(sql, "select * from order_table");
                int ret = mysql_query(mysql_, sql);
                if(ret) {
                    printf("sql解析失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                MYSQL_RES* reslut = mysql_store_result(mysql_);
                if(reslut == NULL) {
                    printf("获取结果失败! %s\n", mysql_error(mysql_));
                    return false;
                }
                int rows = mysql_num_rows(reslut);
                for(int i = 0; i < rows; ++i) {
                    MYSQL_ROW row = mysql_fetch_row(reslut);
                    Json::Value order;
                    order["order_id"] = atoi(row[0]);
                    order["table_id"] = row[1];
                    order["time"] = row[2];
                    order["dishes"] = row[3];
                    order["state"] = row[4];
                    orders->append(order);
                }
                return true;
            }
            //新增订单
            bool Insert(const Json::Value& order) {
                char sql[1024 * 4] = {0};
                sprintf(sql, "insert into order_table values(null, '%s', '%s', '%s', %d)"
                ,order["table_id"].asCString(), order["time"].asCString()
                ,order["dishes"].asCString(), order["status"].asInt());
                int ret = mysql_query(mysql_, sql);
                if(ret) {
                    printf("sql解析失败！%s\n", mysql_error(mysql_));
                    return false;
                }
                return true;
            }    
            //改变订单状态
            bool ChangeState(const Json::Value& order) {
                char sql[1024 * 4] = {0};
                sprintf(sql, "update order_table set status = %d where order_id = %d", order["status"].asInt(), order["order_id"].asInt());
                int ret = mysql_query(mysql_, sql);
                if(ret) {
                    printf("sql解析失败！%s\n", mysql_error(mysql_));
                    return false;
                }
                return true;
            }
        private:
            MYSQL* mysql_;
    };
}//end order_system
