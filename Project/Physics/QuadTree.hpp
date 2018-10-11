#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>

#include <Core\Rect.hpp>
#include "ICollider.hpp"

//#include <SFML\Graphics\Shape.hpp>
//#include <SFML\Graphics\Drawable.hpp>
//#include <SFML\Graphics\RenderTarget.hpp>

class QuadTree;

class QuadTreeNode : public sf::Drawable
{

public:
	inline QuadTreeNode(const size_t depth = 0);
	inline ~QuadTreeNode();

	inline QuadTreeNode* operator[](size_t index);
	inline const QuadTreeNode* operator[](size_t index) const;

	inline bool add(Physics::ICollider* object, const bool forceAdd = false);
	inline bool remove(Physics::ICollider* object);
	inline void split();

	inline bool nodeCollides(const Physics::ICollider* object) const;
	inline bool childCollides(const Physics::ICollider* object) const;
	inline bool childCollides(const Core::Rect<const float&>& rect) const;

	inline void destroyChildNodes();
	inline void removeChildNodesIfPossible();
	inline bool hasChildren() const;
	inline bool isLeaf() const;
	inline bool isFull() const;

	inline bool canSplitNode(const size_t max_size) const;
	inline void setMaxNodes(const size_t max_size);

	Core::Rect<float> rect;

	inline std::vector<Physics::ICollider*>& get();
	inline const std::vector<Physics::ICollider*>& get() const;

	friend class QuadTree;
	static const size_t SPLIT_SIZE = 4;

private:

	QuadTreeNode* parent;
	std::vector<QuadTreeNode*> children;
	std::vector<Physics::ICollider*> nodeObjects;

	size_t depth;
	bool full;

public:
	// Inherited via Drawable
	inline virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override
	{
		if (isFull())
			for each (QuadTreeNode* tn in children)
			{
				target.draw(*tn);
			}
		else
			for each (Physics::ICollider* t in nodeObjects)
				target.draw(*t);
	}
};

class QuadTree : public sf::Drawable
{

public:

	inline QuadTree(const float width, const float height);
	inline QuadTree(const float x, const float y, const float width, const float height);
	inline bool insert(Physics::ICollider* object);
	inline bool remove(Physics::ICollider* object);

	inline std::vector<Physics::ICollider*> collidesWith(Physics::ICollider* object);

	inline void update();

	static constexpr size_t MAX_OBJECTS = 32;
	static constexpr size_t MAX_DEPTH = 6;

	inline const QuadTreeNode& getRootNode() const
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

	inline bool rInsert(Physics::ICollider* object, QuadTreeNode* node);
	inline bool rRemove(Physics::ICollider* object, QuadTreeNode* node);
	inline void checkLeaf(const Physics::ICollider* object, const QuadTreeNode* node, std::vector<Physics::ICollider*>& collidesWith) const;

	QuadTreeNode root;
	std::vector<Physics::ICollider*> allObjects;

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