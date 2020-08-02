// 2020/07/30
// xxh3/xxHash switcher for VC++(SSE2/AVX2/AVX512) by H.Shirouzu

#include "xxh3.h"
#include "xxh3_sw.h"

#ifdef XXH3_SW_MAIN
#include <windows.h>
#include <stdio.h>

int main()
{
	XXH3_state_t *xxh3 = XXH3_createState_sw();

	XXH3_128bits_reset_sw(xxh3);

	BYTE	data[] = "abcdef";
	XXH3_128bits_update_sw(xxh3, data, sizeof(data));
	auto	digest = XXH3_128bits_digest_sw(xxh3);

	wprintf(L"xxh3(%d ...0:def 1:sse2 2:avx2 3:avx512) digest=%016llx/%016llx\n",
		xxh_detect_feature(), digest.high64, digest.low64);

	XXH3_freeState_sw(xxh3);
}
#endif

typedef unsigned __int64	uint64;
typedef unsigned int		uint32;

int xxh_detect_feature() {	// ref. xxh_x86dispatch.c
	static int best = []() {
		int		abcd[4] = {};
		int		best = XXH_SCALAR;
		uint64	xgetbv_val = 0;
		uint32	max_leaves = 0;

	//	return XXH_AVX2;

	// SSE2 check
		__cpuidex(abcd, 0, 0);
		if ((max_leaves = abcd[0]) == 0) {
			return best;
		}
#define SSE2_CPUID_MASK (1 << 26)
		__cpuidex(abcd, 1, 0);
		if ((abcd[3] & SSE2_CPUID_MASK) != SSE2_CPUID_MASK) {
			return best;
		}
		best = XXH_SSE2;

	// AVX2 check
		if (max_leaves < 7) {
			return best;
		}
#define OSXSAVE_CPUID_MASK ((1 << 26) | (1 << 27))
		if ((abcd[2] & OSXSAVE_CPUID_MASK) != OSXSAVE_CPUID_MASK) {
			return best;
		}

#define AVX2_CPUID_MASK (1 << 5)
#define AVX2_XGETBV_MASK ((1 << 2) | (1 << 1))
		__cpuidex(abcd, 7, 0);
		xgetbv_val = _xgetbv(0);
		if ((abcd[1] & AVX2_CPUID_MASK) != AVX2_CPUID_MASK) {
			return best;
		}
		if ((xgetbv_val & AVX2_XGETBV_MASK) != AVX2_XGETBV_MASK) {
			return best;
		}
		best = XXH_AVX2;

	// AVX512 check
#define AVX512F_CPUID_MASK (1 << 16)
#define AVX512F_XGETBV_MASK ((7 << 5) | (1 << 2) | (1 << 1))
		if ((abcd[1] & AVX512F_CPUID_MASK) != AVX512F_CPUID_MASK) {
			return best;
		}
		if ((xgetbv_val & AVX512F_XGETBV_MASK) != AVX512F_XGETBV_MASK) {
			return best;
		}
		best = XXH_AVX512;

		return	best;
	}();

	return	best;
}

// XXH3
static decltype(XXH3_createState)		*pXXH3_createState;
static decltype(XXH3_128bits_reset)		*pXXH3_128bits_reset;
static decltype(XXH3_freeState)			*pXXH3_freeState;
static decltype(XXH3_128bits_update)	*pXXH3_128bits_update;
static decltype(XXH3_128bits_digest)	*pXXH3_128bits_digest;

// init func for CPU features
bool xxh3_init_def() {
	pXXH3_createState		= XXH3_createState_def;
	pXXH3_128bits_reset		= XXH3_128bits_reset_def;
	pXXH3_freeState			= XXH3_freeState_def;
	pXXH3_128bits_update	= XXH3_128bits_update_def;
	pXXH3_128bits_digest	= XXH3_128bits_digest_def;
	return	true;
}

bool xxh3_init_sse2() {
	pXXH3_createState		= XXH3_createState_sse2;
	pXXH3_128bits_reset		= XXH3_128bits_reset_sse2;
	pXXH3_freeState			= XXH3_freeState_sse2;
	pXXH3_128bits_update	= XXH3_128bits_update_sse2;
	pXXH3_128bits_digest	= XXH3_128bits_digest_sse2;
	return	true;
}

bool xxh3_init_avx2() {
	pXXH3_createState		= XXH3_createState_avx2;
	pXXH3_128bits_reset		= XXH3_128bits_reset_avx2;
	pXXH3_freeState			= XXH3_freeState_avx2;
	pXXH3_128bits_update	= XXH3_128bits_update_avx2;
	pXXH3_128bits_digest	= XXH3_128bits_digest_avx2;
	return	true;
}

bool xxh3_init_avx512() {
	pXXH3_createState		= XXH3_createState_avx512;
	pXXH3_128bits_reset		= XXH3_128bits_reset_avx512;
	pXXH3_freeState			= XXH3_freeState_avx512;
	pXXH3_128bits_update	= XXH3_128bits_update_avx512;
	pXXH3_128bits_digest	= XXH3_128bits_digest_avx512;
	return	true;
}

bool xxh3_init() {
	switch (xxh_detect_feature()) {
	case XXH_SSE2:		return xxh3_init_sse2();
	case XXH_AVX2:		return xxh3_init_avx2();
	case XXH_AVX512:	return xxh3_init_avx512();
	default:			return xxh3_init_def();
	}
}

XXH3_state_t* XXH3_createState_sw(void) {
	static bool once = xxh3_init();
	return pXXH3_createState();
}

XXH_errorcode XXH3_128bits_reset_sw(XXH3_state_t *state) {
	return pXXH3_128bits_reset(state);
}

XXH_errorcode XXH3_freeState_sw(XXH3_state_t *state) {
	return pXXH3_freeState(state);
}

XXH_errorcode XXH3_128bits_update_sw(XXH3_state_t* state, const void* input, size_t len) {
	return pXXH3_128bits_update(state, input, len);
}

XXH128_hash_t XXH3_128bits_digest_sw(const XXH3_state_t* state) {
	return pXXH3_128bits_digest(state);
}

