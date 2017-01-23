#include "TextureMap.hpp"

TextureMapPoint& TextureMap::getTextureMapPoint(std::string myPoint)
{
	//std::map<std::string, TextureMapPoint>::iterator it = TexturePoints.find(myPoint);
	//if (it != TexturePoints.end())
	//{
	//	return it->second;
	//}
	return TexturePoints[myPoint];
}