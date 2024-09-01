#pragma once
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

#include <utils/common/string.hpp>
#include <concepts>

namespace of::session
{
	class SaveState;

	template<class T>
	requires std::derived_from<T, SaveState>
	struct SaveStateTypeRef
	{
		static common::String type;
	};

	class SaveState
	{
		common::String stateType;

	protected:

		virtual common::String getType() const = 0;

	public:

		inline SaveState(const common::String& stateType) : stateType(stateType) {}

		virtual ~SaveState() = 0 {};

		inline bool isOfType(const common::String& type) const
		{
			return stateType == type;
		}

		template<class T>
		requires std::derived_from<T, SaveState>
		T* toDerived() const
		{
			return (T*)this;
		}

		template<class T>
		void save(T& ar) const
		{
			ar(stateType);
		}

		template<class T>
		void load(T& ar)
		{
			ar(stateType);
		}

	};
}
