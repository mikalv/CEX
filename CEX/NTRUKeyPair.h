#ifndef CEX_NTRUKEYPAIR_H
#define CEX_NTRUKEYPAIR_H

#include "CexDomain.h"
#include "IAsymmetricKeyPair.h"
#include "NTRUPrivateKey.h"
#include "NTRUPublicKey.h"

NAMESPACE_ASYMMETRICKEY

/// <summary>
/// A NTRU public and private key container
/// </summary>
class NTRUKeyPair final : public IAsymmetricKeyPair
{
private:

	NTRUPrivateKey* m_privateKey;
	NTRUPublicKey* m_publicKey;
	std::vector<byte> m_Tag;

public:

	//~~~Constructor~~~//

	/// <summary>
	/// Copy constructor: copy is restricted, this function has been deleted
	/// </summary>
	NTRUKeyPair(const NTRUKeyPair&) = delete;

	/// <summary>
	/// Copy operator: copy is restricted, this function has been deleted
	/// </summary>
	NTRUKeyPair& operator=(const NTRUKeyPair&) = delete;

	/// <summary>
	/// Default constructor: default is restricted, this function has been deleted
	/// </summary>
	NTRUKeyPair() = delete;

	/// <summary>
	/// Constructor: instantiate this class with the public/private keys
	/// </summary>
	/// 
	/// <param name="PrivateKey">The private key</param>
	/// <param name="PublicKey">The public key</param>
	NTRUKeyPair(NTRUPrivateKey* PrivateKey, NTRUPublicKey* PublicKey);

	/// <summary>
	/// Constructor: instantiate this class with the public/private keys and an identification tag
	/// </summary>
	/// 
	/// <param name="PrivateKey">The private key</param>
	/// <param name="PublicKey">The public key</param>
	/// <param name="Tag">The identification tag</param>
	NTRUKeyPair(NTRUPrivateKey* PrivateKey, NTRUPublicKey* PublicKey, std::vector<byte> &Tag);

	/// <summary>
	/// Destructor: finalize this class.
	/// <para>Only the tag is destroyed in the finalizer. Call the Destroy() function on Public/Private key members,
	/// or let them go out of scope to finalize them.</para>
	/// </summary>
	~NTRUKeyPair() override;

	//~~~Accessors~~~//

	/// <summary>
	/// The secret private Key
	/// </summary>
	IAsymmetricKey* PrivateKey() override;

	/// <summary>
	/// The public key
	/// </summary>
	IAsymmetricKey* PublicKey() override;

	/// <summary>
	/// Read/Write: An optional identification tag
	/// </summary>
	std::vector<byte> &Tag() override;

private:

	void Destroy();
};

NAMESPACE_ASYMMETRICKEYEND
#endif

