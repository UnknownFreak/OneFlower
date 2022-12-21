#pragma once

#include <utils/common/string.hpp>
#include <file/FileId.hpp>
#include "Topics.hpp"

namespace of::object::messaging
{

	class Topic
	{
		const of::common::String topic;

		inline Topic(const of::common::String& topic) : topic(topic) {}
	public:
		inline static Topic of(const of::common::String& topic) { return Topic(topic); };
		inline static Topic of(const Topics& type) { return Topic::of(to_string(type)); };

		inline bool operator==(const Topic& other) { return topic == other.topic; }

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
		FloatPtr( float * fp) : Body(BodyType::FLOAT_PTR), fp(fp) {}

		float * fp;
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