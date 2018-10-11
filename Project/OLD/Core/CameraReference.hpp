#ifndef CAMERA_REFERENCE_HPP
#define CAMERA_REFERENCE_HPP

#include "ICollider.hpp"
#include <SFML\Graphics\View.hpp>

class CameraRef : public ICollider<CameraRef>
{
	const sf::FloatRect& CameraView;
public:
	inline CameraRef(sf::View & camera) : CameraView(camera.getViewport()), ICollider<CameraRef>(CameraView.left, CameraView.top, CameraView.width, CameraView.height)
	{

	}
};
#endif