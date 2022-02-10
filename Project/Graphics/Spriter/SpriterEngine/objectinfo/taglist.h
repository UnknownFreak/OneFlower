#ifndef TAGLIST_H
#define TAGLIST_H

#include <vector>
#include <Helpers/String.hpp>

namespace SpriterEngine
{
	typedef std::vector<const Core::String*> StringRefVector;

	class TagList
	{
	public:
		TagList();

		bool tagIsActive(Core::String tag) const;

		void pushBackTag(const Core::String *tag);

	private:
		StringRefVector tags;
	};
}

#endif // TAGLIST_H
