export module round;
import <iostream>;
import<string>;

namespace gartic
{
	export class Round
	{
	public:
		Round();
		std::string GetHiddenWord() const;
	private:
		uint16_t GenerateHiddenWordIndex();
		std::string m_hiddenWord;
	};
}