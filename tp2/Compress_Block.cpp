#include <iostream>
#include <bits/stdc++.h> 
#include <algorithm>
#include <vector>
#include <cmath>
#include <arpa/inet.h>
#include <queue>
#include <string>
#include <stdio.h>
#include <fstream>
#include "Compress_Block.h"

Compress_Block::Compress_Block() {}

void Compress_Block::set_min_bits(uint8_t num) {
	min_bit = num;
}

void Compress_Block::convert_to_binary(uint32_t num) {
	int total = 0;
	
	std::vector<bool> number;
	for (int i = 0; i < min_bit; i++) {
		if (num > 0) {
			total = num % 2;
			num /= 2;
			number.insert(number.begin(), total);
		} else {
			number.insert(number.begin(), 0);
		}
	}
	save_number(number);
}

void Compress_Block::save_number(std::vector<bool> &number) {
	for (bool bit : number)
		compress_v.insert(compress_v.begin(), bit);
}

void Compress_Block::to_byte() {
	// tranforma el vector de 0's y 1's en chars sifteando
	len = (compress_v.size() + 8 -1) / 8;

	for (uint32_t i = 0; i < compress_v.size(); i += 8) {
		char c = 0;
		for (uint32_t j = 0; j < 8; j++) {
			if (compress_v[j+i]) {
				c += 1 << j;
			}
		}
		char_v.insert(char_v.begin(), c);
	}
}

std::vector<char> Compress_Block::compress(std::vector<uint32_t> *block) {
	for (uint32_t hex : *block)
		convert_to_binary(hex);

	align();
	to_byte();
	return std::move(char_v);
}

void Compress_Block::align() {
	while (compress_v.size() % 8 != 0) {
		compress_v.insert(compress_v.begin(), 0);
	}
}

Compress_Block::Compress_Block(Compress_Block&& other) {
	this->compress_v = std::move(other.compress_v);
    this->min_bit = other.min_bit;
    this->len = other.len;
    this->char_v = std::move(other.char_v);
}

Compress_Block& Compress_Block::operator=(Compress_Block&& other) {
	this->compress_v = std::move(other.compress_v);
    this->min_bit = other.min_bit;
    this->len = other.len;
    this->char_v = std::move(other.char_v);
    return *this;
}


Compress_Block::~Compress_Block() {
	//pass
}
