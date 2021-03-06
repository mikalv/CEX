#include "CSR.h"
#include "IntUtils.h"
#include "ProviderFromName.h"

NAMESPACE_PRNG

const std::string CSR::CLASS_NAME("CSR");

//~~~Accessors~~~//

const Prngs CSR::Enumeral()
{
	return Prngs::CSR;
}

const std::string CSR::Name()
{
	return CLASS_NAME + "-" + m_rngGenerator->Name();
}

//~~~Constructor~~~//

CSR::CSR(ShakeModes ShakeMode, Providers SeedEngine, size_t BufferSize)
	:
	m_bufferIndex(0),
	m_isDestroyed(false),
	m_pvdType(SeedEngine),
	m_rndSeed(0),
	m_rngBuffer(BufferSize != 0 ? BufferSize : (ShakeMode == ShakeModes::SHAKE128) ? 168 : (ShakeMode == ShakeModes::SHAKE256) ? 136 : 72),
	m_rngGenerator(new Drbg::CSG(ShakeMode, SeedEngine)),
	m_shakeType(ShakeMode != ShakeModes::None ? ShakeMode :
		throw CryptoRandomException("CSR:Ctor", "SHAKE type can not be none!"))
{
	Reset();
}

CSR::CSR(std::vector<byte> Seed, ShakeModes ShakeMode, size_t BufferSize)
	:
	m_bufferIndex(0),
	m_isDestroyed(false),
	m_pvdType(Providers::ACP),
	m_rndSeed(Seed),
	m_rngBuffer(BufferSize != 0 ? BufferSize : (ShakeMode == ShakeModes::SHAKE128) ? 168 : (ShakeMode == ShakeModes::SHAKE256) ? 136 : 72),
	m_rngGenerator(new Drbg::CSG(ShakeMode, Providers::None)),
	m_shakeType(ShakeMode != ShakeModes::None ? ShakeMode :
		throw CryptoRandomException("CSR:Ctor", "SHAKE type can not be none!"))
{
	Reset();
}

CSR::~CSR()
{
	if (!m_isDestroyed)
	{
		m_isDestroyed = true;
		m_bufferIndex = 0;
		m_shakeType = ShakeModes::None;
		m_pvdType = Providers::None;

		Utility::IntUtils::ClearVector(m_rndSeed);
		Utility::IntUtils::ClearVector(m_rngBuffer);

		if (m_rngGenerator != nullptr)
		{
			m_rngGenerator.reset(nullptr);
		}
	}
}

//~~~Public Functions~~~//

void CSR::Fill(std::vector<int16_t> &Output, size_t Offset, size_t Elements)
{
	CexAssert(Output.size() - Offset <= Elements, "the output array is too short");

	size_t bufLen = Elements * sizeof(int16_t);
	std::vector<byte> buf(bufLen);
	GetBytes(buf);
	Utility::MemUtils::Copy(buf, 0, Output, Offset, bufLen);
}

void CSR::Fill(std::vector<ushort> &Output, size_t Offset, size_t Elements)
{
	CexAssert(Output.size() - Offset <= Elements, "the output array is too short");

	size_t bufLen = Elements * sizeof(ushort);
	std::vector<byte> buf(bufLen);
	GetBytes(buf);
	Utility::MemUtils::Copy(buf, 0, Output, Offset, bufLen);
}

void CSR::Fill(std::vector<int32_t> &Output, size_t Offset, size_t Elements)
{
	CexAssert(Output.size() - Offset <= Elements, "the output array is too short");

	size_t bufLen = Elements * sizeof(int32_t);
	std::vector<byte> buf(bufLen);
	GetBytes(buf);
	Utility::MemUtils::Copy(buf, 0, Output, Offset, bufLen);
}

void CSR::Fill(std::vector<uint> &Output, size_t Offset, size_t Elements)
{
	CexAssert(Output.size() - Offset <= Elements, "the output array is too short");

	size_t bufLen = Elements * sizeof(uint);
	std::vector<byte> buf(bufLen);
	GetBytes(buf);
	Utility::MemUtils::Copy(buf, 0, Output, Offset, bufLen);
}

void CSR::Fill(std::vector<int64_t> &Output, size_t Offset, size_t Elements)
{
	CexAssert(Output.size() - Offset <= Elements, "the output array is too short");

	size_t bufLen = Elements * sizeof(int64_t);
	std::vector<byte> buf(bufLen);
	GetBytes(buf);
	Utility::MemUtils::Copy(buf, 0, Output, Offset, bufLen);
}

void CSR::Fill(std::vector<ulong> &Output, size_t Offset, size_t Elements)
{
	CexAssert(Output.size() - Offset <= Elements, "the output array is too short");

	size_t bufLen = Elements * sizeof(ulong);
	std::vector<byte> buf(bufLen);
	GetBytes(buf);
	Utility::MemUtils::Copy(buf, 0, Output, Offset, bufLen);
}

std::vector<byte> CSR::GetBytes(size_t Length)
{
	std::vector<byte> rnd(Length);
	GetBytes(rnd);

	return rnd;
}

void CSR::GetBytes(std::vector<byte> &Output, size_t Offset, size_t Length)
{
	CexAssert(Offset + Length <= Output.size(), "the array is too small to fulfill this request");

	std::vector<byte> rnd = GetBytes(Length);
	Utility::MemUtils::Copy(rnd, 0, Output, Offset, Length);
}

void CSR::GetBytes(std::vector<byte> &Output)
{
	CexAssert(Output.size() != 0, "buffer size must be at least 1 in length");

	if (m_rngBuffer.size() - m_bufferIndex < Output.size())
	{
		size_t bufSize = m_rngBuffer.size() - m_bufferIndex;

		// copy remaining bytes
		if (bufSize != 0)
		{
			Utility::MemUtils::Copy(m_rngBuffer, m_bufferIndex, Output, 0, bufSize);
		}

		size_t rmd = Output.size() - bufSize;

		while (rmd > 0)
		{
			// fill buffer
			m_rngGenerator->Generate(m_rngBuffer);

			if (rmd > m_rngBuffer.size())
			{
				Utility::MemUtils::Copy(m_rngBuffer, 0, Output, bufSize, m_rngBuffer.size());
				bufSize += m_rngBuffer.size();
				rmd -= m_rngBuffer.size();
			}
			else
			{
				Utility::MemUtils::Copy(m_rngBuffer, 0, Output, bufSize, rmd);
				m_bufferIndex = rmd;
				rmd = 0;
			}
		}
	}
	else
	{
		Utility::MemUtils::Copy(m_rngBuffer, m_bufferIndex, Output, 0, Output.size());
		m_bufferIndex += Output.size();
	}
}

ushort CSR::NextUInt16()
{
	ushort x = 0;
	Utility::MemUtils::CopyToValue(GetBytes(sizeof(ushort)), 0, x, sizeof(ushort));

	return x;
}

uint CSR::NextUInt32()
{
	uint x = 0;
	Utility::MemUtils::CopyToValue(GetBytes(sizeof(uint)), 0, x, sizeof(uint));

	return x;
}

ulong CSR::NextUInt64()
{
	ulong x = 0;
	Utility::MemUtils::CopyToValue(GetBytes(sizeof(ulong)), 0, x, sizeof(ulong));

	return x;
}

void CSR::Reset()
{
	if (m_rndSeed.size() != 0)
	{
		m_rngGenerator->Initialize(m_rndSeed);
	}
	else
	{
		Provider::IProvider* seedGen = Helper::ProviderFromName::GetInstance(m_pvdType == Providers::None ? Providers::CSP : m_pvdType);
		std::vector<byte> seed(m_rngGenerator->LegalKeySizes()[1].KeySize());
		seedGen->GetBytes(seed);
		delete seedGen;
		m_rngGenerator->Initialize(seed);
	}

	m_rngGenerator->Generate(m_rngBuffer);
	m_bufferIndex = 0;
}

NAMESPACE_PRNGEND
