#pragma once
#include <string>
#include <iostream>

/** Classe ExcessaoBase
  * @brief Usada no tratamento e lançamento de excessões no programa.
  * @note É uma classe base que não deve ser instanciada, apenas devem ser instanciadas as classes derivadas desta.
  */
class ExcessaoBase {
	private:
		/** @brief Razão pela qual a excessão foi lançada. */
		std::string razao;
	public:
		/** @brief Único construtor da classe. Aceita um argumento que é a razão pela qual a excessão está a ser lançada. */
		ExcessaoBase(const std::string& razao);
		/** @brief Retorna a razão pela qual a excessão foi lançada. 
		  * @return A razão pela qual a excessão foi lançada. */
		const std::string& getReason() const;
		/** @brief Overloading do operador de inserção. */
		friend std::ostream& operator<<(std::ostream& out, const ExcessaoBase& excessao);
};