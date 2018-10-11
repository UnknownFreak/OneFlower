#ifndef LoadZoneComponent_HPP
#define LoadZoneComponent_HPP

#include <Core\Component\IBaseComponent.hpp>
#include <Core\Vector.h>

namespace Component
{
	class Portal : public IBaseComponent<Portal>
	{
		std::pair<Core::String, size_t> zoneToLoadID;
		Core::Vector2 posToPlaceCharacter;

		void loadZone();
		
		bool loadZoneOnHitboxContact = true;
	protected:
		void attachOn(GameObject* go);
	public:
		Portal();
		Portal(const Portal& copy);
		Portal& operator=(const Portal& right);

		void onCollision(Physics::Collider&);
		void getMessage(const BaseMessage message);

		virtual Portal* copy() const;

		template<class Archive>
		void save(Archive & ar) const
		{
			ar(zoneToLoadID.first);
			ar(zoneToLoadID.second);
			ar(posToPlaceCharacter);
			ar(loadZoneOnHitboxContact);
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar(zoneToLoadID.first);
			ar(zoneToLoadID.second);
			ar(posToPlaceCharacter);
			ar(loadZoneOnHitboxContact);
		}
	};
}


#endif