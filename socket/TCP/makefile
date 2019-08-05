.PHONY:all
all:dict_client dict_sever

dict_sever:dict_server.cc tcp_srv.hpp tcpsocket.hpp
	g++ $^ -o $@ -std=c++11

dict_client:dict_client.cc tcp_cli.hpp tcpsocket.hpp
	g++ $^ -o $@ -std=c++11
	
  
.PHONY:clean
clean:
	rm dict_client dict_sever
