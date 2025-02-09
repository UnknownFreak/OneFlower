#pragma once

namespace of::engine::courier
{
	enum class MessageType
	{
		DeltaTime,
		Notify,
		InputPressEvent,
		InputHoldEvent,
		InputReleaseEvent,
		InputAxisEvent,
	};
}

namespace courier
{
	using MessageType = of::engine::courier::MessageType;
}
