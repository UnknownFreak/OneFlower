#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include <cereal/cereal.hpp>
#include <utils/common/uuid.hpp>

namespace of::trigger
{
	class Trigger
	{

	protected:

		virtual void executeInternal() = 0;

	public:


		inline virtual ~Trigger() {};

		bool triggerOnce;
		of::common::uuid uuid;

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
