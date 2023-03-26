#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

int main() {
	WSADATA wsa_data;

	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
		abort();
	}

	addrinfo dest_hints;
	addrinfo* dest_addr_info;
	memset((void*)&dest_hints, 0, sizeof(dest_hints));

	dest_hints.ai_socktype = SOCK_STREAM;

	std::string dest_addr = "www.google.com";
	getaddrinfo(dest_addr.data(), "http", &dest_hints, &dest_addr_info);

	auto sock = socket(dest_addr_info->ai_family, dest_addr_info->ai_socktype, dest_addr_info->ai_protocol);

	connect(sock, dest_addr_info->ai_addr, dest_addr_info->ai_addrlen);

	std::string get = "GET / HTTP/1.1\r\nHost: " + dest_addr + "\r\n\r\n";
	send(sock, get.data(), get.length(), 0);

	char buf[4096];
	memset((void*)buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);

	std::cout << buf << '\n';

	closesocket(sock);

	freeaddrinfo(dest_addr_info);
	WSACleanup();
}