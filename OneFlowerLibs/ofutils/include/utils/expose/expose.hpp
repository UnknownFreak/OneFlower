#pragma once

namespace of
{
	// friend class the Expose template in the class you want to expose to the editor
	// define the specialization for the class you want to expose in the library that can "modify" the object
	namespace expose
	{
		namespace
		{
			template<class T>
			class ExposeToEditor
			{
				void edit(T&) {}
			};
		}
	}
}