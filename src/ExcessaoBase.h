#pragma once
#include <string>
#include <iostream>

/** Classe ExcessaoBase
  * @brief Usada no tratamento e lan�amento de excess�es no programa.
  * @note � uma classe base que n�o deve ser instanciada, apenas devem ser instanciadas as classes derivadas desta.
  */
class ExcessaoBase {
	private:
		/** @brief Raz�o pela qual a excess�o foi lan�ada. */
		std::string razao;
	public:
		/** @brief �nico construtor da classe. Aceita um argumento que � a raz�o pela qual a excess�o est� a ser lan�ada. */
		explicit ExcessaoBase(const std::string& razao);
		/** @brief Retorna a raz�o pela qual a excess�o foi lan�ada. 
		  * @return A raz�o pela qual a excess�o foi lan�ada. */
		const std::string& getReason() const;
		/** @brief Overloading do operador de inser��o. */
		friend std::ostream& operator<<(std::ostream& out, const ExcessaoBase& excessao);
};