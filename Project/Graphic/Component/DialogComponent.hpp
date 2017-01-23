#ifndef DIALOGCOMPONENT_HPP
#define DIALOGCOMPONENT_HPP

#include <Core\Component\IBaseComponent.hpp>
#include <Core\Vector.h>
//#include "../GUI/Text/FloatingText.hpp"
//#include "../GUI/Text/Message.hpp"
#include <string>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics.hpp>

namespace Component
{
	class DialogComponent : public IBaseComponent < DialogComponent >
	{
	public:
		//sf::Sprite sprt;
		std::string fontName;
		std::string dialogMessage;

		//sf::RenderTexture *rex;

		//GUI::FloatingText *msg;
		Vector2 position;
		DialogComponent();
		DialogComponent(double duration);
		DialogComponent(const DialogComponent &diag);
		~DialogComponent();

		virtual DialogComponent* copy();

		void show();
		void close();
		void setMessage(std::string text, double duration = -1, int length = -1);
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