#include "db.hpp"
using namespace order_system;

void TestDishTable() {
    MYSQL* mysql = MYSQLInit();
    DishTable d_table(mysql);
    //测试Insert
    //dish["name"] = "黄焖鸡";
    //dish["price"] = 1300;
    //bool ret = d_table.Insert(dish);
    //if(!ret) {
    //    printf("删除失败!\n");
    //}
    //printf("删除成功！\n");

    //测试Delete
    //dish["dish_id"] = 38;
    //dish["name"] = "黄焖鸡";
    //dish["price"] = 1300;
    ////bool ret = d_table.Insert(dish);
    //bool ret = d_table.Delete(dish);
    //if(!ret) {
    //    printf("删除失败!\n");
    //}
    //printf("删除成功！\n");

    //测试SelectALL
    //Json::Value dishes;
    //int ret = d_table.SelectAll(&dishes);
    //if(!ret) {
    //    printf("查询失败！\n");
    //}
    //Json::StyledWriter writer;
    //printf("%s\n", writer.write(dishes).c_str());

    //测试SeclectOne
    //Json::Value dish;
    //int ret = d_table.SelectOne(31, &dish);
    //if(!ret) {
    //    printf("查询失败！\n");
    //}
    //Json::StyledWriter writer;
    //printf("%s\n",writer.write(dish).c_str()); 
    MYSQLRelease(mysql);
}

void  TestOrderTable() {
    MYSQL* mysql = MYSQLInit();
    OrderTable o_table(mysql);
    
    //测试SeclectALL
    //Json::Value orders;
    //int ret = o_table.SelectAll(&orders);
    //if(!ret) {
    //    printf("查看失败！%s\n");
    //}
    //Json::StyledWriter writer;
    //printf("%s\n", writer.write(orders).c_str());

    //测试Insert
    //Json::Value order;
    //order["table_id"] = "忠义堂";
    //order["time"] = "2019-08-07 21:00";
    //order["dishes"] = "[1,2,3]";
    //order["state"] = 0;
    //int ret = o_table.Insert(order);
    //if(!ret) {
    //    printf("插入失败！\n");
    //}
    //else{
    //    printf("success!\n");
    //}

    //测试ChangeState
    Json::Value order;
    order["order_id"] = 8;
    order["status"] = 1;
    o_table.ChangeState(order);
    

    

    MYSQLRelease(mysql);
}


int main() {
    //TestDishTable();
    TestOrderTable();
    return 0;
}
