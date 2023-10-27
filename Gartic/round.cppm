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
		uint16_t GenerateHiddenWordIndex() const;
		std::string m_hiddenWord;
		static const uint16_t kWordNumber=499;
	};
}