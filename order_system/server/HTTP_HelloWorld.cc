#include "httplib.h"

int main() {
    using namespace httplib;
    Server helloserver;
    helloserver.Get("/", [](const Request&  req, Response& resp) {
        (void)req;//不管发送什么请求都返回helloworld
        resp.set_content("<html>Hello World</html>", "text/html");
    });
    //helloserver.set_base_dir("./wwwroot");
    //0.0.0.0 表示从所有ip地址获取内容
    helloserver.listen("0.0.0.0", 9092);
    return 0;
}
