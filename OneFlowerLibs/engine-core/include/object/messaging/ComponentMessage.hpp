#pragma once

#include <utils/common/string.hpp>
#include <file/FileId.hpp>
#include "Topics.hpp"

namespace of::object
{
	class GameObject;

	namespace messaging
	{

		class Topic
		{
			const std::string_view topic;

			inline consteval Topic(const of::common::String& topic) : topic(topic) {}
			inline consteval Topic(const std::string_view& topic) : topic(topic) {}
		public:
			inline static consteval Topic of(const of::common::String& topic) { return Topic(topic); };
			inline static consteval Topic of(const Topics& topic) { return Topic(to_string(topic)); };

			inline bool operator==(const Topic& other) const { return topic == other.topic; }

		};

		struct Body
		{
			inline Body() : Body(BodyType::NONE) {}
			inline Body(const BodyType& bodyType) : bodyType(bodyType) {}

			BodyType bodyType = BodyType::NONE;

			virtual ~Body() = default;
		};

		struct FileIdBody : public Body
		{
			FileIdBody(const file::FileId& fileId) : Body(BodyType::FILE_ID), fileId(fileId) {}
			file::FileId fileId;
		};

		struct ModifierId : public Body
		{
			ModifierId(const file::FileId& fileId, const float& duration) : Body(BodyType::MODIFIER_ID), fileId(fileId), duration(duration), infinite(duration <= 0) {}

			file::FileId fileId;
			float duration;
			bool infinite;
		};

		struct FloatPtr : public Body
		{
			FloatPtr(float* fp) : Body(BodyType::FLOAT_PTR), fp(fp) {}

			float* fp;
		};

		struct GameObjectPtr : public Body
		{
			GameObjectPtr(const GameObject* go) : Body(BodyType::GAMEOBJECT_PTR), go(go) {}
			const GameObject* go;
		};

		struct StringBody : public Body
		{
			StringBody(const of::common::String& s) : Body(BodyType::STRING), s(s) {}
			of::common::String s;
		};

		struct Custom : public Body
		{
			inline Custom() : Body(BodyType::CUSTOM) {};
			virtual ~Custom() = default;
		};

		struct Message
		{
			Topic messageTopic;

			std::shared_ptr<Body> messageBody;

		};
	};
};