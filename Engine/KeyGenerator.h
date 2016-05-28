#ifndef _CEXENGINE_KEYGENERATOR_H
#define _CEXENGINE_KEYGENERATOR_H

#include "Common.h"
#include "CryptoGeneratorException.h"
#include "IDigest.h"
#include "ISeed.h"
#include "KeyParams.h"

NAMESPACE_COMMON

/// <summary>
/// A helper class for generating cryptographically strong keying material.
/// <para>Generates an array or a populated KeyParams class, using a definable Digest(Prng()) dual stage generator.
/// The first stage of the generator gets seed material from the Prng provider, the second hashes the seed and adds the result to the state array.
/// A counter array can be prepended to the seed array, sized between 4 and 32 bytes. 
/// The counter is incremented and prepended to the seed value before each hash call. 
/// If the Counter size parameter is <c>0</c> in the constructor, or the default constructor is used, 
/// the counter is provided by the default random provider.</para>
/// </summary>
/// 
/// <example>
/// <description>Create an array of pseudo random keying material:</description>
/// <code>
/// KeyGenerator* gen = new KeyGenerator([Prng], [Digest], [Counter Size]))
/// // generate pseudo random bytes
/// std:vector&lt;byte&gt; prnd = gen.Generate(Size);
/// </code>
/// </example>
/// 
/// <seealso cref="CEX::Digest::IDigest"/>
/// <seealso cref="CEX::Enumeration::Digests"/>
/// <seealso cref="CEX::Seed"/>
/// <seealso cref="CEX::Seed::ISeed "/>
/// <seealso cref="CEX::Enumeration::SeedGenerators"/>
/// 
/// <remarks>
/// <description>Implementation Notes:</description>
/// <list type="bullet">
/// <item><description>SHA-2 Generates key material using a two stage Hmac_k(Prng()) process.</description></item>
/// <item><description>Blake, Keccak, and Skein also use a two stage generation method; Hash(Prng()).</description></item>
/// <item><description>Seed provider can be any of the <see cref="CEX::Enumeration::SeedGenerators"/> generators.</description></item>
/// <item><description>Hash can be any of the <see cref="CEX::Enumeration::Digests"/> digests.</description></item>
/// <item><description>Default Prng is CSPPrng, default digest is SHA512.</description></item>
/// <item><description>Resources are disposed of automatically.</description></item>
/// </list>
/// </remarks>
class KeyGenerator
{
private:
	static constexpr uint DEFCTR_SIZE = 32;

	uint _ctrLength;
	std::vector<byte> _ctrVector;
	CEX::Enumeration::Digests _dgtType;
	CEX::Digest::IDigest* _hashEngine;
	bool _isDestroyed;
	CEX::Enumeration::SeedGenerators _rngType;
	CEX::Seed::ISeed* _seedEngine;

public:
	/// <summary>
	/// Initialize this class.
	/// <para>Initializes the class with default generators; SHA-2 512, and CSPPrng.
	/// The digest counter mechanism is set to <c>O</c> (disabled) by default.</para>
	/// </summary>
	/// 
	/// <param name="SeedType">The Seed Generators that supplies the seed material to the hash function</param>
	/// <param name="DigestType">The Digest type used to post-process the pseudo random seed material</param>
	KeyGenerator(CEX::Enumeration::SeedGenerators SeedType = CEX::Enumeration::SeedGenerators::CSPRsg, CEX::Enumeration::Digests DigestType = CEX::Enumeration::Digests::SHA512)
		:
		_ctrLength(0),
		_ctrVector(0),
		_dgtType(DigestType),
		_isDestroyed(false),
		_rngType(SeedType)
	{
		// initialize the generators
		Reset();
	}

	/// <summary>
	/// Initialize the class and generators
	/// </summary>
	/// 
	/// <param name="SeedType">The Seed generator that supplies the seed material to the hash function</param>
	/// <param name="DigestType">The Digest type used to post-process the pseudo random seed material</param>
	/// <param name="Counter">The user supplied counter variable in bytes; setting to a <c>0</c> value, produces a counter generated by the default random provider; 
	/// valid values are <c>0</c>, or between <c>4-32</c> bytes</param>
	/// 
	/// <exception cref="CEX::Exception::CryptoGeneratorException">Thrown if the counter is not <c>0</c>, or a value between <c>4</c> and <c>32</c></exception>
	KeyGenerator(const CEX::Enumeration::SeedGenerators SeedType, const CEX::Enumeration::Digests DigestType, const std::vector<byte> &Counter)
		:
		_ctrLength((uint)Counter.size()),
		_ctrVector(Counter),
		_dgtType(DigestType),
		_isDestroyed(false),
		_rngType(SeedType)
	{
		if (Counter.size() > 32 || (Counter.size() < 4 && Counter.size() != 0))
			throw CEX::Exception::CryptoGeneratorException("KeyGenerator:Ctor", "The counter size must be either 0, or between 4 and 32 bytes!");

		// initialize the generators
		Reset();
	}

	/// <summary>
	/// Destructor
	/// </summary>
	~KeyGenerator()
	{
		Destroy();
	}

	/// <summary>
	/// Release all resources associated with the object
	/// </summary>
	void Destroy();

	/// <summary>
	/// Create a populated KeyParams class
	/// </summary>
	/// 
	/// <param name="KeySize">Size of Key to generate in bytes</param>
	/// <param name="IVSize">Size of IV to generate in bytes</param>
	/// <param name="IKMSize">Size of IKM to generate in bytes</param>
	/// 
	/// <returns>A populated <see cref="CEX::Common::KeyParams"/> class</returns>
	CEX::Common::KeyParams* GetKeyParams(const uint KeySize, const uint IVSize = 0, uint IKMSize = 0);

	/// <summary>
	/// Fill an array with pseudo random bytes
	/// </summary>
	/// 
	/// <param name="Data">Array to fill with random bytes</param>
	void GetBytes(std::vector<byte> &Data);

	/// <summary>
	/// Return an array with pseudo random bytes
	/// </summary>
	/// 
	/// <param name="Size">Size of requested byte array</param>
	/// 
	/// <returns>Random byte array</returns>
	std::vector<byte> GetBytes(uint Size);

	/// <summary>
	/// Reset the seed Seed Generators and the Digest engine
	/// </summary>
	void Reset();

private:
	std::vector<byte> Generate(size_t Size);
	std::vector<byte> GetBlock();
	CEX::Digest::IDigest* GetDigestEngine(CEX::Enumeration::Digests DigsetType);
	CEX::Seed::ISeed* GetSeedEngine(CEX::Enumeration::SeedGenerators SeedType);
	void Increment(std::vector<byte> &Counter);
};

NAMESPACE_COMMONEND
#endif