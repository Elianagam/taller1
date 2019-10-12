#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <utility> 
#include <bits/stdc++.h> 
#include "server_Acceptor.h"
#include "server_Thread.h"
#include <stdexcept>

int main(int argc, char* argv[]) {
	if (argc != 3) return -1;
	Acceptor acceptor(argv[1], argv[2]);
	acceptor.start();

	std::string buffer;
	while (1) {
		std::getline(std::cin, buffer);
		if (buffer.compare("q") == 0 || std::cin.eof()) break;
	}
	acceptor.stop();
	acceptor.join();
	return 0;
}
