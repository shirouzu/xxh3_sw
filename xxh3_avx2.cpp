// 2020/07/30
// xxh3/xxHash switcher for SSE2/AVX2/AVX512 by H.Shirouzu

#define XXH_INLINE_ALL
#define XXH_VECTOR XXH_AVX2
#define __AVX2__
#include "xxh3.h"
#include "xxh3_sw.h"

// xxh3
XXH3_state_t* XXH3_createState_avx2(void) {
	return	XXH3_createState();
}

XXH_errorcode XXH3_128bits_reset_avx2(XXH3_state_t *state) {
	return	XXH3_128bits_reset(state);
}

XXH_errorcode XXH3_freeState_avx2(XXH3_state_t *state) {
	return XXH3_freeState(state);
}

XXH_errorcode XXH3_128bits_update_avx2(XXH3_state_t* state, const void* input, size_t len) {
	return XXH3_128bits_update(state, input, len);
}

XXH128_hash_t XXH3_128bits_digest_avx2(const XXH3_state_t* state) {
	return XXH3_128bits_digest(state);
}

