#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include <Helpers/uuid.hpp>

namespace Trigger
{
	class Trigger
	{

	protected:

		virtual void executeInternal() = 0;

	public:

		bool triggerOnce;
		Core::uuid uuid;

		void execute();

		virtual std::unique_ptr<Trigger> clone() const = 0;


		template <class Archive>
		void save(Archive& ar) const
		{
			ar(triggerOnce);
			ar(uuid);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(triggerOnce);
			ar(uuid);
		}

	};
}

#endif // !TRIGGER_HPP
