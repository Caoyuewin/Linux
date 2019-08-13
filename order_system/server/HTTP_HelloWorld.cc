#include "httplib.h"

int main() {
    using namespace httplib;
    Server helloserver;
    //helloserver.Get("/", [](const Request&  req, Response& resp) {
    //    //resp.set_content("<html>Hello World</html>", "text/html");
    //    resp.
    //}); 
    helloserver.set_base_dir("../client");
    //0.0.0.0 表示从所有ip地址获取内容
    helloserver.listen("0.0.0.0", 9092);
    return 0;
}
