//
// Created by vasily on 07.06.23.
//

#ifndef SIGNATURE_AND_CIPHER_GOST_3410_2012_H
#define SIGNATURE_AND_CIPHER_GOST_3410_2012_H

#endif //SIGNATURE_AND_CIPHER_GOST_3410_2012_H

#include <iostream>
//#include <sstream>
#include <vector>
#include <iomanip>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/bn.h>

extern "C"{
#include "gost_3411_2012_calc.h"
//#include "gost_3411_2012_test.h"
};
//using namespace boost::multiprecision;

//curves get from R_1323565.1.024—2019
struct id_tc26_gost_3410_2012_256_paramSetB
{
    unsigned char a_bin[33] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
             0x94};
    unsigned char b_bin[1] =
            {0xa6};
    unsigned char p_bin[33] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
             0x97};
    unsigned char m_bin[33] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0x6c, 0x61, 0x10, 0x70, 0x99, 0x5a, 0xd1,
             0x00, 0x45, 0x84, 0x1b, 0x09, 0xb7, 0x61, 0xb8,
             0x93 };
    unsigned char q_bin[33] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0x6c, 0x61, 0x10, 0x70, 0x99, 0x5a, 0xd1,
             0x00, 0x45, 0x84, 0x1b, 0x09, 0xb7, 0x61, 0xb8,
             0x93 };
    unsigned char x_bin[1] = {0x01};
    unsigned char y_bin[33] ={0x00, 0x8d, 0x91, 0xe4, 0x71, 0xe0, 0x98, 0x9c,
                              0xda, 0x27, 0xdf, 0x50, 0x5a, 0x45, 0x3f, 0x2b,
                              0x76, 0x35, 0x29, 0x4f, 0x2d, 0xdf, 0x23, 0xe3,
                              0xb1, 0x22, 0xac, 0xc9, 0x9c, 0x9e, 0x9f, 0x1e,
                              0x14};
};

struct id_tc26_gost_3410_2012_256_paramSetC
{
    unsigned char a_bin[33] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
             0x96};
    unsigned char b_bin[32] =
            {0x3e, 0x1a, 0xf4, 0x19, 0xa2, 0x69, 0xa5, 0xf8,
             0x66, 0xa7, 0xd3, 0xc2, 0x5c, 0x3d, 0xf8, 0x0a,
             0xe9, 0x79, 0x25, 0x93, 0x73, 0xff, 0x2b, 0x18,
             0x2f, 0x49, 0xd4, 0xce, 0x7e, 0x1b, 0xbc, 0x8b};
    unsigned char p_bin[33] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
             0x99};
    unsigned char m_bin[33] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x01, 0x5f, 0x70, 0x0c, 0xff, 0xf1, 0xa6, 0x24,
             0xe5, 0xe4, 0x97, 0x16, 0x1b, 0xcc, 0x8a, 0x19,
             0x8f };
    unsigned char q_bin[33] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x01, 0x5f, 0x70, 0x0c, 0xff, 0xf1, 0xa6, 0x24,
             0xe5, 0xe4, 0x97, 0x16, 0x1b, 0xcc, 0x8a, 0x19,
             0x8f };
    unsigned char x_bin[1] = {0x01};
    unsigned char y_bin[32] ={0x3f, 0xa8, 0x12, 0x43, 0x59, 0xf9, 0x66, 0x80,
                              0xb8, 0x3d, 0x1c, 0x3e, 0xb2, 0xc0, 0x70, 0xe5,
                              0xc5, 0x45, 0xc9, 0x85, 0x8d, 0x03, 0xec, 0xfb,
                              0x74, 0x4b, 0xf8, 0xd7, 0x17, 0x71, 0x7e, 0xfc};
};

struct id_tc26_gost_3410_2012_256_paramSetD
{
    unsigned char a_bin[33] =
            {0x00, 0x9b, 0x9f, 0x60, 0x5f, 0x5a, 0x85, 0x81,
             0x07, 0xab, 0x1e, 0xc8, 0x5e, 0x6b, 0x41, 0xc8,
             0xaa, 0xcf, 0x84, 0x6e, 0x86, 0x78, 0x90, 0x51,
             0xd3, 0x79, 0x98, 0xf7, 0xb9, 0x02, 0x2d, 0x75,
             0x98};
    unsigned char b_bin[2] =
            {0x80, 0x5a};
    unsigned char p_bin[33] =
            {0x00, 0x9b, 0x9f, 0x60, 0x5f, 0x5a, 0x85, 0x81,
             0x07, 0xab, 0x1e, 0xc8, 0x5e, 0x6b, 0x41, 0xc8,
             0xaa, 0xcf, 0x84, 0x6e, 0x86, 0x78, 0x90, 0x51,
             0xd3, 0x79, 0x98, 0xf7, 0xb9, 0x02, 0x2d, 0x75,
             0x9b};
    unsigned char m_bin[33] =
            {0x00, 0x9b, 0x9f, 0x60, 0x5f, 0x5a, 0x85, 0x81,
             0x07, 0xab, 0x1e, 0xc8, 0x5e, 0x6b, 0x41, 0xc8,
             0xaa, 0x58, 0x2c, 0xa3, 0x51, 0x1e, 0xdd, 0xfb,
             0x74, 0xf0, 0x2f, 0x3a, 0x65, 0x98, 0x98, 0x0b,
             0xb9 };
    unsigned char q_bin[33] =
            {0x00, 0x9b, 0x9f, 0x60, 0x5f, 0x5a, 0x85, 0x81,
             0x07, 0xab, 0x1e, 0xc8, 0x5e, 0x6b, 0x41, 0xc8,
             0xaa, 0x58, 0x2c, 0xa3, 0x51, 0x1e, 0xdd, 0xfb,
             0x74, 0xf0, 0x2f, 0x3a, 0x65, 0x98, 0x98, 0x0b,
             0xb9 };
    unsigned char x_bin[1] = {0x00};
    unsigned char y_bin[32] ={0x41, 0xec, 0xe5, 0x57, 0x43, 0x71, 0x1a, 0x8c,
                              0x3c, 0xbf, 0x37, 0x83, 0xcd, 0x08, 0xc0, 0xee,
                              0x4d, 0x4d, 0xc4, 0x40, 0xd4, 0x64, 0x1a, 0x8f,
                              0x36, 0x6e, 0x55, 0x0d, 0xfd, 0xb3, 0xbb, 0x67};
};

struct id_tc26_gost_3410_2012_512_paramSetA
{
    unsigned char a_bin[65] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
             0xc4};
    unsigned char b_bin[65] =
            {0x00, 0xe8, 0xc2, 0x50, 0x5d, 0xed, 0xfc, 0x86,
             0xdd, 0xc1, 0xbd, 0x0b, 0x2b, 0x66, 0x67, 0xf1,
             0xda, 0x34, 0xb8, 0x25, 0x74, 0x76, 0x1c, 0xb0,
             0xe8, 0x79, 0xbd, 0x08, 0x1c, 0xfd, 0x0b, 0x62,
             0x65, 0xee, 0x3c, 0xb0, 0x90, 0xf3, 0x0d, 0x27,
             0x61, 0x4c, 0xb4, 0x57, 0x40, 0x10, 0xda, 0x90,
             0xdd, 0x86, 0x2e, 0xf9, 0xd4, 0xeb, 0xee, 0x47,
             0x61, 0x50, 0x31, 0x90, 0x78, 0x5a, 0x71, 0xc7,
             0x60};
    unsigned char p_bin[65] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd,
             0xc7};
    unsigned char m_bin[65] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0x27, 0xe6, 0x95, 0x32, 0xf4, 0x8d, 0x89,
             0x11, 0x6f, 0xf2, 0x2b, 0x8d, 0x4e, 0x05, 0x60,
             0x60, 0x9b, 0x4b, 0x38, 0xab, 0xfa, 0xd2, 0xb8,
             0x5d, 0xca, 0xcd, 0xb1, 0x41, 0x1f, 0x10, 0xb2,
             0x75 };
    unsigned char q_bin[65] =
            {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
             0xff, 0x27, 0xe6, 0x95, 0x32, 0xf4, 0x8d, 0x89,
             0x11, 0x6f, 0xf2, 0x2b, 0x8d, 0x4e, 0x05, 0x60,
             0x60, 0x9b, 0x4b, 0x38, 0xab, 0xfa, 0xd2, 0xb8,
             0x5d, 0xca, 0xcd, 0xb1, 0x41, 0x1f, 0x10, 0xb2,
             0x75 };
    unsigned char x_bin[1] = {0x03};
    unsigned char y_bin[64] ={0x75, 0x03, 0xcf, 0xe8, 0x7a, 0x83, 0x6a, 0xe3,
                              0xa6, 0x1b, 0x88, 0x16, 0xe2, 0x54, 0x50, 0xe6,
                              0xce, 0x5e, 0x1c, 0x93, 0xac, 0xf1, 0xab, 0xc1,
                              0x77, 0x80, 0x64, 0xfd, 0xcb, 0xef, 0xa9, 0x21,
                              0xdf, 0x16, 0x26, 0xbe, 0x4f, 0xd0, 0x36, 0xe9,
                              0x3d, 0x75, 0xe6, 0xa5, 0x0e, 0x3a, 0x41, 0xe9,
                              0x80, 0x28, 0xfe, 0x5f, 0xc2, 0x35, 0xf5, 0xb8,
                              0x89, 0xa5, 0x89, 0xcb, 0x52, 0x15, 0xf2, 0xa4};
};

struct id_tc26_gost_3410_2012_512_paramSetB
{
    unsigned char a_bin[65] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x6c};
    unsigned char b_bin[64] =
            {0x68, 0x7d, 0x1b, 0x45, 0x9d, 0xc8, 0x41, 0x45,
             0x7e, 0x3e, 0x06, 0xcf, 0x6f, 0x5e, 0x25, 0x17,
             0xb9, 0x7c, 0x7d, 0x61, 0x4a, 0xf1, 0x38, 0xbc,
             0xbf, 0x85, 0xdc, 0x80, 0x6c, 0x4b, 0x28, 0x9f,
             0x3e, 0x96, 0x5d, 0x2d, 0xb1, 0x41, 0x6d, 0x21,
             0x7f, 0x8b, 0x27, 0x6f, 0xad, 0x1a, 0xb6, 0x9c,
             0x50, 0xf7, 0x8b, 0xee, 0x1f, 0xa3, 0x10, 0x6e,
             0xfb, 0x8c, 0xcb, 0xc7, 0xc5, 0x14, 0x01, 0x16};
    unsigned char p_bin[65] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x6f};
    unsigned char m_bin[65] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x01, 0x49, 0xa1, 0xec, 0x14, 0x25, 0x65, 0xa5,
             0x45, 0xac, 0xfd, 0xb7, 0x7b, 0xd9, 0xd4, 0x0c,
             0xfa, 0x8b, 0x99, 0x67, 0x12, 0x10, 0x1b, 0xea,
             0x0e, 0xc6, 0x34, 0x6c, 0x54, 0x37, 0x4f, 0x25,
             0xbd };
    unsigned char q_bin[65] =
            {0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
             0x01, 0x49, 0xa1, 0xec, 0x14, 0x25, 0x65, 0xa5,
             0x45, 0xac, 0xfd, 0xb7, 0x7b, 0xd9, 0xd4, 0x0c,
             0xfa, 0x8b, 0x99, 0x67, 0x12, 0x10, 0x1b, 0xea,
             0x0e, 0xc6, 0x34, 0x6c, 0x54, 0x37, 0x4f, 0x25,
             0xbd };
    unsigned char x_bin[1] = {0x02};
    unsigned char y_bin[64] ={0x1a, 0x8f, 0x7e, 0xda, 0x38, 0x9b, 0x09, 0x4c,
                              0x2c, 0x07, 0x1e, 0x36, 0x47, 0xa8, 0x94, 0x0f,
                              0x3c, 0x12, 0x3b, 0x69, 0x75, 0x78, 0xc2, 0x13,
                              0xbe, 0x6d, 0xd9, 0xe6, 0xc8, 0xec, 0x73, 0x35,
                              0xdc, 0xb2, 0x28, 0xfd, 0x1e, 0xdf, 0x4a, 0x39,
                              0x15, 0x2c, 0xbc, 0xaa, 0xf8, 0xc0, 0x39, 0x88,
                              0x28, 0x04, 0x10, 0x55, 0xf9, 0x4c, 0xee, 0xec,
                              0x7e, 0x21, 0x34, 0x07, 0x80, 0xfe, 0x41, 0xbd};
};



//std::string uint8_to_hex_string(const uint8_t *v, size_t start, size_t end);
//void handleErrors();
//std::string sign(EC_GROUP *curve, EC_KEY *key, std::vector<uint8_t> data);
//char* get_private_key(EC_KEY *key);
//std::string get_public_key(EC_GROUP *curve, EC_KEY *key);
//EC_KEY* generate_keys(EC_GROUP *curve);
//template<typename T>
//EC_GROUP *creat_curve(T paramSet);

class Signature
{
    EC_GROUP *curve;
    EC_KEY *key = EC_KEY_new();
    std::string uint8_to_hex_string(const uint8_t *v, size_t start, size_t end);
    void handleErrors();
public:
    std::string sign(/*EC_GROUP *curve, EC_KEY *key,*/ std::vector<uint8_t> data);
    std::string get_private_key(/*EC_KEY *key*/);
    std::string get_public_key(/*EC_GROUP *curve, EC_KEY *key*/);
    std::string get_public_key_from_key(const std::string& loginkey);
    EC_KEY* generate_keys(/*EC_GROUP *name_curve*/);
    void free_group_and_key();
    int set_group();
    int set_private_key(const std::string& loginkey);

    template<typename T>
    EC_GROUP *creat_curve(T paramSet);
};

template<typename T>
EC_GROUP* Signature::creat_curve(T paramSet) {
    BN_CTX *ctx;
    //EC_GROUP *curve;
    /*curve parameters*/
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *p = BN_new();
    BIGNUM *m = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    //BIGNUM *d = BN_new();
    EC_POINT *generator;
    /* Set up the BN_CTX */
    if (nullptr == (ctx = BN_CTX_new())) handleErrors();
    /* Set the values for the various parameters */
    if (nullptr == (a = BN_bin2bn(paramSet.a_bin, sizeof(paramSet.a_bin), nullptr))) handleErrors();
    if (nullptr == (b = BN_bin2bn(paramSet.b_bin, sizeof(paramSet.b_bin), nullptr))) handleErrors();
    if (nullptr == (p = BN_bin2bn(paramSet.p_bin, sizeof(paramSet.p_bin), nullptr))) handleErrors();
    if (nullptr == (m = BN_bin2bn(paramSet.m_bin, sizeof(paramSet.m_bin), nullptr))) handleErrors();
    if (nullptr == (q = BN_bin2bn(paramSet.q_bin, sizeof(paramSet.m_bin), nullptr))) handleErrors();
    if (nullptr == (x = BN_bin2bn(paramSet.x_bin, sizeof(paramSet.x_bin), nullptr))) handleErrors();
    if (nullptr == (y = BN_bin2bn(paramSet.y_bin, sizeof(paramSet.y_bin), nullptr))) handleErrors();
    //std::cout<<"q_hex="<<BN_bn2hex(q)<<std::endl;
    /* Create the curve */
    if (nullptr == (curve = EC_GROUP_new_curve_GFp(p, a, b, ctx))) handleErrors();
    //std::cout << BN_bn2dec(a) << std::endl;
    //EC_POINT_set_affine_coordinates(curve,p,x,y,ctx);
    /* Create the generator */
    if (nullptr == (generator = EC_POINT_new(curve))) handleErrors();
    if (1 != EC_POINT_set_affine_coordinates(curve, generator, x, y, ctx))
        handleErrors();
    if (1 != EC_GROUP_set_generator(curve, generator, m, q))
        handleErrors();
    BN_free(y);
    BN_free(x);
    BN_free(m);
    BN_free(q);
    BN_free(p);
    BN_free(b);
    BN_free(a);
    BN_CTX_free(ctx);
    return curve;
}



