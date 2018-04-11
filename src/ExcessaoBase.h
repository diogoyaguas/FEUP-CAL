#pragma once
#include <string>
#include <iostream>

/** Classe ExcessaoBase
  * @brief Used in handling exceptions
  *
  */
class ExcessaoBase {
	private:
		/** @brief Reason why the exception was launched */
		std::string razao;
	public:
		/**
		 * @brief Constructor
		 * @param razao
		 */
		explicit ExcessaoBase(const std::string& razao);
		/** @brief Returns the reason why the exception was launched
		  * @return string - reason */
		const std::string& getReason() const;
		/** @brief Overloading of the operator << */
		friend std::ostream& operator<<(std::ostream& out, const ExcessaoBase& excessao);
};