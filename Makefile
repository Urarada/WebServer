serv: http.o server.o
	g++ -o serv server.o http.o
server.o: server/server.cpp server/server.h
	g++ -c server/server.cpp
http.o: http/http.cpp http/http.h
	g++ -c http/http.cpp
# cli: client.o
# 	g++ -o cli client.o
# client.o: client/client.cpp mws.h
# 	g++ -c client/client.cpp
clean:
	rm serv server.o http.o cli client.o