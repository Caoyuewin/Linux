dish_server:dish_server.cc
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread -std=c++11

.PHONY:clean
clean:
	rm dish_server 
