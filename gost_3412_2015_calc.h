#ifndef GOST_3412_2015_CALC_H
#define GOST_3412_2015_CALC_H

//#include <stdfix.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "gost_3412_2015_const.h"
//#include "test.h"

#define BLOCK_SIZE 16
#define KEY_SIZE 32

//typedef uint8_t vect[BLOCK_SIZE]; //блок размером 128 бит
//uint8_t block[BLOCK_SIZE] = { 0 };

//vect iter_C[32]; //итерационные константы C
uint8_t iter_C[32][BLOCK_SIZE];


//vect iter_key[10]; //итерационные ключи шифрования
uint8_t iter_key[10][BLOCK_SIZE];

void GOST_Kuz_Expand_Key(const uint8_t *key);

void GOST_Kuz_Encrypt(const uint8_t *blk, uint8_t *out_blk);

void GOST_Kuz_Decrypt(const uint8_t *blk, uint8_t *out_blk);

void GOST_Kuz_S(const uint8_t* in_data, uint8_t* out_data);
void GOST_Kuz_reverse_S(const uint8_t* in_data, uint8_t* out_data);
void GOST_Kuz_X(const uint8_t* a, const uint8_t* b, uint8_t* c);
uint8_t GOST_Kuz_GF_mul(uint8_t a, uint8_t b);
void GOST_Kuz_R(uint8_t* state);
void GOST_Kuz_reverse_R(uint8_t* state);
void GOST_Kuz_L(const uint8_t* in_data, uint8_t* out_data);
void GOST_Kuz_reverse_L(const uint8_t* in_data, uint8_t* out_data);
void GOST_Kuz_Get_C();
void GOST_Kuz_F(const uint8_t* in_key_1, const uint8_t* in_key_2,    uint8_t* out_key_1, uint8_t* out_key_2,
    uint8_t* iter_const);


#endif // GOST_3412_2015_CALC_H
