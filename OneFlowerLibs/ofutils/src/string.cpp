#include <utils/common/string.hpp>
#include <locale>

namespace of::common
{
	String trim(const String& s)
	{
		auto start = s.begin();
		while (start != s.end() && std::isspace(*start, std::locale::classic())) {
			start++;
		}
		auto end = s.end();
		do {
			end--;
		} while (std::distance(start, end) > 0 && std::isspace(*end, std::locale::classic()));

		return String(start, end + 1);
	}

	String truncate(const String& theString, size_t max_size)
	{
		if (theString.size() > max_size + 3)
		{
			const size_t max_forward = max_size / 2;
			const size_t max_backwards = theString.size() - max_forward;
			String tmp;
			for (size_t i = 0; i < max_forward; i++)
			{
				tmp.push_back(theString[i]);
			}
			tmp += "...";
			for (size_t i = theString.size() - 1; i > max_backwards; i--)
			{
				tmp.push_back(theString[i]);
			}
			return tmp;
		}
		return theString;
	}

}