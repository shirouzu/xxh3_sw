#ifndef XXH3_SW

#if defined (__cplusplus)
extern "C" {
#endif

// detect cpu feature
int xxh_detect_feature();

// xxh3
XXH3_state_t* XXH3_createState_sw(void);
XXH_errorcode XXH3_128bits_reset_sw(XXH3_state_t *);
XXH_errorcode XXH3_freeState_sw(XXH3_state_t *);
XXH_errorcode XXH3_128bits_update_sw(XXH3_state_t* state, const void* input, size_t len);
XXH128_hash_t XXH3_128bits_digest_sw(const XXH3_state_t* state);

XXH3_state_t* XXH3_createState_def(void);
XXH_errorcode XXH3_128bits_reset_def(XXH3_state_t *);
XXH_errorcode XXH3_freeState_def(XXH3_state_t *);
XXH_errorcode XXH3_128bits_update_def(XXH3_state_t* state, const void* input, size_t len);
XXH128_hash_t XXH3_128bits_digest_def(const XXH3_state_t* state);

XXH3_state_t* XXH3_createState_sse2(void);
XXH_errorcode XXH3_128bits_reset_sse2(XXH3_state_t *);
XXH_errorcode XXH3_freeState_sse2(XXH3_state_t *);
XXH_errorcode XXH3_128bits_update_sse2(XXH3_state_t* state, const void* input, size_t len);
XXH128_hash_t XXH3_128bits_digest_sse2(const XXH3_state_t* state);

XXH3_state_t* XXH3_createState_avx2(void);
XXH_errorcode XXH3_128bits_reset_avx2(XXH3_state_t *);
XXH_errorcode XXH3_freeState_avx2(XXH3_state_t *);
XXH_errorcode XXH3_128bits_update_avx2(XXH3_state_t* state, const void* input, size_t len);
XXH128_hash_t XXH3_128bits_digest_avx2(const XXH3_state_t* state);

XXH3_state_t* XXH3_createState_avx512(void);
XXH_errorcode XXH3_128bits_reset_avx512(XXH3_state_t *);
XXH_errorcode XXH3_freeState_avx512(XXH3_state_t *);
XXH_errorcode XXH3_128bits_update_avx512(XXH3_state_t* state, const void* input, size_t len);
XXH128_hash_t XXH3_128bits_digest_avx512(const XXH3_state_t* state);

#if defined (__cplusplus)
}
#endif

#endif

