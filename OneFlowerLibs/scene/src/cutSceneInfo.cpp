#include <resource/cutSceneInfo.hpp>

of::common::uuid of::file::archive::Trait<of::resource::CutSceneInfo>::typeId = of::common::uuid("32bc48e1-08c6-483b-804c-c20df627c702");

namespace of::resource
{
	bool CutSceneInfo::update(const float& dt)
	{
		mCurrentTime += dt;
		for (auto& track : tracks)
		{
			if (track.isTrackFinshed() == false)
			{
				track.update(mCurrentTime);
			}
		}
		return isFinished();
	}

	void CutSceneInfo::skip()
	{
		mCurrentTime = mCutSceneLength;
	}

	bool CutSceneInfo::isFinished()
	{
		return mCurrentTime >= mCutSceneLength;
	}

	void CutSceneInfo::reset()
	{
		for (auto& track : tracks)
		{
			track.reset();
		}
	}

	of::file::archive::TypeInfo CutSceneInfo::getTrait() const
	{
		return { of::file::archive::Trait<CutSceneInfo>::typeId };
	}
}