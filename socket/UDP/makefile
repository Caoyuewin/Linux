.PHONY:all
all:udp_srv udp_cli
udp_srv:udp_srv.cpp
	g++ $< -o $@
udp_cli:udp_cli.cpp
	g++ $< -o $@

.PHONY:clean
clean:
	rm udp_srv udp_cli
