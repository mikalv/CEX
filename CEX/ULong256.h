#ifndef _CEX_UINT256_H
#define _CEX_UINT256_H

#include "CexDomain.h"
#include "Intrinsics.h"

NAMESPACE_NUMERIC

/// <summary>
/// An AVX2 256bit SIMD intrinsics wrapper.
/// <para>Processes blocks of 64bit unsigned integers.</para>
/// </summary>
class ULong256
{
#if defined(__AVX2__)

public:

	/// <summary>
	/// The internal m256i register value
	/// </summary>
	__m256i ymm;

	//~~~ Constants~~~//

	/// <summary>
	/// A ULong256 initialized with 4x 64bit integers to the value one
	/// </summary>
	inline static const ULong256 ONE()
	{
		return ULong256(_mm256_set1_epi64x(1));
	}

	/// <summary>
	/// A ULong256 initialized with 4x 64bit integers to the value 0
	/// </summary>
	inline static const ULong256 ZERO()
	{
		return ULong256(_mm256_set1_epi64x(0));
	}

	//~~~Constructor~~~//

	/// <summary>
	/// Default constructor; does not initialize the register
	/// </summary>
	ULong256()
	{
	}

	/// <summary>
	/// Initialize with an __m256i integer
	/// </summary>
	///
	/// <param name="Y">The register to copy</param>
	explicit ULong256(__m256i const &Y)
	{
		ymm = Y;
	}

	/// <summary>
	/// Initialize with an 8bit unsigned integer array
	/// </summary>
	///
	/// <param name="Input">The array containing the data; must be at least 16 bytes</param>
	/// <param name="Offset">The starting offset within the Input array</param>
	explicit ULong256(const std::vector<byte> &Input, size_t Offset)
	{
		ymm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&Input[Offset]));
	}

	/// <summary>
	/// Initialize with a 64bit unsigned integer array
	/// </summary>
	///
	/// <param name="Input">The array containing the data; must be at least 2 * 64bit uints</param>
	/// <param name="Offset">The starting offset within the Input array</param>
	explicit ULong256(const std::vector<ulong> &Input, size_t Offset)
	{
		ymm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&Input[Offset]));
	}

	/// <summary>
	/// Initialize with 4 * 64bit unsigned integers
	/// </summary>
	///
	/// <param name="X0">ulong 0</param>
	/// <param name="X1">ulong 1</param>
	/// <param name="X2">ulong 2</param>
	/// <param name="X3">ulong 3</param>
	explicit ULong256(ulong X0, ulong X1, ulong X2, ulong X3)
	{
		ymm = _mm256_set_epi64x(X0, X1, X2, X3);
	}

	/// <summary>
	/// Initialize with 1 * 64bit unsigned integer
	/// </summary>
	///
	/// <param name="X">The uint to add</param>
	explicit ULong256(ulong X)
	{
		ymm = _mm256_set1_epi64x(X);
	}

	//~~~Load and Store~~~//

	/// <summary>
	/// Load an array into a register in Little Endian format
	/// </summary>
	///
	/// <param name="Input">The array containing the data; must be at least 256 bits in length</param>
	/// <param name="Offset">The starting offset within the Input array</param>
	template <typename T>
	inline void Load(const std::vector<T> &Input, size_t Offset)
	{
		ymm = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&Input[Offset]));
	}

	/// <summary>
	/// Load with 4 * 64bit unsigned integers in Little Endian format
	/// </summary>
	///
	/// <param name="X0">uint64 0</param>
	/// <param name="X1">uint64 1</param>
	/// <param name="X2">uint64 2</param>
	/// <param name="X3">uint64 3</param>
	inline void Load(ulong X0, ulong X1, ulong X2, ulong X3)
	{
		ymm = _mm256_set_epi64x(X0, X1, X2, X3);
	}

	/// <summary>
	/// Store register in an integer array in Little Endian format
	/// </summary>
	///
	/// <param name="Output">The array containing the data; must be at least 256 bits in length</param>
	/// <param name="Offset">The starting offset within the Input array</param>
	template <typename T>
	inline void Store(std::vector<T> &Output, size_t Offset) const
	{
		_mm256_storeu_si256(reinterpret_cast<__m256i*>(&Output[Offset]), ymm);
	}
	
	//~~~Public Functions~~~//

	/// <summary>
	/// Returns the absolute value.
	/// <para>Note: returns the absolute value of the 32 bit integers</para>
	/// </summary>
	///
	/// <param name="Value">The comparison integer</param>
	/// 
	/// <returns>The processed ULong256</returns>
	inline static ULong256 Abs(const ULong256 &Value)
	{
		return ULong256(_mm256_abs_epi32(Value.ymm));
	}

	/// <summary>
	/// Computes the bitwise AND of the 256-bit value in *this* and the bitwise NOT of the 256-bit value in X
	/// </summary>
	///
	/// <param name="X">The comparison integer</param>
	/// 
	/// <returns>The processed ULong256</returns>
	inline ULong256 AndNot(const ULong256 &X)
	{
		return ULong256(_mm256_andnot_si256(ymm, X.ymm));
	}

	/// <summary>
	/// Returns the length of the register in bytes
	/// </summary>
	///
	/// <returns>The registers size</returns>
	inline static const size_t size()
	{
		return sizeof(__m256i);
	}

	/// <summary>
	/// Computes the 64 bit left rotation of four unsigned integers
	/// </summary>
	///
	/// <param name="Shift">The shift degree; maximum is 64</param>
	inline void RotL64(const int Shift)
	{
		ymm = _mm256_or_si256(_mm256_slli_epi64(ymm, static_cast<int>(Shift)), _mm256_srli_epi64(ymm, static_cast<int>(64 - Shift)));
	}

	/// <summary>
	/// Computes the 64 bit left rotation of four unsigned integers
	/// </summary>
	///
	/// <param name="X">The integer to rotate</param>
	/// <param name="Shift">The shift degree; maximum is 64</param>
	/// 
	/// <returns>The rotated ULong256</returns>
	inline static ULong256 RotL64(const ULong256 &X, const int Shift)
	{
		return ULong256(_mm256_or_si256(_mm256_slli_epi64(X.ymm, static_cast<int>(Shift)), _mm256_srli_epi64(X.ymm, static_cast<int>(64 - Shift))));
	}

	/// <summary>
	/// Computes the 64 bit right rotation of four unsigned integers
	/// </summary>
	///
	/// <param name="Shift">The shift degree; maximum is 64</param>
	inline void RotR64(const int Shift)
	{
		RotL64(64 - Shift);
	}

	/// <summary>
	/// Computes the 64 bit right rotation of four unsigned integers
	/// </summary>
	///
	/// <param name="X">The integer to rotate</param>
	/// <param name="Shift">The shift degree; maximum is 64</param>
	/// 
	/// <returns>The rotated ULong256</returns>
	static ULong256 RotR64(const ULong256 &X, const int Shift)
	{
		return RotL64(X, 64 - Shift);
	}

	/// <summary>
	/// Performs a byte swap on 4 unsigned integers
	/// </summary>
	/// 
	/// <returns>The byte swapped ULong256</returns>
	inline ULong256 Swap() const
	{
		__m256i T = ymm;

		T = _mm256_shufflehi_epi16(T, _MM_SHUFFLE(2, 3, 0, 1));
		T = _mm256_shufflelo_epi16(T, _MM_SHUFFLE(2, 3, 0, 1));

		return ULong256(_mm256_or_si256(_mm256_srli_epi16(T, 8), _mm256_slli_epi16(T, 8)));
	}

	/// <summary>
	/// Performs a byte swap on 4 unsigned integers
	/// </summary>
	/// 		
	/// <param name="X">The ULong256 to process</param>
	/// 
	/// <returns>The byte swapped ULong256</returns>
	inline static ULong256 Swap(ULong256 &X)
	{
		__m256i T = X.ymm;

		T = _mm256_shufflehi_epi16(T, _MM_SHUFFLE(2, 3, 0, 1));
		T = _mm256_shufflelo_epi16(T, _MM_SHUFFLE(2, 3, 0, 1));

		return ULong256(_mm256_or_si256(_mm256_srli_epi16(T, 8), _mm256_slli_epi16(T, 8)));
	}

	//~~~Operators~~~//

	/// <summary>
	/// Add two integers
	/// </summary>
	///
	/// <param name="X">The value to add</param>
	inline ULong256 operator + (const ULong256 &X) const
	{
		return ULong256(_mm256_add_epi64(ymm, X.ymm));
	}

	/// <summary>
	/// Add a value to this integer
	/// </summary>
	///
	/// <param name="X">The value to add</param>
	inline void operator += (const ULong256 &X)
	{
		ymm = _mm256_add_epi64(ymm, X.ymm);
	}

	/// <summary>
	/// Increase prefix operator
	/// </summary>
	inline ULong256 operator ++ ()
	{
		return ULong256(ymm) + ULong256::ONE();
	}

	/// <summary>
	/// Increase postfix operator
	/// </summary>
	inline ULong256 operator ++ (int)
	{
		return ULong256(ymm) + ULong256::ONE();
	}

	/// <summary>
	/// Subtract a value from this integer
	/// </summary>
	///
	/// <param name="X">The value to subtract</param>
	inline void operator -= (const ULong256 &X)
	{
		ymm = _mm256_sub_epi64(ymm, X.ymm);
	}

	/// <summary>
	/// Subtract two integers
	/// </summary>
	///
	/// <param name="X">The value to subtract</param>
	inline ULong256 operator - (const ULong256 &X) const
	{
		return ULong256(_mm256_sub_epi64(ymm, X.ymm));
	}

	/// <summary>
	/// Multiply a value with this integer
	/// </summary>
	///
	/// <param name="X">The value to multiply</param>
	inline void operator *= (const ULong256 &X)
	{
		__m256i tmp1 = _mm256_mul_epu32(ymm, X.ymm);
		__m256i tmp2 = _mm256_mul_epu32(_mm256_srli_si256(ymm, 4), _mm256_srli_si256(X.ymm, 4));
		ymm = _mm256_unpacklo_epi32(_mm256_shuffle_epi32(tmp1, _MM_SHUFFLE(0, 0, 2, 0)), _mm256_shuffle_epi32(tmp2, _MM_SHUFFLE(0, 0, 2, 0)));
	}

	/// <summary>
	/// Multiply two integers
	/// </summary>
	///
	/// <param name="X">The value to multiply</param>
	inline ULong256 operator * (const ULong256 &X) const
	{
		__m256i tmp1 = _mm256_mul_epu32(ymm, X.ymm);
		__m256i tmp2 = _mm256_mul_epu32(_mm256_srli_si256(ymm, 4), _mm256_srli_si256(X.ymm, 4));
		return ULong256(_mm256_unpacklo_epi32(_mm256_shuffle_epi32(tmp1, _MM_SHUFFLE(0, 0, 2, 0)), _mm256_shuffle_epi32(tmp2, _MM_SHUFFLE(0, 0, 2, 0))));
	}

	/// <summary>
	/// Divide two integers
	/// </summary>
	///
	/// <param name="X">The divisor value</param>
	inline ULong256 operator / (const ULong256 &X) const
	{
		// ToDo: fix this
		return ULong256(
			ymm.m256i_u64[0] / X.ymm.m256i_u64[0],
			ymm.m256i_u64[1] / X.ymm.m256i_u64[1],
			ymm.m256i_u64[2] / X.ymm.m256i_u64[2],
			ymm.m256i_u64[3] / X.ymm.m256i_u64[3]
		);
	}

	/// <summary>
	/// Divide this integer by a value
	/// </summary>
	///
	/// <param name="X">The divisor value</param>
	inline void operator /= (const ULong256 &X)
	{
		// ToDo: fix this
		ymm.m256i_u64[0] = ymm.m256i_u64[0] / X.ymm.m256i_u64[0];
		ymm.m256i_u64[1] = ymm.m256i_u64[1] / X.ymm.m256i_u64[1];
		ymm.m256i_u64[2] = ymm.m256i_u64[2] / X.ymm.m256i_u64[2];
		ymm.m256i_u64[3] = ymm.m256i_u64[3] / X.ymm.m256i_u64[3];

	}

	/// <summary>
	/// Get the remainder from a division operation between two integers
	/// </summary>
	///
	/// <param name="X">The divisor value</param>
	inline ULong256 operator % (const ULong256 &X) const
	{
		// ToDo: fix this
		return ULong256(
			ymm.m256i_u64[0] % X.ymm.m256i_u64[0],
			ymm.m256i_u64[1] % X.ymm.m256i_u64[1],
			ymm.m256i_u64[2] % X.ymm.m256i_u64[2],
			ymm.m256i_u64[3] % X.ymm.m256i_u64[3]
		);
	}

	/// <summary>
	/// Get the remainder from a division operation
	/// </summary>
	///
	/// <param name="X">The divisor value</param>
	inline void operator %= (const ULong256 &X)
	{
		// ToDo: fix this
		ymm.m256i_u64[0] = ymm.m256i_u64[0] % X.ymm.m256i_u64[0];
		ymm.m256i_u64[1] = ymm.m256i_u64[1] % X.ymm.m256i_u64[1];
		ymm.m256i_u64[2] = ymm.m256i_u64[2] % X.ymm.m256i_u64[2];
		ymm.m256i_u64[3] = ymm.m256i_u64[3] % X.ymm.m256i_u64[3];
	}

	/// <summary>
	/// Xor this integer by a value
	/// </summary>
	///
	/// <param name="X">The value to Xor</param>
	inline void operator ^= (const ULong256 &X)
	{
		ymm = _mm256_xor_si256(ymm, X.ymm);
	}

	/// <summary>
	/// Xor two integers
	/// </summary>
	///
	/// <param name="X">The value to Xor</param>
	inline ULong256 operator ^ (const ULong256 &X) const
	{
		return ULong256(_mm256_xor_si256(ymm, X.ymm));
	}

	/// <summary>
	/// Biwise OR of two integers
	/// </summary>
	///
	/// <param name="X">The value to OR</param>
	inline ULong256 operator | (const ULong256 &X)
	{
		return ULong256(_mm256_or_si256(ymm, X.ymm));
	}

	/// <summary>
	/// Biwise OR this integer
	/// </summary>
	///
	/// <param name="X">The value to OR</param>
	inline void operator |= (const ULong256 &X)
	{
		ymm = _mm256_or_si256(ymm, X.ymm);
	}

	/// <summary>
	/// Logical OR of two integers
	/// </summary>
	///
	/// <param name="X">The value to OR</param>
	inline ULong256 operator || (const ULong256 &X) const
	{
		return ULong256(ymm) | X;
	}

	/// <summary>
	/// Bitwise AND of two integers
	/// </summary>
	///
	/// <param name="X">The value to AND</param>
	inline ULong256 operator & (const ULong256 &X)
	{
		return ULong256(_mm256_and_si256(ymm, X.ymm));
	}

	/// <summary>
	/// Bitwise AND this integer
	/// </summary>
	///
	/// <param name="X">The value to AND</param>
	inline void operator &= (const ULong256 &X)
	{
		ymm = _mm256_and_si256(ymm, X.ymm);
	}

	/// <summary>
	/// Logical AND of two integers
	/// </summary>
	///
	/// <param name="X">The value to AND</param>
	inline ULong256 operator && (const ULong256 &X) const
	{
		return ULong256(ymm) & X;
	}

	/// <summary>
	/// Left shift this integer
	/// </summary>
	///
	/// <param name="Shift">The shift position</param>
	inline void operator <<= (const int Shift)
	{
		ymm = _mm256_slli_epi64(ymm, Shift);
	}

	/// <summary>
	/// Left shift two integers
	/// </summary>
	///
	/// <param name="Shift">The shift position</param>
	inline ULong256 operator << (const int Shift) const
	{
		return ULong256(_mm256_slli_epi64(ymm, Shift));
	}

	/// <summary>
	/// Right shift this integer
	/// </summary>
	///
	/// <param name="Shift">The shift position</param>
	inline void operator >>= (const int Shift)
	{
		ymm = _mm256_srli_epi64(ymm, Shift);
	}

	/// <summary>
	/// Right shift two integers
	/// </summary>
	///
	/// <param name="Shift">The shift position</param>
	inline ULong256 operator >> (const int Shift) const
	{
		return ULong256(_mm256_srli_epi64(ymm, Shift));
	}

	/// <summary>
	/// Bitwise NOT this integer
	/// </summary>
	inline ULong256 operator ~ () const
	{
		return ULong256(_mm256_xor_si256(ymm, _mm256_set1_epi32(0xFFFFFFFF)));
	}

	/// <summary>
	/// Greater than operator
	/// </summary>
	///
	/// <param name="X">The values to compare</param>
	inline ULong256 operator > (ULong256 const &X) const
	{
		return ULong256(_mm256_cmpgt_epi64(ymm, X.ymm));
	}

	/// <summary>
	/// Less than operator
	/// </summary>
	///
	/// <param name="X">The values to compare</param>
	inline ULong256 operator < (ULong256 const &X) const
	{
		return ULong256(_mm256_cmpgt_epi64(X.ymm, ymm));
	}

	/// <summary>
	/// Greater than or equal operator
	/// </summary>
	///
	/// <param name="X">The values to compare</param>
	inline ULong256 operator >= (ULong256 const &X) const
	{
		return ULong256(ULong256(~(X > ULong256(ymm))));
	}

	/// <summary>
	/// Less than operator or equal
	/// </summary>
	///
	/// <param name="X">The values to compare</param>
	inline ULong256 operator <= (ULong256 const &X) const
	{
		return X >= ULong256(ymm);
	}

	/// <summary>
	/// Compare two sets of integers for equality, returns max integer size if equal
	/// </summary>
	///
	/// <param name="X">The values to compare</param>
	inline ULong256 operator == (ULong256 const &X) const
	{
		return ULong256(_mm256_cmpeq_epi64(ymm, X.ymm));
	}

	/// <summary>
	/// Compare two sets of integers for inequality, returns max integer size if inequal
	/// </summary>
	inline ULong256 operator ! () const
	{
		return ULong256(_mm256_cmpeq_epi64(ymm, _mm256_setzero_si256()));
	}

	/// <summary>
	/// Compare two sets of integers for inequality, returns max integer size if inequal
	/// </summary>
	///
	/// <param name="X">The values to compare</param>
	inline ULong256 operator != (const ULong256 &X) const
	{
		return ~ULong256(_mm256_cmpeq_epi64(ymm, X.ymm));
	}

#endif
};

NAMESPACE_NUMERICEND
#endif