#pragma once

#include <component/base.hpp>
#include <component/transform.hpp>

#include <glm/glm.hpp>

namespace of::component
{
	class Portal : public Base
	{
		
		virtual void onMessage(const of::object::messaging::Message& message) override;


		std::shared_ptr<of::component::Transform> mSelfTrackingPos;

		float mTeleportDistance;
		float mGuiHintDistance;

		virtual void initialize() override;
		virtual void deconstruct() override;


		of::file::FileId world;
		of::file::FileId loadingScreen;
		// change pos coordinates to player pos marker object, that once the zone is loaded will teleport the player to the marker position.
		of::file::FileId positionMarker;
		glm::vec3 teleportPos;
		bool requireInteraction;

		void teleport();

	public:

		Portal() = default;
		~Portal() = default;

		virtual Portal* copy() const override
		{
			return new Portal(*this);
		}

		virtual std::unique_ptr<Base> ucopy() const override
		{
			return std::make_unique<Portal>(*this);
		}

		void persist(of::object::ObjectSaveState*) override {};
		void onReconstruct(of::object::ObjectSaveState*) override {};
		void resolveReferences() override {};

		of::common::uuid getType() const override
		{
			return typeId;
		};

		of::common::String getTypeName() const override
		{
			return "Portal";
		};

		static constexpr of::common::uuid typeId = "9f11a5ca-5f3c-4d2c-8cf2-7dc57a62503c";
	};
}