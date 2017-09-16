#ifndef DIALOGCOMPONENT_HPP
#define DIALOGCOMPONENT_HPP

#include <Core\Component\IBaseComponent.hpp>
#include <Core\Vector.h>
//#include "../GUI/Text/FloatingText.hpp"
//#include "../GUI/Text/Message.hpp"
#include <Core/String.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics.hpp>

namespace Component
{
	class DialogComponent : public IBaseComponent < DialogComponent >
	{
	public:
		//sf::Sprite sprt;
		Core::String fontName;
		Core::String dialogMessage;

		//sf::RenderTexture *rex;

		//GUI::FloatingText *msg;
		Core::Vector2 position;
		DialogComponent();
		DialogComponent(double duration);
		DialogComponent(const DialogComponent &diag);
		~DialogComponent();

		virtual DialogComponent* copy();

		void show();
		void close();
		void setMessage(Core::String text, double duration = -1, int length = -1);
		void updateLocation();
		bool open;
		bool dCreated;
		bool updateFromEditor();

		template <class Archive>
		void serialize(Archive& ar)
		{
			ar(fontName);
			//	ar(*dc.msg);
			ar(position.x);
			ar(position.y);
			ar(dialogMessage);
		}

	protected:
		void attachOn(GameObject* go);

	private:

		void tryLoadTextureAndFont();

		void createDialog();
		void createDialog(bool b);

		//template < class Archive>//, GameObject& go>
		//friend void save(Archive& archive, const DialogComponent& dc);
		//template < class Archive>//, GameObject& go>
		//friend void load(Archive& archive, DialogComponent& dc);
	};
}
#endif