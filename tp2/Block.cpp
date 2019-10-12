#include <iostream>
#include <bits/stdc++.h> 
#include <algorithm>
#include <vector>
#include <cmath>
#include <arpa/inet.h>
#include <string>
#include <fstream>
#include "Compress_Block.h"
#include "Block.h"

#define MAX_1B 1

uint8_t Block::min_binary(uint32_t max_number) {
	if (max_number == 0) {
		return 0;
	} else if (max_number == MAX_1B) {
		return 1;
	} else {
		return (uint8_t)log2(max_number) + 1;
	}
}

void Block::set_compress_block() {
	min_value = *std::min_element(block.begin(), block.end());
	for(uint32_t n = 0; n < block.size(); n++) {
		block[n] -= min_value;
	}
	uint32_t max_value = *std::max_element(block.begin(), block.end());
	min_bits = min_binary(max_value);
	compress_block.set_min_bits(min_bits);
}

Block::Block(uint32_t max) {
	max_size = max;
}

void Block::add(uint32_t number) {
	block.push_back(number);
}

bool Block::is_full() {
	return block.size() >= max_size;
}

uint32_t Block::get_size() {
	return block.size();
}

void Block::complete_block() {
	if (!is_full()) {
		while (block.size() < max_size)
			add(block.back());
	}
}

void Block::compress() {
	complete_block();
	set_compress_block();

	std::vector<char> char_c;
	uint32_t v = htonl(min_value);
	char* chars = reinterpret_cast<char*>(&v);
    char_c.insert(char_c.end(), chars, chars + sizeof(uint32_t));

    char_c.insert(char_c.end(), (char)min_bits);

	std::vector<char> comp = std::move(compress_block.compress(&block));
	char_c.insert(char_c.end(), comp.begin(), comp.end());
	char_compress = std::move(char_c);
}

std::vector<char> Block::get_compress() {
	return std::move(char_compress);
}

Block::Block(Block&& other) {
    this->block = std::move(other.block);
    this->max_size = other.max_size;
    this->min_value = other.min_value;
    this->min_bits = other.min_bits;
    this->compress_block = std::move(other.compress_block);
    this->char_compress = std::move(other.char_compress);
}

Block& Block::operator=(Block&& other) {
	this->block = std::move(other.block);
    this->max_size = other.max_size;
    this->min_value = other.min_value;
    this->min_bits = other.min_bits;
    this->compress_block = std::move(other.compress_block);
    this->char_compress = std::move(other.char_compress);
    return *this;
}

void Block::print_block() {
	for (uint32_t x: block)
		std::cout << x;
}

Block::~Block() {}
