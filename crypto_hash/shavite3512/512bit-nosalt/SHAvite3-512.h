#include "portable.h"
#include "AESround.h"
#include "SHA3api_ref.h"
 
#define InternalRounds512 4
#define ExternalRounds512 14
#define ExpandedMessageSize512 (ExternalRounds512*4*(InternalRounds512)*2)

#define NonLinExpansionRegular(rk,position,x0,x1,x2,x3,y0,y1,y2,y3)\
{\
        x0 = rk[position-31];\
        x1 = rk[position-30];\
        x2 = rk[position-29];\
        x3 = rk[position-32];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[position]   = y0^rk[position-4];\
        rk[position+1] = y1^rk[position-3];\
        rk[position+2] = y2^rk[position-2];\
        rk[position+3] = y3^rk[position-1];\
	x0 = rk[position-27];\
        x1 = rk[position-26];\
        x2 = rk[position-25];\
        x3 = rk[position-28];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[position+4] = y0^rk[position];\
        rk[position+5] = y1^rk[position+1];\
        rk[position+6] = y2^rk[position+2];\
        rk[position+7] = y3^rk[position+3];\
        x0 = rk[position-23];\
        x1 = rk[position-22];\
        x2 = rk[position-21];\
        x3 = rk[position-24];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[position+8]  = y0^rk[position+4];\
        rk[position+9]  = y1^rk[position+5];\
        rk[position+10] = y2^rk[position+6];\
        rk[position+11] = y3^rk[position+7];\
        x0 = rk[position-19];\
        x1 = rk[position-18];\
        x2 = rk[position-17];\
        x3 = rk[position-20];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[position+12] = y0^rk[position+8];\
        rk[position+13] = y1^rk[position+9];\
        rk[position+14] = y2^rk[position+10];\
        rk[position+15] = y3^rk[position+11];\
}


#define NonLinExpansion32(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3)\
{\
        x0 = rk[1];\
        x1 = rk[2];\
        x2 = rk[3];\
        x3 = rk[0];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[32] = y0^rk[28]^counter[0];\
        rk[33] = y1^rk[29]^counter[1];\
        rk[34] = y2^rk[30]^counter[2];\
        rk[35] = y3^rk[31]^counter[3];\
	x0 = rk[5];\
        x1 = rk[6];\
        x2 = rk[7];\
        x3 = rk[4];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[36] = y0^rk[32];\
        rk[37] = y1^rk[33];\
        rk[38] = y2^rk[34];\
        rk[39] = y3^rk[35];\
        x0 = rk[9];\
        x1 = rk[10];\
        x2 = rk[11];\
        x3 = rk[8];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[40] = y0^rk[36];\
        rk[41] = y1^rk[37];\
        rk[42] = y2^rk[38];\
        rk[43] = y3^rk[39];\
        x0 = rk[13];\
        x1 = rk[14];\
        x2 = rk[15];\
        x3 = rk[12];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[44] = y0^rk[40];\
        rk[45] = y1^rk[41];\
        rk[46] = y2^rk[42];\
        rk[47] = y3^rk[43];\
}


#define NonLinExpansion160(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3)\
{\
        x0 = rk[129];\
        x1 = rk[130];\
        x2 = rk[131];\
        x3 = rk[128];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[160] = y0^rk[156];\
        rk[161] = y1^rk[157];\
        rk[162] = y2^rk[158];\
        rk[163] = y3^rk[159];\
	x0 = rk[133];\
        x1 = rk[134];\
        x2 = rk[135];\
        x3 = rk[132];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[164] = y0^rk[160]^counter[3];\
        rk[165] = y1^rk[161]^counter[2];\
        rk[166] = y2^rk[162]^counter[1];\
        rk[167] = y3^rk[163]^counter[0];\
        x0 = rk[137];\
        x1 = rk[138];\
        x2 = rk[139];\
        x3 = rk[136];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[168] = y0^rk[164];\
        rk[169] = y1^rk[165];\
        rk[170] = y2^rk[166];\
        rk[171] = y3^rk[167];\
        x0 = rk[141];\
        x1 = rk[142];\
        x2 = rk[143];\
        x3 = rk[140];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[172] = y0^rk[168];\
        rk[173] = y1^rk[169];\
        rk[174] = y2^rk[170];\
        rk[175] = y3^rk[171];\
}

#define NonLinExpansion304(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3)\
{\
        x0 = rk[273];\
        x1 = rk[274];\
        x2 = rk[275];\
        x3 = rk[272];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[304] = y0^rk[300];\
        rk[305] = y1^rk[301];\
        rk[306] = y2^rk[302];\
        rk[307] = y3^rk[303];\
	x0 = rk[277];\
        x1 = rk[278];\
        x2 = rk[279];\
        x3 = rk[276];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[308] = y0^rk[304];\
        rk[309] = y1^rk[305];\
        rk[310] = y2^rk[306];\
        rk[311] = y3^rk[307];\
        x0 = rk[281];\
        x1 = rk[282];\
        x2 = rk[283];\
        x3 = rk[280];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[312] = y0^rk[308];\
        rk[313] = y1^rk[309];\
        rk[314] = y2^rk[310];\
        rk[315] = y3^rk[311];\
        x0 = rk[285];\
        x1 = rk[286];\
        x2 = rk[287];\
        x3 = rk[284];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[316] = y0^rk[312]^counter[2];\
        rk[317] = y1^rk[313]^counter[3];\
        rk[318] = y2^rk[314]^counter[0];\
        rk[319] = y3^rk[315]^counter[1];\
}

#define NonLinExpansion432(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3)\
{\
        x0 = rk[401];\
        x1 = rk[402];\
        x2 = rk[403];\
        x3 = rk[400];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[432] = y0^rk[428];\
        rk[433] = y1^rk[429];\
        rk[434] = y2^rk[430];\
        rk[435] = y3^rk[431];\
	x0 = rk[405];\
        x1 = rk[406];\
        x2 = rk[407];\
        x3 = rk[404];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[436] = y0^rk[432];\
        rk[437] = y1^rk[433];\
        rk[438] = y2^rk[434];\
        rk[439] = y3^rk[435];\
        x0 = rk[409];\
        x1 = rk[410];\
        x2 = rk[411];\
        x3 = rk[408];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[440] = y0^rk[436]^counter[1];\
        rk[441] = y1^rk[437]^counter[0];\
        rk[442] = y2^rk[438]^counter[3];\
        rk[443] = y3^rk[439]^counter[2];\
        x0 = rk[413];\
        x1 = rk[414];\
        x2 = rk[415];\
        x3 = rk[412];\
        roundAESnokey(x0,x1,x2,x3,y0,y1,y2,y3);\
        rk[444] = y0^rk[440];\
        rk[445] = y1^rk[441];\
        rk[446] = y2^rk[442];\
        rk[447] = y3^rk[443];\
}

#define LinExpansion512(rk,position,temp0,temp1,temp2)\
{\
   temp0=position; temp1=position-32; temp2=position-7;\
   for (;temp1<position;temp0++,temp1++,temp2++)\
     rk[temp0] = rk[temp1]^rk[temp2];\
}


#define oneround(state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,x0,x1,x2,x3,y0,y1,y2,y3,rk,position)\
{\
   x0 = state4^rk[position];\
   x1 = state5^rk[position+1];\
   x2 = state6^rk[position+2];\
   x3 = state7^rk[position+3];\
   roundAES(x0,x1,x2,x3,y0,y1,y2,y3,rk[position+4],rk[position+5],rk[position+6],rk[position+7]);\
   roundAES(y0,y1,y2,y3,x0,x1,x2,x3,rk[position+8],rk[position+9],rk[position+10],rk[position+11]);\
   roundAES(x0,x1,x2,x3,y0,y1,y2,y3,rk[position+12],rk[position+13],rk[position+14],rk[position+15]);\
   roundAESnokey(y0,y1,y2,y3,x0,x1,x2,x3);\
   state0^=x0;\
   state1^=x1;\
   state2^=x2;\
   state3^=x3;\
   x0 = state12^rk[position+16];\
   x1 = state13^rk[position+17];\
   x2 = state14^rk[position+18];\
   x3 = state15^rk[position+19];\
   roundAES(x0,x1,x2,x3,y0,y1,y2,y3,rk[position+20],rk[position+21],rk[position+22],rk[position+23]);\
   roundAES(y0,y1,y2,y3,x0,x1,x2,x3,rk[position+24],rk[position+25],rk[position+26],rk[position+27]);\
   roundAES(x0,x1,x2,x3,y0,y1,y2,y3,rk[position+28],rk[position+29],rk[position+30],rk[position+31]);\
roundAESnokey(y0,y1,y2,y3,x0,x1,x2,x3);\
   state8^=x0;\
   state9^=x1;\
   state10^=x2;\
   state11^=x3;\
}

void E512(u32 pt[16], u32 ct[16], u32 message[32], u32 counter[4])
{
   u32 state0,state1,state,2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15;
   u32 x0,x1,x2,x3,y0,y1,y2,y3,i,j,k;
   u32 rk[ExpandedMessageSize512];

   state0=pt[0]; 
   state1=pt[1]; 
   state2=pt[2]; 
   state3=pt[3];
   state4=pt[4];
   state5=pt[5];
   state6=pt[6];
   state7=pt[7];
   state8=pt[8]; 
   state9=pt[9]; 
   state10=pt[10]; 
   state11=pt[11];
   state12=pt[12];
   state13=pt[13];
   state14=pt[14];
   state15=pt[15];
   
   for (i=0;i<32;i++) rk[i]=message[i];
   oneround(state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,x0,x1,x2,x3,y0,y1,y2,y3,rk,0);
   NonLinExpansion32(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansionRegular(rk,48,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,x0,x1,x2,x3,y0,y1,y2,y3,rk,32);
   LinExpansion512(rk,64,i,j,k);
   oneround(state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,state4,state5,state6,state7,x0,x1,x2,x3,y0,y1,y2,y3,rk,64);
   NonLinExpansionRegular(rk,96,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansionRegular(rk,112,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state12,state13,state14,state15,state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,x0,x1,x2,x3,y0,y1,y2,y3,rk,96);
   LinExpansion512(rk,128,i,j,k);
   oneround(state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,x0,x1,x2,x3,y0,y1,y2,y3,rk,128);
   NonLinExpansion160(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansionRegular(rk,176,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,x0,x1,x2,x3,y0,y1,y2,y3,rk,160);

   LinExpansion512(rk,192,i,j,k);
   oneround(state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,state4,state5,state6,state7,x0,x1,x2,x3,y0,y1,y2,y3,rk,192);
   NonLinExpansionRegular(rk,224,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansionRegular(rk,240,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state12,state13,state14,state15,state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,x0,x1,x2,x3,y0,y1,y2,y3,rk,224);
   LinExpansion512(rk,256,i,j,k);
   oneround(state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,x0,x1,x2,x3,y0,y1,y2,y3,rk,256);
   NonLinExpansionRegular(rk,288,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansion304(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,x0,x1,x2,x3,y0,y1,y2,y3,rk,288);

   LinExpansion512(rk,320,i,j,k);
   oneround(state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,state4,state5,state6,state7,x0,x1,x2,x3,y0,y1,y2,y3,rk,320);
   NonLinExpansionRegular(rk,352,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansionRegular(rk,368,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state12,state13,state14,state15,state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,x0,x1,x2,x3,y0,y1,y2,y3,rk,352);
   LinExpansion512(rk,384,i,j,k);
   oneround(state0,state1,state2,state3,state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,x0,x1,x2,x3,y0,y1,y2,y3,rk,384);
   NonLinExpansionRegular(rk,416,x0,x1,x2,x3,y0,y1,y2,y3);
   NonLinExpansion432(rk,counter,x0,x1,x2,x3,y0,y1,y2,y3);
   oneround(state4,state5,state6,state7,state8,state9,state10,state11,state12,state13,state14,state15,state0,state1,state2,state3,x0,x1,x2,x3,y0,y1,y2,y3,rk,416);

   ct[0]=state8; 
   ct[1]=state9; 
   ct[2]=state10; 
   ct[3]=state11;
   ct[4]=state12;
   ct[5]=state13;
   ct[6]=state14;
   ct[7]=state15;
   ct[8]=state0; 
   ct[9]=state1; 
   ct[10]=state2; 
   ct[11]=state3;
   ct[12]=state4;
   ct[13]=state5;
   ct[14]=state6;
   ct[15]=state7;

   return;
}

/* The actual compression function C_{512}                           */

void Compress512(const u8 *message_block, u8 *chaining_value, u64 counter)
{    
   u32 pt[16],ct[16];
   u32 msg_u32[32];
   u32 cnt[4];
   int i;

/* Translating all the inputs to 32-bit words                        */

   for (i=0;i<16;i++)
      pt[i]=U8TO32_LITTLE(chaining_value+4*i);

   for (i=0;i<32;i++)
      msg_u32[i]=U8TO32_LITTLE(message_block+4*i);

   cnt[1]=(u32)(counter>>32);
   cnt[0]=(u32)(counter & 0xFFFFFFFFULL);

/* Due to NIST specifications, there are no messages of length       */
/* longer than 2^64 that are expected				     */

   cnt[2]=0;
   cnt[3]=0;

/* Computing the encryption function                                 */

   E512(pt, ct, msg_u32, cnt);


/* Davies-Meyer transformation                                       */
 
   for (i=0;i<16;i++) 
       pt[i]^=ct[i]; 

/* Translating the output to 8-bit words                             */

   for(i=0; i<16; i++)
       U32TO8_LITTLE(chaining_value+i*4, pt[i]); 

   return;
}
