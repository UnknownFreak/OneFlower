#ifndef TIMERCOMPONENT_HPP
#define TIMERCOMPONENT_HPP
#include "IBaseComponent.hpp"

namespace Component
{
	class Timer : public IBaseComponent < Timer >
	{
	public:
		~Timer();
		Timer(double timedLife);
		void update();
		// returns a pointer towards object if we can remove this.
		bool canRemove();
	protected:
		void attachOn(GameObject* attachTo);
	private:

		double timedLife;
		double currentTime;

		template < class Archive>//, GameObject& go>
		friend void save(Archive& archive, const Component::Timer& dc);
		template < class Archive>//, GameObject& go>
		friend void load(Archive& archive, Component::Timer& dc);
	};
}

#endif