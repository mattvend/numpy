#ifndef NPY_SIMD
    #error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SSE_MISC_H
#define _NPY_SIMD_SSE_MISC_H

// vector with zero lanes
#define npyv_zero_u8  _mm_setzero_si128
#define npyv_zero_s8  _mm_setzero_si128
#define npyv_zero_u16 _mm_setzero_si128
#define npyv_zero_s16 _mm_setzero_si128
#define npyv_zero_u32 _mm_setzero_si128
#define npyv_zero_s32 _mm_setzero_si128
#define npyv_zero_u64 _mm_setzero_si128
#define npyv_zero_s64 _mm_setzero_si128
#define npyv_zero_f32 _mm_setzero_ps
#define npyv_zero_f64 _mm_setzero_pd

// vector with a specific value set to all lanes
#define npyv_setall_u8(VAL)  _mm_set1_epi8((char)VAL)
#define npyv_setall_s8(VAL)  _mm_set1_epi8((char)VAL)
#define npyv_setall_u16(VAL) _mm_set1_epi16((short)VAL)
#define npyv_setall_s16(VAL) _mm_set1_epi16((short)VAL)
#define npyv_setall_u32(VAL) _mm_set1_epi32((int)VAL)
#define npyv_setall_s32(VAL) _mm_set1_epi32(VAL)
#if !defined(__x86_64__) && !defined(_M_X64)
    #define npyv_setall_u64(VAL) _mm_set_epi32((int)(VAL >> 32), (int)VAL, (int)(VAL >> 32), (int)VAL)
    #define npyv_setall_s64 npyv_setall_u64
#else
    #define npyv_setall_u64(VAL) _mm_set1_epi64x(VAL)
    #define npyv_setall_s64(VAL) _mm_set1_epi64x(VAL)
#endif
#define npyv_setall_f32(VAL) _mm_set1_ps(VAL)
#define npyv_setall_f64(VAL) _mm_set1_pd(VAL)

/**
 * vector with specific values set to each lane and
 * set a specific value to all remained lanes
 *
 * Args that generated by NPYV__SET_FILL_* not going to expand if
 * _mm_setr_* are defined as macros.
 */
NPY_FINLINE __m128i npyv__setr_epi8(
    char i0, char i1, char i2,  char i3,  char i4,  char i5,  char i6,  char i7,
    char i8, char i9, char i10, char i11, char i12, char i13, char i14, char i15)
{
    return _mm_setr_epi8(i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15);
}
NPY_FINLINE __m128i npyv__setr_epi16(short i0, short i1, short i2, short i3, short i4, short i5,
                                     short i6, short i7)
{
    return _mm_setr_epi16(i0, i1, i2, i3, i4, i5, i6, i7);
}
NPY_FINLINE __m128i npyv__setr_epi32(int i0, int i1, int i2, int i3)
{
    return _mm_setr_epi32(i0, i1, i2, i3);
}
NPY_FINLINE __m128i npyv__setr_epi64(npy_int64 i0, npy_int64 i1)
{
    return _mm_set_epi64x(i1, i0);
}
NPY_FINLINE __m128 npyv__setr_ps(float i0, float i1, float i2, float i3)
{
    return _mm_setr_ps(i0, i1, i2, i3);
}
NPY_FINLINE __m128d npyv__setr_pd(double i0, double i1)
{
    return _mm_setr_pd(i0, i1);
}
#define npyv_setf_u8(FILL, ...)  npyv__setr_epi8(NPYV__SET_FILL_16(char, FILL, __VA_ARGS__))
#define npyv_setf_s8(FILL, ...)  npyv__setr_epi8(NPYV__SET_FILL_16(char, FILL, __VA_ARGS__))
#define npyv_setf_u16(FILL, ...) npyv__setr_epi16(NPYV__SET_FILL_8(short, FILL, __VA_ARGS__))
#define npyv_setf_s16(FILL, ...) npyv__setr_epi16(NPYV__SET_FILL_8(short, FILL, __VA_ARGS__))
#define npyv_setf_u32(FILL, ...) npyv__setr_epi32(NPYV__SET_FILL_4(int, FILL, __VA_ARGS__))
#define npyv_setf_s32(FILL, ...) npyv__setr_epi32(NPYV__SET_FILL_4(int, FILL, __VA_ARGS__))
#define npyv_setf_u64(FILL, ...) npyv__setr_epi64(NPYV__SET_FILL_2(npy_int64, FILL, __VA_ARGS__))
#define npyv_setf_s64(FILL, ...) npyv__setr_epi64(NPYV__SET_FILL_2(npy_int64, FILL, __VA_ARGS__))
#define npyv_setf_f32(FILL, ...) npyv__setr_ps(NPYV__SET_FILL_4(float, FILL, __VA_ARGS__))
#define npyv_setf_f64(FILL, ...) npyv__setr_pd(NPYV__SET_FILL_2(double, FILL, __VA_ARGS__))

// vector with specific values set to each lane and
// set zero to all remained lanes
#define npyv_set_u8(...)  npyv_setf_u8(0,  __VA_ARGS__)
#define npyv_set_s8(...)  npyv_setf_s8(0,  __VA_ARGS__)
#define npyv_set_u16(...) npyv_setf_u16(0, __VA_ARGS__)
#define npyv_set_s16(...) npyv_setf_s16(0, __VA_ARGS__)
#define npyv_set_u32(...) npyv_setf_u32(0, __VA_ARGS__)
#define npyv_set_s32(...) npyv_setf_s32(0, __VA_ARGS__)
#define npyv_set_u64(...) npyv_setf_u64(0, __VA_ARGS__)
#define npyv_set_s64(...) npyv_setf_s64(0, __VA_ARGS__)
#define npyv_set_f32(...) npyv_setf_f32(0, __VA_ARGS__)
#define npyv_set_f64(...) npyv_setf_f64(0, __VA_ARGS__)

// Per lane select
#ifdef NPY_HAVE_SSE41
    #define npyv_select_u8(MASK, A, B)  _mm_blendv_epi8(B, A, MASK)
    #define npyv_select_f32(MASK, A, B) _mm_blendv_ps(B, A, _mm_castsi128_ps(MASK))
    #define npyv_select_f64(MASK, A, B) _mm_blendv_pd(B, A, _mm_castsi128_pd(MASK))
#else
    NPY_FINLINE __m128i npyv_select_u8(__m128i mask, __m128i a, __m128i b)
    { return _mm_xor_si128(b, _mm_and_si128(_mm_xor_si128(b, a), mask)); }
    NPY_FINLINE __m128 npyv_select_f32(__m128i mask, __m128 a, __m128 b)
    { return _mm_xor_ps(b, _mm_and_ps(_mm_xor_ps(b, a), _mm_castsi128_ps(mask))); }
    NPY_FINLINE __m128d npyv_select_f64(__m128i mask, __m128d a, __m128d b)
    { return _mm_xor_pd(b, _mm_and_pd(_mm_xor_pd(b, a), _mm_castsi128_pd(mask))); }
#endif
#define npyv_select_s8  npyv_select_u8
#define npyv_select_u16 npyv_select_u8
#define npyv_select_s16 npyv_select_u8
#define npyv_select_u32 npyv_select_u8
#define npyv_select_s32 npyv_select_u8
#define npyv_select_u64 npyv_select_u8
#define npyv_select_s64 npyv_select_u8

// Reinterpret
#define npyv_reinterpret_u8_u8(X)  X
#define npyv_reinterpret_u8_s8(X)  X
#define npyv_reinterpret_u8_u16(X) X
#define npyv_reinterpret_u8_s16(X) X
#define npyv_reinterpret_u8_u32(X) X
#define npyv_reinterpret_u8_s32(X) X
#define npyv_reinterpret_u8_u64(X) X
#define npyv_reinterpret_u8_s64(X) X
#define npyv_reinterpret_u8_f32 _mm_castps_si128
#define npyv_reinterpret_u8_f64 _mm_castpd_si128

#define npyv_reinterpret_s8_s8(X)  X
#define npyv_reinterpret_s8_u8(X)  X
#define npyv_reinterpret_s8_u16(X) X
#define npyv_reinterpret_s8_s16(X) X
#define npyv_reinterpret_s8_u32(X) X
#define npyv_reinterpret_s8_s32(X) X
#define npyv_reinterpret_s8_u64(X) X
#define npyv_reinterpret_s8_s64(X) X
#define npyv_reinterpret_s8_f32 _mm_castps_si128
#define npyv_reinterpret_s8_f64 _mm_castpd_si128

#define npyv_reinterpret_u16_u16(X) X
#define npyv_reinterpret_u16_u8(X)  X
#define npyv_reinterpret_u16_s8(X)  X
#define npyv_reinterpret_u16_s16(X) X
#define npyv_reinterpret_u16_u32(X) X
#define npyv_reinterpret_u16_s32(X) X
#define npyv_reinterpret_u16_u64(X) X
#define npyv_reinterpret_u16_s64(X) X
#define npyv_reinterpret_u16_f32 _mm_castps_si128
#define npyv_reinterpret_u16_f64 _mm_castpd_si128

#define npyv_reinterpret_s16_s16(X) X
#define npyv_reinterpret_s16_u8(X)  X
#define npyv_reinterpret_s16_s8(X)  X
#define npyv_reinterpret_s16_u16(X) X
#define npyv_reinterpret_s16_u32(X) X
#define npyv_reinterpret_s16_s32(X) X
#define npyv_reinterpret_s16_u64(X) X
#define npyv_reinterpret_s16_s64(X) X
#define npyv_reinterpret_s16_f32 _mm_castps_si128
#define npyv_reinterpret_s16_f64 _mm_castpd_si128

#define npyv_reinterpret_u32_u32(X) X
#define npyv_reinterpret_u32_u8(X)  X
#define npyv_reinterpret_u32_s8(X)  X
#define npyv_reinterpret_u32_u16(X) X
#define npyv_reinterpret_u32_s16(X) X
#define npyv_reinterpret_u32_s32(X) X
#define npyv_reinterpret_u32_u64(X) X
#define npyv_reinterpret_u32_s64(X) X
#define npyv_reinterpret_u32_f32 _mm_castps_si128
#define npyv_reinterpret_u32_f64 _mm_castpd_si128

#define npyv_reinterpret_s32_s32(X) X
#define npyv_reinterpret_s32_u8(X)  X
#define npyv_reinterpret_s32_s8(X)  X
#define npyv_reinterpret_s32_u16(X) X
#define npyv_reinterpret_s32_s16(X) X
#define npyv_reinterpret_s32_u32(X) X
#define npyv_reinterpret_s32_u64(X) X
#define npyv_reinterpret_s32_s64(X) X
#define npyv_reinterpret_s32_f32 _mm_castps_si128
#define npyv_reinterpret_s32_f64 _mm_castpd_si128

#define npyv_reinterpret_u64_u64(X) X
#define npyv_reinterpret_u64_u8(X)  X
#define npyv_reinterpret_u64_s8(X)  X
#define npyv_reinterpret_u64_u16(X) X
#define npyv_reinterpret_u64_s16(X) X
#define npyv_reinterpret_u64_u32(X) X
#define npyv_reinterpret_u64_s32(X) X
#define npyv_reinterpret_u64_s64(X) X
#define npyv_reinterpret_u64_f32 _mm_castps_si128
#define npyv_reinterpret_u64_f64 _mm_castpd_si128

#define npyv_reinterpret_s64_s64(X) X
#define npyv_reinterpret_s64_u8(X)  X
#define npyv_reinterpret_s64_s8(X)  X
#define npyv_reinterpret_s64_u16(X) X
#define npyv_reinterpret_s64_s16(X) X
#define npyv_reinterpret_s64_u32(X) X
#define npyv_reinterpret_s64_s32(X) X
#define npyv_reinterpret_s64_u64(X) X
#define npyv_reinterpret_s64_f32 _mm_castps_si128
#define npyv_reinterpret_s64_f64 _mm_castpd_si128

#define npyv_reinterpret_f32_f32(X) X
#define npyv_reinterpret_f32_u8  _mm_castsi128_ps
#define npyv_reinterpret_f32_s8  _mm_castsi128_ps
#define npyv_reinterpret_f32_u16 _mm_castsi128_ps
#define npyv_reinterpret_f32_s16 _mm_castsi128_ps
#define npyv_reinterpret_f32_u32 _mm_castsi128_ps
#define npyv_reinterpret_f32_s32 _mm_castsi128_ps
#define npyv_reinterpret_f32_u64 _mm_castsi128_ps
#define npyv_reinterpret_f32_s64 _mm_castsi128_ps
#define npyv_reinterpret_f32_f64 _mm_castpd_ps

#define npyv_reinterpret_f64_f64(X) X
#define npyv_reinterpret_f64_u8  _mm_castsi128_pd
#define npyv_reinterpret_f64_s8  _mm_castsi128_pd
#define npyv_reinterpret_f64_u16 _mm_castsi128_pd
#define npyv_reinterpret_f64_s16 _mm_castsi128_pd
#define npyv_reinterpret_f64_u32 _mm_castsi128_pd
#define npyv_reinterpret_f64_s32 _mm_castsi128_pd
#define npyv_reinterpret_f64_u64 _mm_castsi128_pd
#define npyv_reinterpret_f64_s64 _mm_castsi128_pd
#define npyv_reinterpret_f64_f32 _mm_castps_pd

// Only required by AVX2/AVX512
#define npyv_cleanup() ((void)0)

#endif // _NPY_SIMD_SSE_MISC_H
