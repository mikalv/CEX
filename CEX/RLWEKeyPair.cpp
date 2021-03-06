#include "RLWEKeyPair.h"

NAMESPACE_ASYMMETRICKEY

//~~~Constructor~~~//

RLWEKeyPair::RLWEKeyPair(RLWEPrivateKey* PrivateKey, RLWEPublicKey* PublicKey)
	:
	m_privateKey(PrivateKey),
	m_publicKey(PublicKey),
	m_Tag(0)
{
}

RLWEKeyPair::RLWEKeyPair(RLWEPrivateKey* PrivateKey, RLWEPublicKey* PublicKey, std::vector<byte> &Tag)
	:
	m_privateKey(PrivateKey),
	m_publicKey(PublicKey),
	m_Tag(Tag)
{
}

RLWEKeyPair::~RLWEKeyPair()
{
	Destroy();
}

//~~~Accessors~~~//

IAsymmetricKey* RLWEKeyPair::PrivateKey()
{
	return m_privateKey;
}

IAsymmetricKey* RLWEKeyPair::PublicKey()
{
	return m_publicKey;
}

std::vector<byte> &RLWEKeyPair::Tag()
{
	return m_Tag;
}

//~~~Private Functions~~~//

void RLWEKeyPair::Destroy()
{
	if (m_Tag.size() != 0)
	{
		m_Tag.clear();
	}
}

NAMESPACE_ASYMMETRICKEYEND
