/*
 * DESblock.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Arash
 */

#ifndef DESBLOCK_H_
#define DESBLOCK_H_

typedef bool bit;

class DESblock {
public:
	static void encrypt_block(bit pcrypted[64], bit block[64],bit subkeys[16][48], bool decrypt = 0);
	static void encrypt_block(bit pcrypt[64], char text[], bit subkeys[16][48], bool decrypt = 0);
	static void create_subkeys(bit subkeys[16][48], bit key[64]);
	static void create_subkeys(bit subkeys[16][48], char key[]);


private:
	static const int PC1[];
	static const int PC2[];
	static const int IP[];
	static const int FP[];
	static const int LEFT_SHIFT[];
	static const int E[];
	static const int SBOX[8][4][16];
	static const int P[];
	static void permute(bit pb[], const bit b[], const int t[], const int size);
	static void shift_left(bit a[],const bit b[], unsigned int n);
	static void connect_bits(bit res[], const bit c[], const bit d[], int size);
	static void add_bits(bit res[], const bit a[], int size, int from = 0);
	static void dec_to_bits(bit bits[4], int d);
	static void feistel(bit pout[], const bit Rn[], const bit Kn[]);
	static int bits_to_dec(bit b[], int size);
	static int pow(const int a, const int n);
	static void create_bits(bit bits[64], const char text[]);
	static int get_dec(char h);

};

#endif /* DESBLOCK_H_ */
