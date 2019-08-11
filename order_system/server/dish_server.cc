#include "httplib.h"
#include "mysql/mysql.h"
#include "../db.hpp"

MYSQL *mysql = NULL;
//GetDishes
bool GetDishes(const Json::Value &dish_ids, Json::Value *dishes, order_system::DishTable &dish_table)
{
    for (uint32_t i = 0; i < dish_ids.size(); ++i)
    {
        int dish_id = dish_ids[i].asInt();
        Json::Value dish_info;
        bool ret = dish_table.SelectOne(dish_id, &dish_info);
        if (!ret)
        {
            printf("Select dish %d failed! \n", dish_id);
            continue;
        }
        dishes->append(dish_info);
    }
    return true;
}

int GetConsume(const Json::Value &dishes)
{
    int consume = 0;
    for (uint32_t i = 0; i < dishes.size(); ++i)
    {
        consume += dishes[i]["price"].asInt();
    }
    return consume;
}

int main()
{
    using namespace httplib;
    using namespace order_system;

    Server server;
    //1. 数据库客户端初始化和释放
    mysql = MYSQLInit();
    signal(SIGINT, [](int) {MYSQLRelease(mysql);exit(0); });
    DishTable dish_table(mysql);
    OrderTable order_table(mysql);

    //2. 设置路由
    //新增菜品
    server.Post("/dish", [&dish_table](const Request &req, Response &resp) {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value req_json;
        Json::Value resp_json;
        //1. 请求解析成Json格式
        bool ret = reader.parse(req.body, req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "parse Request failed!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        //2. 进行参数校验
        if (req_json["name"].empty() || req_json["price"].empty())
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Request has no name or price!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        //3. 调用数据库接口进行操作数据
        ret = dish_table.Insert(req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Insert failed!\n";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        //4. 插入成功
        resp_json["ok"] = true;
        resp.set_content(writer.write(resp_json), "application/json");
        return;
    });
    //查看所有菜品
    server.Get("/dish", [&dish_table](const Request &req, Response &resp) {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value resp_json;
        Json::Value dishes;
        bool ret = dish_table.SelectAll(&dishes);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "SelectAll failed!\n";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        resp.set_content(writer.write(dishes), "application/json");
        return;
    });
    //删除菜品
    server.Delete(R"(/dish/(\d+))", [&dish_table](const Request &req, Response &resp) {
        Json::FastWriter writer;
        Json::Value resp_json;
        //1. 解析 获取dish_id
        int dish_id = std::stoi(req.matches[1]);
        //2. 删除菜品
        bool ret = dish_table.Delete(dish_id);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Delete failed!\n";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        resp_json["ok"] = true;
        resp.set_content(writer.write(resp_json), "application/json");
        return;
    });
    //修改菜品
    server.Put(R"(/dish/(\d+))", [&dish_table](const Request &req, Response &resp) {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value req_json;
        Json::Value resp_json;
        int dish_id = std::stoi(req.matches[1]);
        //校验菜品信息
        bool ret = reader.parse(req.body, req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Parse failed!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        //补上dish_id
        resp_json["dish_id"] = dish_id;
        if (req_json["dish_id"].empty() || req_json["price"].empty())
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Request has no name  or price!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        ret = dish_table.Update(req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Update failed!\n";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        resp_json["ok"] = true;
        resp.set_content(writer.write(resp_json), "application/json");
        return;
    });
    //新增订单 测试通过！
    server.Post("/order", [&order_table](const Request &req, Response &resp) {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value req_json;
        Json::Value resp_json;

        bool ret = reader.parse(req.body, req_json);
        if (!ret)
        {
            resp_json["ok"] = false;
            resp_json["reason"] = "Parse failed!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        if (req_json["time"].empty())
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Request has no table_id or time!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        //转换接口，吧dishes转换成字符串，存到dishes中，数据库中插入dishes
        const Json::Value &dish_ids = req_json["dishes"];
        req_json["dishes"] = writer.write(dish_ids);
        ret = order_table.Insert(req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Update failed!\n";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        resp_json["ok"] = true;
        resp.set_content(writer.write(resp_json), "application/json");
        return;
    });
    //修改订单状态
    server.Put(R"(/order/(\d+))", [&order_table](const Request &req, Response &resp) {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value req_json;
        Json::Value resp_json;

        int order_id = std::stoi(req.matches[1]);

        bool ret = reader.parse(req.body, req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "Parse failed!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        printf("parsed!\n");
        //补充order_id
        req_json["order_id"] = order_id;
        if (req_json["order_id"].empty() || req_json["state"].empty())
        {
            resp_json["ok"] = false;
            resp_json["reason"] = "Request has no order_id or status!\n";
            resp.status = 400;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        printf("content ok!\n");

        ret = order_table.ChangeState(req_json);
        if (!ret)
        {
            resp_json["ok]"] = false;
            resp_json["reason"] = "ChangeState failed failed!\n";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
            return;
        }
        printf("ChangeState ok!\n");
        resp_json["ok"] = true;
        resp.set_content(writer.write(resp_json), "application/json");
        return;
    });
    //获取订单
    server.Get("/order", [&order_table, &dish_table](const Request &req, Response &resp) {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value resp_json;
        //查看菜品没有请求参数
        Json::Value orders;
        bool ret = order_table.SelectAll(&orders);
        if (!ret)
        {
            resp_json["ok"] = false;
            resp_json["reason"] = "SelectAll failed";
            resp.status = 500;
            resp.set_content(writer.write(resp_json), "application/json");
        }
        for (uint32_t order_index = 0; order_index < orders.size(); ++order_index)
        {
            Json::Value &order = orders[order_index];
            Json::Value dish_ids;
            ret = reader.parse(order["dishes"].asString(), dish_ids);
            if (!ret)
            {
                printf("No.%d parsefailed\n", order_index);
                continue;
            }
            //GetDishes(dish_ids, &order["dishes"], dish_table);
            //order["consume"] = GetConsume(order["dishes"]);
        }
        resp.set_content(writer.write(orders), "application/json");
        return;
    });
    //获取用户客户端，匹配桌子id
    server.Get(R"(/client/table/(\S+))", [](const Request &req, Response &resp) {

    });
    //设置静态文件目录
    server.set_base_dir("../client");
    server.listen("0.0.0.0", 9092);
    return 0;
}
