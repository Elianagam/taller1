#include <iostream>
#include <algorithm>
#include <arpa/inet.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <stdio.h>
#include "client_Client.h"

int main(int argc, char* argv[]) {
	if (argc != 3) return -1;
	Client client(argv[1], argv[2]);
	client.main();
	return 0;
}
