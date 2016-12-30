/*
 * DESblock.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Arash
 */

#ifndef DESBLOCK_H_
#define DESBLOCK_H_

//encrypt block gets an empty array of bits or strings (pcrypt) and fills it with encrypted form of given block or text




typedef bool bit;

class DESblock
{
public:


	static void encrypt_block(bit pcrypted[64], bit block[64],bit subkeys[16][48], bool decrypt = 0);
	static void encrypt_block(bit pcrypt[64], char text[], bit subkeys[16][48], bool decrypt = 0);
	static void encrypt_block(char pcrypted[], char text[], bit subkeys[16][48], bool decrypt = 0);

	static void create_subkeys(bit subkeys[16][48], bit key[64]);
	static void create_subkeys(bit subkeys[16][48], char key[]);

	static void encrypt_block(char crypted[], char block[], char key[], bool decrypt = 0);

	static char get_char(const int & a);
	static int get_dec(const char & h);

private:
	class bits;
	static const char PC1[];
	static const char PC2[];
	static const char IP[];
	static const char FP[];
	static const char LEFT_SHIFT[];
	static const char E[];
	static const int SBOX[8][4][16];
	static const char P[];
	static void permute(bit pb[], const bit b[], const char t[], const int size);
	static void shift_left(bit a[],const bit b[], unsigned int n);
	static void connect_bits(bit res[], const bit c[], const bit d[], int size);
	static void add_bits(bit res[], const bit a[], int size, int from = 0);
	static void dec_to_bits(bit bits[4], int d);
	static void feistel(bit pout[], const bit Rn[], const bit Kn[]);
	static int bits_to_dec(bit b[], int size);
	static int pow(const int a, const int n);
	static void create_hex(char hex[], const bit bits[64]);
	static void create_bits(bit bits[64], const char text[]);
	static void create_subkeys(bits subkeys[16], const bits & key);

	static bits create_bits(const char text[], const int & n = 64);
	static void create_hex(char text[], const bits & b);
	static bits feistel(const bits & Rn, const bits & Kn);
	static unsigned int bits_to_dec(const bits & b);
	static bits dec_to_bits(unsigned int d, const int n = 4);
	static bits shift_left(bits b, const int n);
	static bits permute(const bits & b,const char t[], const int & size);
};

class DESblock::bits
{
	int _size;
	int _length;
	unsigned char ** _list;

	class bitsProxy
	{
		bits * ptr;
		int pos;
	public:
		bitsProxy( bits * a, int b) : ptr(a) , pos(b) {}
		operator bool() const { return ptr->read(pos); }
		bitsProxy & operator =(const bool val) {ptr->assign(pos, val); return *this;}
		bitsProxy & operator =(const bitsProxy & b) {ptr->assign(pos, (bool)b); return *this;}
	}; // class bitsProxy

public	:
	bits() : _size(0), _length(0), _list(0) {}
	bits(const int a, const bool allTrue = 0);
	bits(const bits & a);
	int size() const {return _size;}
	int length() const {return _length;}
	void assign(const int pos, const bool val);
	bool read(const int digit) const;
	~bits();
	bits & operator =(const bits & rhs);
	const bool operator [](const int digit) const {return this->read(digit);}
	bitsProxy operator [](const int digit) {return bitsProxy(this, digit);}
	void append(const bool b);
	unsigned char list(const int i) const { return *_list[i]; }
	void listAssign(const int i, const unsigned char c) const { if (i < _size) *_list[i] = c; }
}; //class bits


#endif /* DESBLOCK_H_ */
