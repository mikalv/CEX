#ifndef CEX_DOCUMENTATION_H
#define CEX_DOCUMENTATION_H

#error Documentation only!

#include "CexDomain.h"

// start doxygen main //
/*! \mainpage A programmers guide to the CEX++ Cryptographic library

\section intro_sec Welcome
Welcome to the CEX++ Cryptographic Library, version 1.0.0.4 (A4).
\brief
CEX is a library built for both speed and maximum security.
This help package contains details on the cryptographic primitives used in the library, their uses, and code examples.

\section road_map Road Map
The current version is <B>1.0.0.4</B> (A4 version), which are the major, minor, patch, and release codes. \n
\brief

\author    John Underhill
\version   1.0.0.3
\date      July 04, 2017
\copyright GPL version 3 license (GPLv3)

<B>Trajectory</B> \n \n

The current version is 1.0.0.5 (A5 version), which are the major, minor, patch, and release codes. \n \n

<B>Current Release 1.0.0.5 (version A4):</B> \n
The ModuleLWE asymmetric cipher \n
The SHAKE XOF function \n
Full MISRA C++2014 compliant \n \n

<B>Planned Release 1.1.0.1</B> \n
RingLWE \n
McEliece \n
ModuleLWE \n
NTRU \n
Picnic \n
SPHINCS+ \n \n

<B>Planned Release 1.2.0.1</B> \n
TLS \n
STM-KEX \n
Android/iOS/Linux Compatability \n
DLL API \n \n

<B>History</B> \n \n

<B>Version 1.0.0.5, February 22, 2018</B> \n
Added the ModuleLWE asymmetric cipher \n
Added asymmetric cipher Encapsulate/Decapsulate api \n
Added the 128/256/512/1024 SHAKE XOF function \n
Updates to random providers and Prngs \n
The library is now Misra C++ 2014 compliant \n \n

<B>Version 1.0.0.4, November 11, 2017</B> \n
Added the McEliece asymmetric cipher \n
Added the 1024bit Keccak digest \n
Added the Poly1305 Message Authentication Code generator \n
The library is now SEI-CERT compliant (Misra compliance by 1.0.0.5) \n
Full coding standards sweep of the library \n
Integration of std::array and std::unique_ptr throughout \n
A full optimization cycle completed \n \n

<B>Version 1.0.0.3, June 30, 2017</B> \n
Added asymmetric cipher interfaces and framework \n
Added RingLWE asymmetric cipher \n
Added the Auto Collection seed Provider (ACP) \n
Addition of the HCR prng \n
Renaming of the drbgs to xCG format: BCG, DCG, and HCG; Block cipher Counter Generator, Digest and HMAC Counter Generators \n
Overhaul of SecureRandom and prng classes \n \n

<B>Version 1.0.0.2: April 23, 2017</B> \n
Last of 1.0 sweep of the symmetric library before the second half of the project engages, with thousands of changes made throughout, and the addition of (!experimental) AVX512 support. \n
Added a vectorized MemUtils class, with SIMD 128/256/512 copy, clear, set-value, and xor functions. \n
Integrated vectorized replacements for memcpy, xor, and memset throughout, including cipher mode support for AVX512, (I don't have a xeon to test this, maybe you can help?). \n
Reformatting of headers (inline accessors removed and the override hint added). \n
Many small TODOs finished, api synchronized, and formatting and documentation changes throughout. \n \n

<B>Version 1.0: March 28, 2017</B> \n
The first official release of the library, (ciphers and protocols are now tested, documented, and ready for deployment). \n
Completed Code and Help review cycles. \n
Added parallelized HMAC implementation. \n
Added multi-threaded Tree Hashing to all Skein and Keccak digest implementations. \n
Added SIMD parallelization to Skein512. \n
Rewrote SHA-2 paralellized tree hashing and added support for the SHA-NI SIMD to SHA-256. \n
Added a multi-threaded and SIMD parallelized implementation of the SCRYPT key derivation function. \n \n

\section intro_link Links
The CEX++ Help pages: http://www.vtdev.com/CEX-Plus/Help/html/index.html  \n
CEX++ on Github: https://github.com/Steppenwolfe65/CEX  \n
CEX .NET on Github: https://github.com/Steppenwolfe65/CEX-NET  \n
The Code Project article on CEX .NET: http://www.codeproject.com/Articles/828477/Cipher-EX-V
*/
// end doxygen main //



/*!
*  \addtogroup CEX
*  @{
*  @brief Root Namespace
*/
NAMESPACE_ROOT

	/*!
	*  \addtogroup Cipher
	*  @{
	*  @brief Cryptographic Cipher Namespace
	*/
	NAMESPACE_CIPHER

		/*!
		*  \addtogroup Asymmetric
		*  @{
		*  @brief Asymmetric Ciphers Namespace
		*/
		NAMESPACE_ASYMMETRIC

			/*!
			*  \addtogroup McEliece
			*  @{
			*  @brief The McEliece Cipher Namespace
			*/
			NAMESPACE_MCELIECE
				class McEliece {};
			NAMESPACE_MCELIECEEND
			/*! @} */

			/*!
			*  \addtogroup ModuleLWE
			*  @{
			*  @brief The McEliece Cipher Namespace
			*/
			NAMESPACE_MODULELWE
				class ModuleLWE {};
			NAMESPACE_MODULELWEEND
			/*! @} */

			/*!
			*  \addtogroup RingLWE
			*  @{
			*  @brief The RingLWE Cipher Namespace
			*/
			NAMESPACE_RINGLWE
				class RingLWE {};
			NAMESPACE_RINGLWEEND
			/*! @} */

		NAMESPACE_ASYMMETRICEND
		/*! @} */

		/*!
		*  \addtogroup Symmetric
		*  @{
		*  @brief Symmetric Cipher Namespace
		*/
		NAMESPACE_SYMMETRIC

		/*!
		*  \addtogroup Block
		*  @{
		*  @brief Symmetric Block Cipher Namespace
		*/
		NAMESPACE_BLOCK
			class AHX {};
			class IBlockCipher {};
			class RHX {};
			class SHX {};
			class THX {};

			/*!
			*  \addtogroup Mode
			*  @{
			*  @brief Symmetric Block Cipher Mode Namespace
			*/
			NAMESPACE_MODE
				class CBC {};
				class CFB {};
				class CTR {};
				class EAX {};
				class ECB {};
				class GCM {};
				class IAeadMode {};
				class ICipherMode {};
				class ICM {};
				class OCB {};
				class OFB {};
			NAMESPACE_MODEEND
			/*! @} */

			/*!
			*  \addtogroup Padding
			*  @{
			*  @brief Symmetric Block Cipher Padding Namespace
			*/
			NAMESPACE_PADDING
				class IPadding {};
				class ISO7816 {};
				class PKCS7 {};
				class TBC {};
				class X923 {};
				class ZeroPad {};
			NAMESPACE_PADDINGEND
			/*! @} */

		NAMESPACE_BLOCKEND
		/*! @} */

		/*!
		*  \addtogroup Stream
		*  @{
		*  @brief Symmetric Stream Cipher Namespace
		*/
		NAMESPACE_STREAM
			class IStreamCipher {};
			class ChaCha20 {};
			class Salsa20 {};
		NAMESPACE_STREAMEND
		/*! @} */

		NAMESPACE_SYMMETRICEND
		/*! @} */
	NAMESPACE_CIPHEREND
	/*! @} */

	/*!
	*  \addtogroup Common
	*  @brief Cipher Common Utilities
	*  @{
	*/
	NAMESPACE_COMMON
		class CipherDescription {};
		class CpuDetect {};
		class ParallelOptions {};
	NAMESPACE_COMMONEND
	/*! @} */

	/*!
	*  \addtogroup Digest
	*  @brief Cryptographic Hash Classes
	*  @{
	*/
	NAMESPACE_DIGEST
		class Blake512 {};
		class Blake256 {};
		class Blake2Params {};
		class IDigest {};
		class Keccak256 {};
		class Keccak512 {};
		class Keccak1024 {};
		class KeccakParams {};
		class SHA256 {};
		class SHA512 {};
		class SHA2Params {};
		class Skein256 {};
		class Skein512 {};
		class Skein1024 {};
		class SkeinParams {};
		class SkeinUbiTweak {};
		enum class SkeinUbiType {};
	NAMESPACE_DIGESTEND
	/*! @} */

	/*!
	*  \addtogroup Drbg
	*  @{
	*  @brief Deterministic Random Byte Generators
	*/
	NAMESPACE_DRBG
		class BCG {};
		class DCG {};
		class IDrbg {};
		class HCG {};
	NAMESPACE_DRBGEND
	/*! @} */

	/*!
	*  \addtogroup Enumeration
	*  @{
	*  @brief Cryptographic Enumerations
	*/
	NAMESPACE_ENUMERATION
		enum class AsymmetricEngines {};
		enum class BlockCiphers {};
		enum class BlockSizes {};
		enum class CipherModes {};
		enum class Digests {};
		enum class Drbgs {};
		enum class IVSizes {};
		enum class Kdfs {};
		enum class KeySizes {};
		enum class Macs {};
		enum class MPKCParams {};
		enum class PaddingModes {};
		enum class Prngs {};
		enum class Providers {};
		enum class RLWEParams {};
		enum class RoundCounts {};
		enum class SimdProfiles {};
		enum class StreamCiphers {};
		enum class StreamModes {};
		enum class SymmetricEngines {};
	NAMESPACE_ENUMERATIONEND
	/*! @} */

	/*!
	*  \addtogroup Exception
	*  @{
	*  @brief Cryptographic Exceptions
	*/
	NAMESPACE_EXCEPTION
		class CryptoAsymmetricException {};
		class CryptoCipherModeException {};
		class CryptoDigestException {};
		class CryptoException {};
		class CryptoGeneratorException {};
		class CryptoKdfException {};
		class CryptoMacException {};
		class CryptoPaddingException {};
		class CryptoProcessingException {};
		class CryptoRandomException {};
		class CryptoSymmetricCipherException {};
	NAMESPACE_EXCEPTIONEND
	/*! @} */

	/*!
	*  \addtogroup Helper
	*  @{
	*  @brief Cryptographic Helper Classes
	*/
	NAMESPACE_HELPER
		class BlockCipherFromName {};
		class CipherFromDescription {};
		class CipherModeFromName {};
		class DigestFromName {};
		class DrbgFromName {};
		class KdfFromName {};
		class MacFromDescription {};
		class PaddingFromName {};
		class PrngFromName {};
		class ProviderFromName {};
		class StreamCipherFromName {};
	NAMESPACE_HELPEREND
	/*! @} */

	/*!
	*  \addtogroup IO
	*  @{
	*  @brief IO Processors
	*/
	NAMESPACE_IO
		class BitConverter {};
		class FileStream {};
		class IByteStream {};
		class MemoryStream {};
		class SecureStream {};
		enum class SeekOrigin {};
		class StreamReader {};
		class StreamWriter {};
	NAMESPACE_IOEND
	/*! @} */

	/*!
	*  \addtogroup KDF
	*  @{
	*  @brief Key Derivation Functions
	*/
	NAMESPACE_KDF
		class HKDF {};
		class IKdf {};
		class KDF2 {};
		class PBKDF2 {};
		class SCRYPT {};
		class SHAKE {};
	NAMESPACE_KDFEND
	/*! @} */

	/*!
	*  \addtogroup Key
	*  @{
	*  @brief Cipher Keys
	*/
	NAMESPACE_KEY
		/*!
		*  \addtogroup AsymmetricKey
		*  @{
		*  @brief Asymmetric Key containers and generator
		*/
		NAMESPACE_ASYMMETRICKEY
			class IAsymmetricKey {};
			class IAsymmetricKeyPair {};
			class MPKCKeyPair {};
			class MPKCPrivateKey {};
			class MPKCPublicKey {};
			class RLWEKeyPair {};
			class RLWEPrivateKey {};
			class RLWEPublicKey {};
		NAMESPACE_ASYMMETRICKEYEND
		/*! @} */

		/*!
		*  \addtogroup SymmetricKey
		*  @{
		*  @brief Symmetric Key containers and generator
		*/
		NAMESPACE_SYMMETRICKEY
			class ISymmetricKey {};
			class SymmetricKeyGenerator {};
			class SymmetricKey {};
			class SymmetricKeySize {};
			class SymmetricSecureKey {};
		NAMESPACE_SYMMETRICKEYEND
		/*! @} */

	NAMESPACE_KEYEND
	/*! @} */

	/*!
	*  \addtogroup Mac
	*  @{
	*  @brief Message Authentication Code Generators
	*/
	NAMESPACE_MAC
		class CMAC {};
		class GMAC {};
		class HMAC {};
		class IMac {};
	NAMESPACE_MACEND
	/*! @} */

	//NAMESPACE_NETWORK
	//NAMESPACE_NETWORKEND

	/*!
	*  \addtogroup Numeric
	*  @{
	*  @brief SIMD and Big Integer Namespace
	*/
	NAMESPACE_NUMERIC
		class UInt128 {};
		class UInt256 {};
		class ULong256 {};
		class UInt512 {};
	NAMESPACE_NUMERICEND
	/*! @} */

	/*!
	*  \addtogroup Prng
	*  @{
	*  @brief Pseudo Random Number Generators
	*/
	NAMESPACE_PRNG
		class BCR {};
		class DCR {};
		class IPrng {};
		class PBR {};
		class SecureRandom {};
	NAMESPACE_PRNGEND
	/*! @} */

	/*!
	*  \addtogroup Processing
	*  @{
	*  @brief Cryptographic Processing Namespace
	*/
	NAMESPACE_PROCESSING
		class CipherDescription {};
		class CipherStream {};
		class DigestStream {};
		class MacDescription {};
		class MacStream {};
	NAMESPACE_PROCESSINGEND
	/*! @} */

	/*!
	*  \addtogroup Provider
	*  @{
	*  @brief Entropy source collectors and concentrators
	*/
	NAMESPACE_PROVIDER
		class CJP {};
		class CSP {};
		class ECP {};
		class IProvider {};
		class RDP {};
	NAMESPACE_PROVIDEREND
	/*! @} */

	/*!
	*  \addtogroup Event Routing
	*  @brief Library Events
	*  @{
	*/
	NAMESPACE_ROUTING
		class Delegate {};
		class Event {};
	NAMESPACE_ROUTINGEND
	/*! @} */

	/*!
	*  \addtogroup Utility
	*  @{
	*  @brief Library Utilities Classes
	*/
	NAMESPACE_UTILITY 
		class ArrayUtils {};
		class IntUtils {};
		class MemUtils {};
		class ParallelUtils {};
		class SysUtils {};
	NAMESPACE_UTILITYEND
	/*! @} */

NAMESPACE_ROOTEND
/*! @} */

#endif
