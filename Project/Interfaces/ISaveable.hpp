#ifndef ISaveAble_HPP
#define ISaveAble_HPP

namespace Interfaces
{

	class ISaveable
	{
	
	public:

		ISaveable() = default;
		virtual ~ISaveable() = default;

		template <class Archive>
		void save(Archive& saver) const = 0;

		template <class Archive>
		void load(Archive& loader) = 0;

		template <class Archive, class Saveable>
		void lazyloadsave(Archive& ar, Saveable& s)
		{
			ar(s);
		}

		template <class Archive, class Saveable>
		void lazyloadsaveconst(Archive& ar, const Saveable& s) const
		{
			ar(s);
		}
	};
}

#endif