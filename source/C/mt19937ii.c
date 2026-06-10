#include <util2/C/mt19937ii.h>
/* 
    This is a maximally equidistributed Mersenne Twister MEMT19937-II by Shin Harase (2014/11/10).
    
    A C-program for MT19937, with initialization improved 2002/1/26.
    Coded by Takuji Nishimura and Makoto Matsumoto.

    Before using, initialize the state by using init_genrand(seed)  
    or init_by_array(init_key, key_length).

    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
    All rights reserved.                          

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
        1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

        3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS i32ERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


    Any feedback is very welcome.
    http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
    email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/
/* [NOTE] ---------------- 'real' functions are due to Isaku Wada, 2002/01/09 added ---------------- [NOTE] */
/*
    Modified Under the specified license (as defined above) by inonitz
    For More Info regarding sources, see the following links:
	1. https://www.ritsumei.ac.jp/~harase/megenerators.html
	2. https://www.ritsumei.ac.jp/~harase/megenerators2.html
	3. https://www.ritsumei.ac.jp/~harase/memt19937-II.c
	Also See (WELL512 and friends):
	https://stackoverflow.com/a/1227137
	https://en.wikipedia.org/wiki/Well_equidistributed_long-period_linear
*/


/* Period parameters */
#define MT_N           624
#define MT_M           397
#define MT_MATRIX_A    0x9908b0dfU /* constant vector a */
#define MT_UPPER_MASK  0x80000000U /* most significant w-r bits */
#define MT_LOWER_MASK  0x7fffffffU /* least significant r bits */
#define MT_UINT32_MASK 0xffffffffU
#define MT_MIXBITS(u, v) (((u) & MT_UPPER_MASK) | ((v) & MT_LOWER_MASK))
#define MT_TWIST(u, v)   ((MT_MIXBITS(u, v) >> 1) ^ ((v) & 1U ? MT_MATRIX_A : 0U))


/* Tempering parameters */
#define MT_LAG1                 151
#define MT_LAG2                 36
#define MT_LAG1over             473
#define MT_LAG2over             588
#define MT_TEMPERING_SHIFT_1(z) (z << 8)
#define MT_TEMPERING_SHIFT_2(z) (z << 14)
#define MT_MASK1                0xb219beabU
#define MT_MASK2                0x56bde52aU


const u8 util2_mt19937ii_keyBufferLength = 8;
typedef u32 (*randomUint32GeneratorFunction_mt19937_ver2)(void);
typedef randomUint32GeneratorFunction_mt19937_ver2 mt19937ver2_32_func;


/* Global State */
util2_mt19937ii_keyBuffer_t gs_maybeRecordedInitState;
static mt19937ver2_32_func  gs_randNumGenFunc;
static u32 gs_state[MT_N];         /* the array for the state vector            */
static i32 gs_stateIdx = MT_N + 1; /* mti == N+1 means mt[N] is not initialized */
static u32 gs_z;


static void initializeGeneratorWithRand(u32 s);
static void initializeGeneratorWithRandArray(const u32 init_key[], i32 key_length);
static u32 internal_case_1(void);
static u32 internal_case_2(void);
static u32 internal_case_3(void);
static u32 internal_case_4(void);
static u32 internal_case_5(void);




void util2_initializeMersenneTwister19937Ver2_FixedDefault()
{
	const util2_mt19937ii_keyBuffer_t k_initBuf = {
        0x123U, 
        0x234U, 
        0x345U, 
        0x456U,
		0x567U,
		0x678U,
		0x789U,
		0x89AU
	};
	util2_initializeMersenneTwister19937Ver2_ExistingKeyBuffer(&k_initBuf);
	return;
}


void util2_initializeMersenneTwister19937Ver2_ExistingKeyBuffer(
    util2_mt19937ii_keyBuffer_t const* buf
) {
	initializeGeneratorWithRandArray( &(*buf)[0], util2_mt19937ii_keyBufferLength);
	for(u8 i = 0; i < util2_mt19937ii_keyBufferLength; ++i) {
		gs_maybeRecordedInitState[i] = (*buf)[i];
	}
	return;
}

void util2_getMersenneTwister19937Ver2_KeyBuffer(
    util2_mt19937ii_keyBuffer_t* toSet
) {
	for(u8 i = 0; i < util2_mt19937ii_keyBufferLength; ++i) {
		(*toSet)[i] = gs_maybeRecordedInitState[i];
	}
	return;
}


void util2_initializeMersenneTwister19937Ver2_RandomKeyBuffer(
    u32 const* keyBuf, 
    u16 keyBufLength
) {
    initializeGeneratorWithRandArray(keyBuf, (i32)keyBufLength);
    return;
}


/* generates a random number on [0,0x7fffffff] interval */
u32 util2_generate31BitUnsignedInt()
{
	return (u32)(gs_randNumGenFunc() >> 1);
}


/* generates a random number on [0,0xffffffff] interval */
u32 util2_generate32BitUnsignedInt()
{
    return gs_randNumGenFunc();
}


/* generates a random number on [0,1]-real-interval */
double util2_generateRealOnClosedInterval(void)
{
    const double k_uint32_max_inv = 1.0 / 4294967295.0;
    return gs_randNumGenFunc() * k_uint32_max_inv;
}


/* generates a random number on the [0,1) - real interval */
double util2_generateRealOnHalfClosedInterval(void)
{
    const double k_one_pow_32_inv = 1.0 / 4294967296.0;
	return gs_randNumGenFunc() * k_one_pow_32_inv;
}


/* generates a random number on the (0,1) - real interval */
double util2_generateRealOnOpenInterval()
{
    const double k_one_pow_32_inv = 1.0 / 4294967296.0;
	return (((double) gs_randNumGenFunc()) + 0.5) * k_one_pow_32_inv;
}


/* generates a random number on [0,1) with 53-bit resolution */
double util2_generateRealOnHalfClosedInterval53Bits()
{
    const double k_one_pow_53_inv       = 1.0 / 9007199254740992.0;
    const double k_funky_number_lol_idk = 67108864.0; /* 0x4000000 */
	u32 a = gs_randNumGenFunc() >> 5;
    u32 b = gs_randNumGenFunc() >> 6;
	return (a * k_funky_number_lol_idk + b) * k_one_pow_53_inv;
}




/*  ---------------- Internal Implementation Details ---------------- */


/* 
    [NOTE]: do not use this function directly
    initializes mt[N] with a seed
*/
void initializeGeneratorWithRand(u32 s) {
	gs_state[0] = s & MT_UINT32_MASK;
	for (gs_stateIdx = 1; gs_stateIdx < MT_N; gs_stateIdx++) {
		gs_state[gs_stateIdx] =
		    (1812433253U * (gs_state[gs_stateIdx - 1] ^ (gs_state[gs_stateIdx - 1] >> 30)) + gs_stateIdx);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		gs_state[gs_stateIdx] &= MT_UINT32_MASK;
		/* for >32 bit machines */
	}
	gs_stateIdx       = 0;
	gs_randNumGenFunc = internal_case_1;
}


/*
    initialize by an array with array-length
    init_key is the array for initializing keys
    key_length is its length
    slight change for C++, 2004/2/26
*/
void initializeGeneratorWithRandArray(const u32 init_key[], i32 key_length) 
{
	i32 i, j, k;
	initializeGeneratorWithRand(19650218U);
	i = 1;
	j = 0;
	k = (MT_N > key_length ? MT_N : key_length);
	for (; k; k--) {
		gs_state[i] = (gs_state[i] ^ ((gs_state[i - 1] ^ (gs_state[i - 1] >> 30)) * 1664525U)) + init_key[j] + j; /* non linear */
		gs_state[i] &= MT_UINT32_MASK; /* for WORDSIZE > 32 machines */
		i++;
		j++;
		if (i >= MT_N) {
			gs_state[0] = gs_state[MT_N - 1];
			i           = 1;
		}
		if (j >= key_length) {
			j = 0;
        }
	}
	for (k = MT_N - 1; k; k--) {
		gs_state[i] = (gs_state[i] ^ ((gs_state[i - 1] ^ (gs_state[i - 1] >> 30)) * 1566083941U)) - i; /* non linear */
		gs_state[i] &= MT_UINT32_MASK;                                                                             /* for WORDSIZE > 32 machines */
		i++;
		if (i >= MT_N) {
			gs_state[0] = gs_state[MT_N - 1];
			i           = 1;
		}
	}

	gs_state[0] = MT_UPPER_MASK; /* MSB is 1; assuring non-zero initial array */
	gs_stateIdx = 0;
	gs_randNumGenFunc = internal_case_1;
    return;
}




u32 internal_case_1(void) {
	gs_state[gs_stateIdx] = gs_state[gs_stateIdx + MT_M] ^ MT_TWIST(gs_state[gs_stateIdx], gs_state[gs_stateIdx + 1]);
	gs_z                        = gs_state[gs_stateIdx] ^ (gs_state[gs_stateIdx + MT_LAG1] & MT_MASK1);
	gs_z ^= MT_TEMPERING_SHIFT_1(gs_z);
	gs_z ^= MT_TEMPERING_SHIFT_2(gs_z);
	gs_z ^= (gs_state[gs_stateIdx + MT_LAG2] & MT_MASK2);
	gs_stateIdx++;
	if (gs_stateIdx == MT_N - MT_M)
		gs_randNumGenFunc = internal_case_2;
	return gs_z;
}


u32 internal_case_2(void) {
	gs_state[gs_stateIdx] = gs_state[gs_stateIdx + (MT_M - MT_N)] ^ MT_TWIST(gs_state[gs_stateIdx], gs_state[gs_stateIdx + 1]);
	gs_z                        = gs_state[gs_stateIdx] ^ (gs_state[gs_stateIdx + MT_LAG1] & MT_MASK1);
	gs_z ^= MT_TEMPERING_SHIFT_1(gs_z);
	gs_z ^= MT_TEMPERING_SHIFT_2(gs_z);
	gs_z ^= (gs_state[gs_stateIdx + MT_LAG2] & MT_MASK2);
	gs_stateIdx++;
	if (gs_stateIdx == MT_LAG1over) {
		gs_randNumGenFunc = internal_case_3;
    }
	return gs_z;
}


u32 internal_case_3(void) {
	gs_state[gs_stateIdx] = gs_state[gs_stateIdx + (MT_M - MT_N)] ^ MT_TWIST(gs_state[gs_stateIdx], gs_state[gs_stateIdx + 1]);
	gs_z                        = gs_state[gs_stateIdx] ^ (gs_state[gs_stateIdx - MT_LAG1over] & MT_MASK1);
	gs_z ^= MT_TEMPERING_SHIFT_1(gs_z);
	gs_z ^= MT_TEMPERING_SHIFT_2(gs_z);
	gs_z ^= (gs_state[gs_stateIdx + MT_LAG2] & MT_MASK2);
	gs_stateIdx++;
	if (gs_stateIdx == MT_LAG2over) {
		gs_randNumGenFunc = internal_case_4;
    }
	return gs_z;
}


u32 internal_case_4(void) {
	gs_state[gs_stateIdx] = gs_state[gs_stateIdx + (MT_M - MT_N)] ^ MT_TWIST(gs_state[gs_stateIdx], gs_state[gs_stateIdx + 1]);
	gs_z                        = gs_state[gs_stateIdx] ^ (gs_state[gs_stateIdx - MT_LAG1over] & MT_MASK1);
	gs_z ^= MT_TEMPERING_SHIFT_1(gs_z);
	gs_z ^= MT_TEMPERING_SHIFT_2(gs_z);
	gs_z ^= (gs_state[gs_stateIdx - MT_LAG2over] & MT_MASK2);
	gs_stateIdx++;
	if (gs_stateIdx == MT_N - 1) {
		gs_randNumGenFunc = internal_case_5;
    }
	return gs_z;
}


u32 internal_case_5(void) {
	gs_state[MT_N - 1] = gs_state[MT_M - 1] ^ MT_TWIST(gs_state[MT_N - 1], gs_state[0]);
	gs_z            = gs_state[gs_stateIdx] ^ (gs_state[gs_stateIdx - MT_LAG1over] & MT_MASK1);
	gs_z ^= MT_TEMPERING_SHIFT_1(gs_z);
	gs_z ^= MT_TEMPERING_SHIFT_2(gs_z);
	gs_z ^= (gs_state[gs_stateIdx - MT_LAG2over] & MT_MASK2);
	gs_stateIdx       = 0;
	gs_randNumGenFunc = internal_case_1;
	return gs_z;
}
