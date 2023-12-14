module;

export module word;

import <string>;
import <cstdint>;
import <ostream>;

namespace gartic
{
	export class Word
	{
	public:
		Word() = default;
		Word(const std::string& word, int difficulty);

		//Setteri
		void SetWord(const std::string& word) noexcept;
		void SetDifficulty(int difficulty) noexcept;

		//Getteri
		const std::string& GetWord() const noexcept;
		int GetDifficulty() const noexcept;
	private:
		std::string m_word;
		int m_difficulty;
	};
	export std::ostream& operator <<(std::ostream& os, const Word&);
}