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

class DESblock {
public:
	static void encrypt_block(bit pcrypted[64], bit block[64],bit subkeys[16][48], bool decrypt = 0);
	static void encrypt_block(bit pcrypt[64], char text[], bit subkeys[16][48], bool decrypt = 0);
	static void encrypt_block(char pcrypted[], char text[], bit subkeys[16][48], bool decrypt = 0);
	static void create_subkeys(bit subkeys[16][48], bit key[64]);
	static void create_subkeys(bit subkeys[16][48], char key[]);

	static char get_char(int a);
	static int get_dec(char h);


private:
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
	static void create_bits(bit bits[64], const char text[]);
	static void create_hex(char hex[], const bit bits[64]);

};

#endif /* DESBLOCK_H_ */
