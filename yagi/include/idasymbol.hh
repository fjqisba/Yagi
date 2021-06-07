#ifndef __YAGI_IDASYMBOLFACTORY__
#define __YAGI_IDASYMBOLFACTORY__

#include "symbolinfo.hh"

namespace yagi 
{
	/*!
	 * \brief	Symbol database interface from IDA to Yagi 
	 */
	class IdaSymbolInfo : public SymbolInfo 
	{
	public:
		/*!
		 *	\brief	ctor
		 */
		explicit IdaSymbolInfo(uint64_t ea, std::string name);

		/*!
		 * \brief	default ctor 
		 */
		~IdaSymbolInfo() = default;

		/*!
		 *	\brief	Copy is authorized because we only use copyable type
		 */
		IdaSymbolInfo(const IdaSymbolInfo&) = default;
		IdaSymbolInfo& operator=(const IdaSymbolInfo&) = default;

		/*!
		 *	\brief	moving is allowed
		 */
		IdaSymbolInfo(IdaSymbolInfo&&) noexcept = default;
		IdaSymbolInfo& operator=(IdaSymbolInfo&&) noexcept = default;

		/*!
		 *	\brief	if symbol refer to a function compute the size of the symbol
		 *	\return	the size of the symbol
		 *	\raise	SymbolIsNotAFunction
		 */
		uint64_t getFunctionSize() const override;

		/*!
		 * \brief	override the default name
		 *			with IDA API
		 */
		std::string getName() const override;

		/*!
		 *	\brief	state of symbol
		 *	\return	true if the symbol is a function
		 */
		bool isFunction() const noexcept override;

		/*!
		 *	\brief	state of the function
		 *	\return	true if symbol is associated to a symbol
		 */
		bool isLabel() const noexcept override;

		/*!
		 *	\brief	state of the symbol
		 *	\return	true the symbol is associate to an import
		 */
		bool isImport() const noexcept override;

		/*!
		 *	\brief	Is the symbol is in Read only mode
		 *			Use to espand static data from read only memory space
		 */
		bool isReadOnly() const noexcept override;
	};

	/*!
	 * \brief	Factory for IDA symbol
	 */
	class IdaSymbolInfoFactory : public SymbolInfoFactory
	{
	public:
		/*!
		 * \brief	ctor 
		 */
		IdaSymbolInfoFactory() = default;

		/*!
		 * \brief	destructor
		 */
		~IdaSymbolInfoFactory() = default;

		/*!
		 * \brief	Find any symbol at a particular address
		 *			This is the implementation for IDA
		 * \param	ea	the address of the symbol
		 * \return	optional symbol if found into database
		 */
		std::optional<std::unique_ptr<SymbolInfo>> find(uint64_t ea) override;

		/*!
		 * \brief	Find a function symbol from an address anywhere in the function
		 *			This is the implementation for IDA
		 * \param	ea	any address that is handle by a function
		 */
		std::optional<std::unique_ptr<SymbolInfo>> find_function(uint64_t ea) override;
	};
}

#endif