#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include "../GUIElement/BaseHandler.hpp"
#include "../Button/Button.hpp"
namespace GUI
{

	class Scrollbar : public BaseHandler
	{

	public:
		Scrollbar();
		~Scrollbar();
		unsigned int handle(MessageType msg) override;

		void addItem(BaseHandler* item);
		bool removeItem(BaseHandler* item);
		bool removeItem(size_t index);
	protected:

	private:
		Button upButton;
		Button downButton;
		Button trackButton;

		//not really required, but the item count in the scrollbar
		size_t itemCount = 0;
		//Number of items that can be displayed
		// scrollBar size
		size_t itemsThatCanBeDisplayed = 0;
		// the scrollposition
		size_t scrollPos = 0;

		//Scroll one item per scrollclick. 
		size_t scrollAmount = 1; 


		std::vector<BaseHandler*> itemList;
		BaseHandler* selectedItem;
		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	};

}

#endif