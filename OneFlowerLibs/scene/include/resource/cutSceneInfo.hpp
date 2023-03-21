#pragma once
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>


#include <file/archive/Requestable.hpp>

#include <vector>
#include <memory>

namespace of::resource
{

	class TrackEvent
	{
		bool fired = false;
		bool ended = false;

		float delta;

	public:

		float mEventStartTime;
		float mEventCurrentTime;
		float mEventEndTime;

		float getTimeDelta()
		{
			return delta;
		}

		bool hasEventFired()
		{
			return fired;
		}

		bool canEventFire()
		{
			return mEventCurrentTime > mEventStartTime && mEventCurrentTime < mEventEndTime && hasEventFired() == false;
		}

		bool canEventEnd()
		{
			return mEventCurrentTime >= mEventEndTime && hasEventEnded() == false;
		}

		bool hasEventEnded()
		{
			return ended;
		}

		void fireEvent()
		{
			fired = true;
			fireEventInternal();
		}

		void endEvent()
		{
			ended = true;
			endEventInternal();
		}

		void reset()
		{
			fired = false;
			ended = false;
		}

		void update(const float& currentTrackTime)
		{
			delta = currentTrackTime - mEventCurrentTime;
			mEventCurrentTime = currentTrackTime;
			if (canEventFire())
			{
				fireEvent();
			}
			if (hasEventFired() && hasEventEnded() == false)
			{
				updateInternal();
				if (canEventEnd())
				{
					endEvent();
				}
			}
		};

		void skip()
		{
			if (hasEventFired() && hasEventEnded() == false)
			{
				endEvent();
			}
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(mEventEndTime);
			ar(mEventStartTime);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(mEventEndTime);
			ar(mEventStartTime);
		}

		virtual void updateInternal() = 0;
		virtual void fireEventInternal() = 0;
		virtual void endEventInternal() = 0;
	};

	struct Track
	{

		std::vector<std::shared_ptr<TrackEvent>> events;

		float mTrackActiveFrameStart;
		float mTrackLength;
		float mTrackCurrentTime = 0.f;

		bool isTimeWithinFrame()
		{
			return mTrackCurrentTime > mTrackActiveFrameStart;
		}

		bool isTrackFinshed()
		{
			return mTrackCurrentTime >= mTrackLength;
		}

		void update(const float& currentTrackTime)
		{
			mTrackCurrentTime = currentTrackTime;
			if (isTimeWithinFrame() && isTrackFinshed() == false)
			{
				for (auto& event : events)
				{
					event->update(mTrackCurrentTime);
				}
			}
		}

		void reset()
		{
			for (auto& event : events)
			{
				event->reset();
			}
		}

		void skip()
		{
			for (auto& event : events)
			{
				event->skip();
			}
		}

		template<class Archive>
		void save(Archive& ar) const
		{
			ar(mTrackActiveFrameStart);
			ar(mTrackLength);
			ar(events);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(mTrackActiveFrameStart);
			ar(mTrackLength);
			ar(events);
		}
	};

	struct CutSceneInfo : public of::file::archive::Requestable
	{
		float mCurrentTime = 0.f;
		float mCutSceneLength;
		std::vector<Track> tracks;

		bool update(const float& dt);
		void skip();
		bool isFinished();
		void reset();
		virtual of::file::archive::TypeInfo getTrait() const override;


		template<class Archive>
		void save(Archive& ar) const
		{
			ar(mCutSceneLength);
			ar(tracks);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			ar(mCutSceneLength);
			ar(tracks);
		}
	};
}

CEREAL_REGISTER_TYPE(of::resource::CutSceneInfo);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, of::resource::CutSceneInfo);