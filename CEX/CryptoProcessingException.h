#ifndef CEX_CRYPTOPROCESSINGEXCEPTION_H
#define CEX_CRYPTOPROCESSINGEXCEPTION_H

#include "CexDomain.h"

NAMESPACE_EXCEPTION

/// <summary>
/// Generalized cryptographic error container
/// </summary>
struct CryptoProcessingException : std::exception
{
private:

	std::string m_details;
	std::string m_message;
	std::string m_origin;

public:

	//~~~Constructor~~~//

	/// <summary>
	/// Copy operator: copy is restricted, this function has been deleted
	/// </summary>
	CryptoProcessingException& operator=(const CryptoProcessingException&) = delete;

	/// <summary>
	/// Default constructor: default is restricted, this function has been deleted
	/// </summary>
	CryptoProcessingException() = delete;

	/// <summary>
	/// Constructor: instantiate this class with a message
	/// </summary>
	///
	/// <param name="Message">A custom message or error data</param>
	explicit CryptoProcessingException(const std::string &Message);

	/// <summary>
	/// Constructor: instantiate this class with an origin and message
	/// </summary>
	///
	/// <param name="Origin">The origin of the exception</param>
	/// <param name="Message">A custom message or error data</param>
	CryptoProcessingException(const std::string &Origin, const std::string &Message);

	/// <summary>
	/// Constructor: instantiate this class with an origin, message and inner exception
	/// </summary>
	///
	/// <param name="Origin">The origin of the exception</param>
	/// <param name="Message">A custom message or error data</param>
	/// <param name="Detail">The inner exception string</param>
	CryptoProcessingException(const std::string &Origin, const std::string &Message, const std::string &Detail);

	/// <summary>
	/// Destructor: finalize this class
	/// </summary>
	~CryptoProcessingException();

	//~~~Accessors~~~//

	/// <summary>
	/// Read/Write: The inner exception string
	/// </summary>
	std::string &Details();

	/// <summary>
	/// Read/Write: The message associated with the error
	/// </summary>
	std::string &Message();

	/// <summary>
	/// Read/Write: The origin of the exception in the format Class
	/// </summary>
	std::string &Origin();
};

NAMESPACE_EXCEPTIONEND
#endif
