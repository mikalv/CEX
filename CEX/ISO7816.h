#ifndef CEX_ISO7816_H
#define CEX_ISO7816_H

#include "IPadding.h"

NAMESPACE_PADDING

/// <summary>
/// The ISO7816 Padding Scheme
/// </summary>
///
/// <remarks>
/// <description>Guiding Publications:</description>
/// <list type="number">
/// <item><description>ISO/IEC <a href="http://www.iso.org/iso/home/store/catalogue_tc/catalogue_detail.htm?csnumber=36134">7816-4:2005</a>.</description></item>
/// </list>
/// </remarks>
class ISO7816 final : public IPadding
{
private:

	static const std::string CLASS_NAME;
	static const byte MKCODE = 0x80;
	static const byte ZBCODE = 0x00;

public:

	//~~~Constructor~~~//

	/// <summary>
	/// Copy constructor: copy is restricted, this function has been deleted
	/// </summary>
	ISO7816(const ISO7816&) = delete;

	/// <summary>
	/// Copy operator: copy is restricted, this function has been deleted
	/// </summary>
	ISO7816& operator=(const ISO7816&) = delete;

	/// <summary>
	/// Constructor: instantiate this class
	/// </summary>
	ISO7816();

	/// <summary>
	/// Destructor: finalize this class: finalize this class
	/// </summary>
	~ISO7816() override;

	//~~~Accessors~~~//

	/// <summary>
	/// Read Only: The padding modes type name
	/// </summary>
	const PaddingModes Enumeral() override;

	/// <summary>
	/// Read Only: The padding modes class name
	/// </summary>
	const std::string Name() override;

	//~~~Public Functions~~~//

	/// <summary>
	/// Add padding to input array
	/// </summary>
	///
	/// <param name="Input">Array to modify</param>
	/// <param name="Offset">Offset into array</param>
	///
	/// <returns>Length of padding</returns>
	///
	/// <exception cref="Exception::CryptoPaddingException">Thrown if the padding offset value is longer than the array length</exception>
	size_t AddPadding(std::vector<byte> &Input, size_t Offset) override;

	/// <summary>
	/// Get the length of padding in an array
	/// </summary>
	///
	/// <param name="Input">Padded array of bytes</param>
	///
	/// <returns>Length of padding</returns>
	size_t GetPaddingLength(const std::vector<byte> &Input) override;

	/// <summary>
	/// Get the length of padding in an array
	/// </summary>
	///
	/// <param name="Input">Padded array of bytes</param>
	/// <param name="Offset">Offset into array</param>
	///
	/// <returns>Length of padding</returns>
	size_t GetPaddingLength(const std::vector<byte> &Input, size_t Offset) override;
};

NAMESPACE_PADDINGEND
#endif

