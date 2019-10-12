#ifndef BLOCK_H
#define BLOCK_H

#include "Compress_Block.h"
#include <vector>

class Block {
private:
	std::vector<uint32_t> block;
	uint32_t max_size;
	uint32_t min_value;
	uint8_t min_bits;
	Compress_Block compress_block;
	std::vector<char> char_compress;

	uint8_t min_binary(uint32_t max_number);
	
	void set_compress_block();

	void complete_block();
	
public:
	explicit Block(uint32_t max);
	
	void add(uint32_t number);
	
	bool is_full();
	
	uint32_t get_size();
	
	void compress();
	
	std::vector<char> get_compress();

	//Block(const Block&) = delete;

	//Block& operator=(const Block&) = delete;

	Block(Block&& other);

	Block& operator=(Block&& other);

	void print_block();

	~Block();
};

#endif
