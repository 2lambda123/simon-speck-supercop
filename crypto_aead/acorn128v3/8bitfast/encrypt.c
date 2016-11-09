/*
  This is an optimized implementation of ACORN-128 for 8-bit processors.
  We try to get small code size in this implementation
  At the same time, we try to improve the speed of the cipher
  To improve speed, we mainly try to reduce the shift operations.
  In this program, every 32 steps (32 bits), we shift the registers once.

  In the implementation, we store the 293-bit register into 37 8-bit registers
  293-bit register R:  r292 r291 r290 r289 r288 r287 r286 r285 ...... r5 r4 r3 r2 r1 r0

  state[0]:   r7   r6  ... r2  r1  r0  (lsb: r0)
  state[1]:   r15  r14 ... r10 r9  r8  (lsb: r8)
  state[2]:   r23  r22 ... r18 r17 r16 (lsb: r16)
  ......
  state[36]:  r292 r291 r290 r289 r288 (lsb: r288)
  state[37]:  empty
*/
#include <string.h>
#include <stdio.h>
#include "crypto_aead.h"

#define maj(x,y,z)   ( ((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z))  )
#define ch(x,y,z)    ( ((x) & (y)) ^ ((~x) & (z)) )

// 32 steps of ACORN
// the last input parameter of this function is to indicate whether it is encryption (value1) or decryption (value 0).
void acorn128_32steps(unsigned char *state, unsigned char *plaintextbyte, unsigned char *ciphertextbyte, unsigned char cabyte, unsigned char cbbyte, unsigned char enc_dec_flag)
{
    unsigned int i;
    unsigned char j,f;
    unsigned char byte_12, byte_235, byte_244, byte_23,  byte_160, byte_111, byte_66, byte_196;
    unsigned char byte_230,byte_193, byte_154, byte_107, byte_61;
    unsigned char tem;
    unsigned char *state_tem, ksbyte;

    state_tem = state;

    for (i = 0; i < 4; i++)
    {
        byte_12  = (state_tem[1]  >> 4) | (state_tem[2]  << 4);
        byte_235 = (state_tem[29] >> 3) | (state_tem[30] << 5);
        byte_244 = (state_tem[30] >> 4) | (state_tem[31] << 4);
        byte_23  = (state_tem[2]  >> 7) | (state_tem[3]  << 1);
        byte_160 =  state_tem[20];
        byte_111 = (state_tem[13] >> 7) | (state_tem[14] << 1);
        byte_66  = (state_tem[8]  >> 2) | (state_tem[9]  << 6);
        byte_196 = (state_tem[24] >> 4) | (state_tem[25] << 4);

        byte_230 = (state_tem[28] >> 6) | (state_tem[29] << 2);
        byte_193 = (state_tem[24] >> 1) | (state_tem[25] << 7);
        byte_154 = (state_tem[19] >> 2) | (state_tem[20] << 6);
        byte_107 = (state_tem[13] >> 3) | (state_tem[14] << 5);
        byte_61  = (state_tem[7]  >> 5) | (state_tem[8]  << 3);

        tem = byte_235 ^ byte_230;
        state_tem[36] ^= tem << 1;
        state_tem[37] ^= tem >> 7;

        tem = byte_196 ^ byte_193;
        byte_230 ^= tem;
        state_tem[28] ^= tem << 6;
        state_tem[29] ^= tem >> 2;

        tem = byte_160 ^ byte_154;
        byte_193  ^= tem;
        state_tem[24] ^= tem << 1;
        state_tem[25] ^= tem >> 7;

        tem = byte_111 ^ byte_107;
        byte_154  ^= tem;
        state_tem[19] ^= tem << 2;
        state_tem[20] ^= tem >> 6;

        tem = byte_66 ^ byte_61;
        byte_107  ^= tem;
        state_tem[13] ^= tem << 3;
        state_tem[14] ^= tem >> 5;

        tem = byte_23 ^ state_tem[0];
        byte_61  ^= tem;
        state_tem[7] ^= tem << 5;
        state_tem[8] ^= tem >> 3;

        ksbyte = byte_12 ^ byte_154 ^ maj(byte_235, byte_61, byte_193) ^ ch(byte_230, byte_111, byte_66);

        if (enc_dec_flag == 1) *(ciphertextbyte+i) = *(plaintextbyte+i) ^ ksbyte;
        else                   *(plaintextbyte+i) = *(ciphertextbyte+i) ^ ksbyte;

        f = state_tem[0] ^ (~byte_107) ^ maj(byte_244, byte_23, byte_160) ^ (cabyte & byte_196) ^ (cbbyte & ksbyte);
        f ^= *(plaintextbyte+i);

        state_tem[36] ^= (f << 5);
        state_tem[37] ^= (f >> 3);

        state_tem++;
    }

    //shift by 32-bit positions
    for (j = 0; j <= 36; j++) state[j] = state[j+4];
    state[37] = 0;
    state[38] = 0;
    state[39] = 0;
    state[40] = 0;
}

// 8 steps of ACORN
// the last input parameter of this function is to indicate whether it is encryption (value1) or decryption (value 0).
void acorn128_8steps(unsigned char *state, unsigned char *plaintextbyte, unsigned char *ciphertextbyte, unsigned char cabyte, unsigned char cbbyte, unsigned char enc_dec_flag)
{
    unsigned char j,f;
    unsigned char byte_12, byte_235, byte_244, byte_23,  byte_160, byte_111, byte_66, byte_196;
    unsigned char byte_230,byte_193, byte_154, byte_107, byte_61;
    unsigned char tem, ksbyte;

    byte_12  = (state[1]  >> 4) | (state[2]  << 4);
    byte_235 = (state[29] >> 3) | (state[30] << 5);
    byte_244 = (state[30] >> 4) | (state[31] << 4);
    byte_23  = (state[2]  >> 7) | (state[3]  << 1);
    byte_160 =  state[20];
    byte_111 = (state[13] >> 7) | (state[14] << 1);
    byte_66  = (state[8]  >> 2) | (state[9]  << 6);
    byte_196 = (state[24] >> 4) | (state[25] << 4);

    byte_230 = (state[28] >> 6) | (state[29] << 2);
    byte_193 = (state[24] >> 1) | (state[25] << 7);
    byte_154 = (state[19] >> 2) | (state[20] << 6);
    byte_107 = (state[13] >> 3) | (state[14] << 5);
    byte_61  = (state[7]  >> 5) | (state[8]  << 3);

    tem = byte_235 ^ byte_230;
    state[36] ^= tem << 1;
    state[37] ^= tem >> 7;

    tem = byte_196 ^ byte_193;
    byte_230 ^= tem;
    state[28] ^= tem << 6;
    state[29] ^= tem >> 2;

    tem = byte_160 ^ byte_154;
    byte_193  ^= tem;
    state[24] ^= tem << 1;
    state[25] ^= tem >> 7;

    tem = byte_111 ^ byte_107;
    byte_154  ^= tem;
    state[19] ^= tem << 2;
    state[20] ^= tem >> 6;

    tem = byte_66 ^ byte_61;
    byte_107  ^= tem;
    state[13] ^= tem << 3;
    state[14] ^= tem >> 5;

    tem = byte_23 ^ state[0];
    byte_61  ^= tem;
    state[7] ^= tem << 5;
    state[8] ^= tem >> 3;

    ksbyte = byte_12 ^ byte_154 ^ maj(byte_235, byte_61, byte_193) ^ ch(byte_230, byte_111, byte_66);

    if (enc_dec_flag == 1) *ciphertextbyte = *plaintextbyte ^ ksbyte;
    else                   *plaintextbyte = *ciphertextbyte ^ ksbyte;

    f = state[0] ^ (~byte_107) ^ maj(byte_244, byte_23, byte_160) ^ (cabyte & byte_196) ^ (cbbyte & ksbyte);
    f ^= *plaintextbyte;

    //shift by 8-bit positions
    state[36] ^= (f << 5);
    state[37] ^= (f >> 3);
    for (j = 0; j <= 36; j++) state[j] = state[j+1];
    state[37] = 0;
}

// The initialization state of ACORN
/* The input to initialization is the 128-bit key; 128-bit IV;*/
void acorn128_initialization(const unsigned char *key, const unsigned char *iv, unsigned char *state)
{
    unsigned char j;
    unsigned char ks=0, t;
    unsigned char tem[4] = {0,0,0,0};

    //initialize the state to 0
    for (j = 0; j <= 37+3; j++) state[j] = 0;

    //run the cipher for 1792 steps

    //load the key
    for (j = 0;  j < 16;  j = j+4)
    {
        acorn128_32steps(state, &(key[j]), tem, 0xff, 0xff, 1);
    }

    //load the iv
    for (j = 16;  j < 32;  j = j+4)
    {
        acorn128_32steps(state, &(iv[j-16]), tem, 0xff, 0xff, 1);
    }

    //bit "1" is padded
    for (j = 32;  j < 33; j++)
    {
        t = key[j&0xf] ^ 1;
        acorn128_8steps(state, &t, tem, 0xff, 0xff, 1);
    }

    for (j = 33;  j < 36; j++)
    {
        acorn128_8steps(state, &(key[j&0xf]), tem, 0xff, 0xff, 1);
    }

    for (j = 36;  j < 224; j=j+4)
    {
        acorn128_32steps(state, &(key[j&0xf]), tem, 0xff, 0xff, 1);
    }
}

//the finalization state of acorn
void acorn128_tag_generation(unsigned char maclen, unsigned char *mac, unsigned char *state)
{
    unsigned char i;
    unsigned char plaintextbyte[4]  = {0,0,0,0};
    unsigned char ciphertextbyte[4] = {0,0,0,0};
    unsigned char ksbyte = 0;

    for (i = 0; i < (768-128)/8; i = i+4)
    {
        acorn128_32steps(state, plaintextbyte, ciphertextbyte, 0xff, 0xff,1);
    }

    for (i = 0; i < 128/8; i++)
    {
        acorn128_8steps(state, plaintextbyte, ciphertextbyte, 0xff, 0xff,1);
        mac[i] = *ciphertextbyte;
    }
}

// the 256-step padding
// cb = 0xff for the padding after the associated data;
// cb = 0 for the padding after the plaintext.
void acorn128_fixed_padding_256(unsigned char *state, unsigned char cb)
{
    unsigned char i;
    unsigned char plaintextbyte[4]  = {0,0,0,0};
    unsigned char ciphertextbyte[4] = {0,0,0,0};
    unsigned char ksbyte = 0;
    unsigned char ca;

    plaintextbyte[0] = 0x1;
    ca = 0xff;
    acorn128_8steps(state, plaintextbyte, ciphertextbyte, ca, cb, 1);

    plaintextbyte[0] = 0;
    for (i = 1; i < 4; i++)
    {
        acorn128_8steps(state, plaintextbyte, ciphertextbyte, ca, cb, 1);
    }

    for (i = 4; i < 128/8; i=i+4)
    {
        acorn128_32steps(state, plaintextbyte, ciphertextbyte, ca, cb, 1);
    }

    ca = 0;
    for (i = 0; i < 128/8; i=i+4)
    {
        acorn128_32steps(state, plaintextbyte, ciphertextbyte, ca, cb, 1);
    }
}

// encrypt a message
int crypto_aead_encrypt(
	unsigned char *c,unsigned long long *clen,
	const unsigned char *m,unsigned long long mlen,
	const unsigned char *ad,unsigned long long adlen,
	const unsigned char *nsec,
	const unsigned char *npub,
	const unsigned char *k
	)
{
    unsigned long long i;
    unsigned char mac[16];
    unsigned char ciphertextbyte[4] = {0,0,0,0};
    unsigned char state[38+3];
    unsigned char ca, cb;

    //initialization stage
    acorn128_initialization(k, npub, state);

    //process the associated data
    ca = 0xff;
    cb = 0xff;
    for (i = 0; i < (adlen & 0xfffffffffffffffcULL); i = i+4)
    {
        acorn128_32steps(state, &(ad[i]), ciphertextbyte, ca, cb, 1);
    }

    for (i = adlen & 0xfffffffffffffffcULL; i < adlen; i=i+1)
    {
        acorn128_8steps(state, &(ad[i]), ciphertextbyte, ca, cb, 1);
    }

    acorn128_fixed_padding_256(state, cb);

    //process the plaintext
    ca = 0xff;
    cb = 0;

    for (i = 0; i < (mlen&0xfffffffffffffffcULL); i=i+4)
    {
        acorn128_32steps(state, &(m[i]), &c[i], ca, cb, 1);
    }

    for (i = mlen&0xfffffffffffffffcULL; i < mlen; i=i+1)
    {
        acorn128_8steps(state, &(m[i]), &c[i], ca, cb,1);
    }

    acorn128_fixed_padding_256(state, cb);

    //finalization stage, we assume that the tag length is a multiple of bytes
    acorn128_tag_generation(16, mac, state);
    *clen = mlen + 16;
    memcpy(c+mlen, mac, 16);

    return 0;
}

// encrypt a message
int crypto_aead_decrypt(
	unsigned char *m,unsigned long long *mlen,
	unsigned char *nsec,
	const unsigned char *c,unsigned long long clen,
	const unsigned char *ad,unsigned long long adlen,
	const unsigned char *npub,
	const unsigned char *k
	)
{
    unsigned long long i;
    unsigned char tag[16],check = 0;
    unsigned char ciphertextbyte[4]={0,0,0,0};

    unsigned char state[38+3];
    unsigned char ca, cb;

    //initialization stage
    acorn128_initialization(k, npub, state);

    //process the associated data
    ca = 0xff;
    cb = 0xff;
    for (i = 0; i < (adlen & 0xfffffffffffffffcULL); i = i+4)
    {
        acorn128_32steps(state, &(ad[i]), ciphertextbyte, ca, cb, 1);
    }

    for (i = adlen & 0xfffffffffffffffcULL; i < adlen; i=i+1)
    {
        acorn128_8steps(state, &(ad[i]), ciphertextbyte, ca, cb, 1);
    }

    acorn128_fixed_padding_256(state, cb);

    //process the ciphertext
    ca = 0xff;
    cb = 0;
    *mlen = clen - 16;

    for (i = 0; i < (*mlen & 0xfffffffffffffffcULL); i=i+4)
    {
        acorn128_32steps(state, &(m[i]), &c[i], ca, cb,0);
    }

    for (i = *mlen & 0xfffffffffffffffcULL; i < *mlen; i=i+1)
    {
        acorn128_8steps(state, &(m[i]), &c[i], ca, cb,0);
    }

    acorn128_fixed_padding_256(state, cb);

    //finalization stage, we assume that the tag length is a multiple of bytes
    acorn128_tag_generation(16, tag, state);

    for (i = 0; i  < 16; i++) check |= (tag[i] ^ c[clen - 16 + i]);
    if (check == 0) return 0;
    else return -1;
}
