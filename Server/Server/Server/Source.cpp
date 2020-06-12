#include <SFML/Network.hpp>
#include <iostream>
#include "windows.h"
#include "time.h"
using namespace sf;
int main()
{
	while (true) {
		srand(time(NULL));
		IpAddress ip = "172.0.0.1";
		TcpSocket socket;
		TcpListener listener;
		std::size_t received;
		listener.listen(2000);
		listener.accept(socket);
		int shoot;
		socket.receive((char*)&shoot, sizeof(shoot), received);
		if (shoot == 1) {
			int x = rand() % 10;
			int y = rand() % 10;
			socket.send((char*)&x, sizeof(x));
			socket.send((char*)&y, sizeof(y));
			shoot = 0;
		}
	}
return 0;
}
	
