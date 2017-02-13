/*
 * DESblock.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Arash
 */

#ifndef DESBLOCK_H_
#define DESBLOCK_H_

//encrypt block gets an empty array of bits or strings and fills it with encrypted form of given block or text

class DESblock
{
public:

	static void encrypt_block(char crypted[], char block[], char key[], const bool & decrypt = 0);

	static char get_char(const int & a);
	static int get_dec(const char & h);

private:
	class bits;
	static const char _PC1[];
	static const char _PC2[];
	static const char _IP[];
	static const char _FP[];
	static const char _LEFT_SHIFT[];
	static const char _E[];
	static const char _SBOX[8][4][16];
	static const char _P[];
	static int pow(const int & a, const int & n);
	static void create_subkeys(bits subkeys[16], const bits & key);

	static bits create_bits(const char text[], const int & n = 64);
	static void create_hex(char text[], const bits & b);
	static bits feistel(const bits & Rn, const bits & Kn);
	static unsigned int bits_to_dec(const bits & b);
	static bits dec_to_bits(const char & d, const int & n = 4);
	static bits shift_left(bits b, const int & n);
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
		bitsProxy( bits * a, const int & b) : ptr(a) , pos(b) {}
		operator bool() const { return ptr->read(pos); }
		bitsProxy & operator =(const bool & val) {ptr->assign(pos, val); return *this;}
		bitsProxy & operator =(const bitsProxy & b) {ptr->assign(pos, (bool)b); return *this;}
	}; // class bitsProxy

public	:
	bits() : _size(0), _length(0), _list(0) {}
	bits(const int & a, const bool & allTrue = 0);
	bits(const bits & a);
	int size() const {return _size;}
	int length() const {return _length;}
	void assign(const int & pos, const bool & val);
	bool read(const int & digit) const;
	~bits();
	bits & operator =(const bits & rhs);
	const bool operator [](const int & digit) const {return this->read(digit);}
	bitsProxy operator [](const int & digit) {return bitsProxy(this, digit);}
	void append(const bool & b);
	unsigned char list(const int & i) const { return *_list[i]; }
	void listAssign(const int & i, const unsigned char & c) { if (i < _size) *_list[i] = c; }
}; //class bits


#endif /* DESBLOCK_H_ */
