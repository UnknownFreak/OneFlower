#ifndef LOADINGHELPERS_H
#define LOADINGHELPERS_H

#include <Helpers/String.hpp>
#include <map>

#include "../entity/object.h"
#include "../global/global.h"

namespace SpriterEngine
{
	class EasingCurveInterface;

	static const s_int NO_FILE = 0xffffffff;

	struct SpriteKeyFileInfo
	{
		bool useDefaultPivot;
		s_int fileIndex;
	};

	struct SubEntityKeyInfo
	{
		s_int entityId;
		s_int animationIndex;
	};

	typedef std::vector<SpriteKeyFileInfo> SpriteKeyFileInfoVector;
	typedef std::map<s_int, SpriteKeyFileInfoVector> SpriteKeyFileInfoObjectIdMap;

	typedef std::vector<SubEntityKeyInfo> SubEntityKeyInfoVector;
	typedef std::map<s_int, SubEntityKeyInfoVector> SubEntityKeyInfoMap;

	typedef std::vector<s_int> IntVector;
	typedef std::vector < IntVector> Int2DVector;

	typedef std::map<s_int, point> PointMap;

	typedef std::vector<bool> BooleanVector;

	const s_int MAX_CONTROL_POINTS = 4;
	typedef real ControlPointArray[MAX_CONTROL_POINTS];

	enum CurveType
	{
		CURVETYPE_NONE,
		CURVETYPE_INSTANT,
		CURVETYPE_LINEAR,
		CURVETYPE_QUADRATIC,
		CURVETYPE_CUBIC,
		CURVETYPE_QUARTIC,
		CURVETYPE_QUINTIC,
		CURVETYPE_BEZIER
	};

	Object::ObjectType objectTypeNameToType(Core::String typeName);

	CurveType curveTypeNameToType(Core::String typeName);

	EasingCurveInterface *getNewEasingCurve(CurveType curveType, ControlPointArray *controlPoints);

	Core::String extractFilePath(Core::String fileName);

	class FileFlattener
	{
	public:
		FileFlattener();

		void appendFolder();
		void appendFile();
		s_int getFlattenedIndex(s_int folderIndex, s_int fileIndex);

	private:
		Int2DVector folders;
		s_int fileCount;
	};
}

#endif // LOADINGHELPERS_H
