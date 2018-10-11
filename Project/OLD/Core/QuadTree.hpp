#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>

#include <Core\Rect.hpp>
#include <SFML\Graphics\Shape.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

template<class T>
class QuadTree;

template <class T>
class QuadTreeNode : public sf::Drawable
{

public:
	inline QuadTreeNode(const size_t depth = 0);
	inline ~QuadTreeNode();

	inline QuadTreeNode* operator[](size_t index);
	inline const QuadTreeNode* operator[](size_t index) const;

	inline bool add(T* object, const bool forceAdd = false);
	inline bool remove(T* object);
	inline void split();

	inline bool nodeCollides(const T* object) const;
	inline bool childCollides(const T* object) const;
	inline bool childCollides(const Core::Rect<const float&>& rect) const;

	inline void destroyChildNodes();
	inline void removeChildNodesIfPossible();
	inline bool hasChildren() const;
	inline bool isLeaf() const;
	inline bool isFull() const;

	inline bool canSplitNode(const size_t max_size) const;
	inline void setMaxNodes(const size_t max_size);

	Core::Rect<float> rect;

	inline std::vector<T*>& get();
	inline const std::vector<T*>& get() const;

	friend class QuadTree<T>;
	static const size_t SPLIT_SIZE = 4;

private:

	QuadTreeNode<T>* parent;
	std::vector<QuadTreeNode<T>*> children;
	std::vector<T*> nodeObjects;

	size_t depth;
	bool full;

	template <class Ty = T>
	inline typename std::enable_if<std::is_base_of<sf::Drawable, Ty>::value>::type
		_draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (isFull())
			for each (QuadTreeNode<T>* tn in children)
			{
				target.draw(*tn);
			}
		else
			for each (T* t in nodeObjects)
				target.draw(*t);
	}

	template <class Ty = T>
	inline typename std::enable_if<!std::is_base_of<sf::Drawable, Ty>::value>::type
		_draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}

public:
	// Inherited via Drawable
	inline virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override
	{
		_draw(target, states);
	}
};

template <class T>
class QuadTree : public sf::Drawable
{

public:

	inline QuadTree(const float width, const float height);
	inline QuadTree(const float x, const float y, const float width, const float height);
	inline bool insert(T* object);
	inline bool remove(T* object);

	inline std::vector<T*> collidesWith(T* object);

	inline void update();

	static constexpr size_t MAX_OBJECTS = 32;
	static constexpr size_t MAX_DEPTH = 6;

	inline const QuadTreeNode<T>& getRootNode() const
	{
		return root;
	}

	inline bool resize(Core::Vector2& pos, Core::Vector2& size)
	{
		if (allObjects.empty())
		{
			root.rect = Core::FloatRect(pos, size);
			return true;
		}
		return false;
	}

private:

	inline bool rInsert(T* object, QuadTreeNode<T>* node);
	inline bool rRemove(T* object, QuadTreeNode<T>* node);
	inline void checkLeaf(const T* object, const QuadTreeNode<T>* node, std::vector<T*>& collidesWith) const;

	QuadTreeNode<T> root;
	std::vector<T*> allObjects;

public:
	// Inherited via Drawable
	inline virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override
	{
		target.draw(root, states);
	}

};

template<typename T>
T clamp(const T& val, const T&low, const T& high)
{
	if (val < low)
		return low;
	else if (val > high)
		return high;
	return val;
}

#include "QuadTree.inl"


#endif 