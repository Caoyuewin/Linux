.PHONY:all
all:dish_server Test_server
dish_server:dish_server.cc
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread -std=c++11
Test_server:HTTP_HelloWorld.cc
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread -std=c++11

.PHONY:clean
clean:
	rm dish_server Test_server
