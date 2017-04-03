// The GPL version 3 License (GPLv3)
// 
// Copyright (c) 2017 vtdev.com
// This file is part of the CEX Cryptographic library.
// 
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <http://www.gnu.org/licenses/>.
//
// 
// Implementation Details:
// An implementation of the Scrypt Derivation Function (SCRYPT) written by Colin Percival.
// Written by John Underhill, March 24, 2017
// Contact: develop@vtdev.com

#ifndef _CEX_SCRYPT_H
#define _CEX_SCRYPT_H

#include "IKdf.h"
#include "Digests.h"
#include "IDigest.h"
#include "ParallelOptions.h"

NAMESPACE_KDF

using Enumeration::Digests;
using Digest::IDigest;
using Common::ParallelOptions;

/// <summary>
/// An implementation of the Key Derivation Function: SCRYPT
/// </summary> 
/// 
/// <example>
/// <description>Generate an array of pseudo random bytes:</description>
/// <code>
/// // set to 10,000 rounds (default: 4000)
/// SCRYPT kdf(Enumeration::Digests::SHA256, 16384, 8, 1);
/// // initialize
/// kdf.Initialize(Key, [Salt]);
/// // generate bytes
/// kdf.Generate(Output, [Offset], [Size]);
/// </code>
/// </example>
/// 
/// <remarks>
/// <description><B>Overview:</B></description>
/// <para>SCRYPT is a password-based key derivation function created by Colin Percival, originally for the Tarsnap online backup service. \n
/// SCRYPT uses a combination of a message digest and the Salsa stream cipher to make it costly to perform large-scale hardware attacks by requiring large amounts of memory
/// to generate an output key. \n
/// Using the same input key, and optional salt, produces the exact same output. \n
/// It is recommended that a salt value is added along with the key.</para>
/// 
/// <description><B>Description:</B></description> \n
/// <EM>Legend:</EM> \n
/// <B>P</B>=passphrase, <B>S</B>=salt, <B>N</B>=cpu/memory cost, <B>r</B>=block-size, <B>P</B>=parallelization parameter, <B>DK</B>=derived key \n
/// <para><EM>Generate:</EM> \n
/// 1) Initialize an array B consisting of p blocks of 128 * r octets each: \n
///		B[0] || B[1] || ... || B[p - 1] = PBKDF2 - HMAC - SHA256(P, S, 1, p * 128 * r) \n
/// 2) for i = 0 to p - 1 do: B[i] = scryptROMix(r, B[i], N) \n
/// 3) DK = PBKDF2 - HMAC - SHA256(P, B[0] || B[1] || ... || B[p - 1], 1, dkLen)</para>
///
/// <description><B>Implementation Notes:</B></description>
/// <list type="bullet">
/// <item><description>Class can be initialized with a message digest instance, or by using a digests enumeration type name.</description></item>
/// <item><description>The minimum key size is the size the digests return array in bytes, a key equal to the digests block size is recommended.</description></item>
/// <item><description>The use of a salt value can strongly mitigate some attack vectors targeting the key, and is highly recommended with SCRYPT.</description></item>
/// <item><description>The minimum salt size is 4 bytes, larger (pseudo-random) salt values are more secure.</description></item>
/// <item><description>The generator must be initialized with a key using one of the Initialize() functions before output can be generated.</description></item>
/// </list>
/// 
/// <description><B>Guiding Publications:</B></description>
/// <list type="number">
/// <item><description>SCRYPT: <a href="https://www.tarsnap.com/scrypt/scrypt.pdf">Stronger Key Derivation</a> via Sequential Memory Hard Functions.</description></item>
/// <item><description>RFC 7914: <a href="https://tools.ietf.org/html/rfc7914">The scrypt Password-Based Key Derivation Function</a>.</description></item>
/// <item><description>Scrypt is <a href="http://eprint.iacr.org/2016/989.pdf">Maximally Memory-Hard</a>.</description></item>
/// </list>
/// </remarks>
class SCRYPT : public IKdf 
{
private:

	struct ScryptParameters
	{
		size_t CpuCost;
		size_t Parallelization;

		explicit ScryptParameters(size_t CpuCost, size_t Parallelization)
			:
			CpuCost(CpuCost),
			Parallelization(Parallelization)
		{}

		void Reset()
		{
			CpuCost = 0;
			Parallelization = 0;
		}
	};

	const size_t MEM_COST = 8;
	const size_t MIN_PASSLEN = 6;
	const size_t MIN_SALTLEN = 4;

	IDigest* m_kdfDigest;
	bool m_destroyEngine;
	bool m_isDestroyed;
	bool m_isInitialized;
	Digests m_kdfDigestType;
	std::vector<byte> m_kdfKey;
	std::vector<byte> m_kdfSalt;
	std::vector<SymmetricKeySize> m_legalKeySizes;
	ParallelOptions m_parallelProfile;
	ScryptParameters m_scryptParameters;

public:

	SCRYPT() = delete;
	SCRYPT(const SCRYPT&) = delete;
	SCRYPT& operator=(const SCRYPT&) = delete;
	SCRYPT& operator=(SCRYPT&&) = delete;

	//~~~Properties~~~//

	/// <summary>
	/// Get: The Kdf generators type name
	/// </summary>
	virtual const Kdfs Enumeral() { return Kdfs::SCRYPT; }

	/// <summary>
	/// Get: Generator is ready to produce random
	/// </summary>
	virtual const bool IsInitialized() { return m_isInitialized; }

	/// <summary>
	/// Get: Processor parallelization availability.
	/// <para>Indicates whether parallel processing is available with this protocol.
	/// Multi-threading and SIMD parallelization can be modified through the ParallelProfile() accessor.</para>
	/// </summary>
	const bool IsParallel() { return m_parallelProfile.IsParallel(); }

	/// <summary>
	/// Minimum recommended initialization key size in bytes.
	/// <para>Combined sizes of key, salt, and info should be at least this size.</para>
	/// </summary>
	virtual size_t MinKeySize() { return MIN_PASSLEN; }

	/// <summary>
	/// Get: Available Kdf Key Sizes in bytes
	/// </summary>
	virtual std::vector<SymmetricKeySize> LegalKeySizes() const { return m_legalKeySizes; };

	/// <summary>
	/// Get: The Kdf generators class name
	/// </summary>
	virtual const std::string Name() { return "SCRYPT"; }

	/// <summary>
	/// Get/Set: Parallel and SIMD capability flags and sizes 
	/// <para>The maximum number of threads allocated when using multi-threaded processing can be set with the ParallelMaxDegree() property.
	/// SIMD parallelization can be overriden using the SetSimdProfile(SimdProfiles) accessor, highest available value is chosen automatically.</para>
	/// </summary>
	ParallelOptions &ParallelProfile() { return m_parallelProfile; }

	//~~~Constructor~~~//

	/// <summary>
	/// Instantiates an SCRYPT generator using a message digest type-name
	/// </summary>
	/// 
	/// <param name="DigestType">The hash functions type-name enumeral</param>
	/// <param name="CpuCost">The CPU cost parameter; increasing this value affects the cpu and memory cost.
	/// <para>This value must be evenly divisible by 1024, with the minimum legal size of 1024. 
	/// The minimum recommended size is 16384.</para></param>
	/// <param name="Parallelization">The Parallelization parameter; indicates the number of threads used by the generator. 
	/// <para>Change this value to multiply the cpu cost by this factor, the default value is 1.
	/// Setting this value to 0 will automatically use the number of system processor cores.</para></param>
	/// 
	/// <exception cref="Exception::CryptoKdfException">Thrown if an invalid digest name or parameters are used</exception>
	explicit SCRYPT(Digests DigestType, size_t CpuCost = 16384, size_t Parallelization = 1);

	/// <summary>
	/// Instantiates an SCRYPT generator using a message digest instance
	/// </summary>
	/// 
	/// <param name="Digest">The initialized message digest instance</param>
	/// <param name="CpuCost">The CPU cost parameter; increasing this value affects the cpu and memory cost.
	/// <para>This value must be evenly divisible by 1024, with the minimum legal size of 1024. 
	/// The minimum recommended size is 16384.</para></param>
	/// <param name="Parallelization">The Parallelization parameter; indicates the number of threads used by the generator.  
	/// <para>Change this value to multiply the cpu cost by this factor, the default value is 1.
	/// Setting this value to 0 will automatically use the number of system processor cores.</para></param>
	/// 
	/// <exception cref="Exception::CryptoKdfException">Thrown if a null digest or invalid parameters are used</exception>
	explicit SCRYPT(IDigest* Digest, size_t CpuCost = 16384, size_t Parallelization = 1);

	/// <summary>
	/// Finalize objects
	/// </summary>
	virtual ~SCRYPT();

	//~~~Public Functions~~~//

	/// <summary>
	/// Release all resources associated with the object
	/// </summary>
	virtual void Destroy();

	/// <summary>
	/// Generate a block of pseudo random bytes
	/// </summary>
	/// 
	/// <param name="Output">Output array filled with random bytes</param>
	/// 
	/// <returns>The number of bytes generated</returns>
	virtual size_t Generate(std::vector<byte> &Output);

	/// <summary>
	/// Generate pseudo random bytes using offset and length parameters
	/// </summary>
	/// 
	/// <param name="Output">Output array filled with random bytes</param>
	/// <param name="OutOffset">The starting position within the Output array</param>
	/// <param name="Length">The number of bytes to generate</param>
	/// 
	/// <returns>The number of bytes generated</returns>
	virtual size_t Generate(std::vector<byte> &Output, size_t OutOffset, size_t Length);

	/// <summary>
	/// Initialize the generator with a SymmetricKey structure containing the key, and optional salt, and info string.
	/// <para>The use of a salt value mitigates some attacks against a passphrase, and is highly recommended with SCRYPT.</para>
	/// </summary>
	/// 
	/// <param name="GenParam">The SymmetricKey containing the generators keying material</param>
	virtual void Initialize(ISymmetricKey &GenParam);

	/// <summary>
	/// Initialize the generator with a key.
	/// <para>The use of a salt value mitigates some attacks against a passphrase, and is highly recommended with SCRYPT.</para>
	/// </summary>
	/// 
	/// <param name="Key">The primary key array used to seed the generator</param>
	/// 
	/// <exception cref="Exception::CryptoKdfException">Thrown if the key is too small</exception>
	virtual void Initialize(const std::vector<byte> &Key);

	/// <summary>
	/// Initialize the generator with key and salt arrays
	/// </summary>
	/// 
	/// <param name="Key">The primary key array used to seed the generator</param>
	/// <param name="Salt">The salt value containing an additional source of entropy</param>
	virtual void Initialize(const std::vector<byte> &Key, const std::vector<byte> &Salt);

	/// <summary>
	/// Initialize the generator with a key, a salt array, and an information string or nonce
	/// </summary>
	/// 
	/// <param name="Key">The primary key array used to seed the generator</param>
	/// <param name="Salt">The salt value used as an additional source of entropy</param>
	/// <param name="Info">The information string or nonce used as a third source of entropy</param>
	virtual void Initialize(const std::vector<byte> &Key, const std::vector<byte> &Salt, const std::vector<byte> &Info);

	/// <summary>
	/// Update the generators keying material
	/// </summary>
	///
	/// <param name="Seed">The new seed value array</param>
	/// 
	/// <exception cref="Exception::CryptoKdfException">Thrown if the seed is too small</exception>
	virtual void ReSeed(const std::vector<byte> &Seed);

	/// <summary>
	/// Reset the internal state; Kdf must be re-initialized before it can be used again
	/// </summary>
	virtual void Reset();

private:

	void BlockMix(std::vector<uint> &State, std::vector<uint> &Y);
	size_t Expand(std::vector<byte> &Output, size_t OutOffset, size_t Length);
	void Extract(std::vector<byte> &Output, size_t OutOffset, std::vector<byte> &Key, std::vector<byte> &Salt, size_t Length);
	void SalsaCore(std::vector<uint> &Output);
	void SalsaCoreW(std::vector<uint> &Output);
	void Scope();
	void SMix(std::vector<uint> &State, size_t StateOffset, size_t N);
};

NAMESPACE_KDFEND
#endif