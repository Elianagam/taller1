#ifndef COMPRESS_BLOCK_H
#define COMPRESS_BLOCK_H

#include <vector>

class Compress_Block {
private:
	std::vector<bool> compress_v;
	uint8_t min_bit;
	uint32_t len;
	std::vector<char> char_v;

	void align();	

	void convert_to_binary(uint32_t num);
	
	void save_number(std::vector<bool> &number);

	void to_byte();

public:
	Compress_Block();
	
	void set_min_bits(uint8_t num);

	std::vector<char> compress(std::vector<uint32_t> *block); 

	Compress_Block(Compress_Block&& other);

	Compress_Block& operator=(Compress_Block&& other);

	~Compress_Block();
};

#endif
