#include <algorithm>

inline QuadTreeNode::QuadTreeNode(const size_t depth) : parent(nullptr), full(false), depth(depth)
{
	children.reserve(4);
	nodeObjects.clear();
}

inline QuadTreeNode::~QuadTreeNode()
{
	if (hasChildren()) destroyChildNodes();
	nodeObjects.clear();

}

inline QuadTreeNode * QuadTreeNode::operator[](size_t index)
{
	if (isLeaf()) return nullptr;
	return children[clamp<size_t>(index, 0, SPLIT_SIZE - 1)];
}

inline const QuadTreeNode * QuadTreeNode::operator[](size_t index) const
{
	if (isLeaf()) return nullptr;
	return children[clamp<size_t>(index, 0, SPLIT_SIZE - 1)];
}

inline bool QuadTreeNode::add(Physics::ICollider * object, const bool forceAdd)
{
	if (full && !forceAdd) return false;
	nodeObjects.push_back(object);
	full = nodeObjects.size() >= QuadTree::MAX_OBJECTS;
	return true;
}

inline bool QuadTreeNode::remove(Physics::ICollider * object)
{
	std::vector<Physics::ICollider*>::iterator it = nodeObjects.begin();
	std::vector<Physics::ICollider*>::iterator eit = nodeObjects.end();
	for (it; it != eit; it++)
	{
		if (*it == object)
		{
			nodeObjects.erase(it);
			if (parent && nodeObjects.size() == 0)
				parent->removeChildNodesIfPossible();
			return true;
		}
	}
	return false;
}


inline void QuadTreeNode::removeChildNodesIfPossible()
{
	size_t TotalChildObjectCount = 0;
	for each(QuadTreeNode* child in children)
	{
		if (child->children.size() != 0)
			return;
		TotalChildObjectCount += child->nodeObjects.size();
	}
	if (TotalChildObjectCount == 0)
	{
		for each(QuadTreeNode* child in children)
			delete child;
		children.clear();
		children.reserve(4);
		if(parent)
			parent->removeChildNodesIfPossible();
	}
}


inline void QuadTreeNode::split()
{
	if (!isLeaf()) destroyChildNodes();
	children.resize(SPLIT_SIZE);

	Core::Vector2 start = Core::Vector2(rect.x, rect.y);

	for (size_t i = 0; i < SPLIT_SIZE; i++)
	{
		size_t d = parent == nullptr ? 0 : parent->depth + 1;
		QuadTreeNode* current = new QuadTreeNode(d);
		current->parent = this;
		current->rect = Core::FloatRect(start.x, start.y, rect.w / 2, rect.h / 2);
		
		std::vector<Physics::ICollider*>::iterator it = nodeObjects.begin();
		for (it; it != nodeObjects.end(); )
		{
			if (current->nodeCollides(*it))
			{
				current->add(*it);
				it = nodeObjects.erase(it);
			}
			else
				it++;
		}
		children[i] = current;
		start.x += current->rect.h;
		if (start.x >= rect.x + rect.w)
		{
			start.x = rect.x;
			start.y += current->rect.h;
		}
	}
	nodeObjects.clear();

}

inline bool QuadTreeNode::nodeCollides(const Physics::ICollider * object) const
{
	return object->collides(rect);
}

inline bool QuadTreeNode::childCollides(const Physics::ICollider * object) const
{
	if (!hasChildren()) return false;
	for (size_t i = 0; i < SPLIT_SIZE; i++)
		if (object->collides(children[i]->rect))
			return true;
	return false;
}

inline bool QuadTreeNode::childCollides(const Core::Rect<const float&> & _rect) const
{
	const Core::FloatRect rtmp(_rect.x, _rect.y, _rect.w, _rect.h);
	if (!hasChildren()) return false;
	for (size_t i = 0; i < SPLIT_SIZE; i++)
		if (rtmp.intersects(children[i]->rect))
			return true;
	return false;
}

inline void QuadTreeNode::destroyChildNodes()
{
	for (size_t i = 0; i < SPLIT_SIZE; ++i)
	{
		std::vector<Physics::ICollider*>::iterator it = children[i]->nodeObjects.begin();
		std::vector<Physics::ICollider*>::iterator eit = children[i]->nodeObjects.end();
		for (it; it != eit; ++it)
			nodeObjects.push_back(*it);

		delete children[i];
	}
	children.clear();
}

inline bool QuadTreeNode::hasChildren() const
{
	return !children.empty();;
}

inline bool QuadTreeNode::isLeaf() const
{
	return children.empty();
}

inline bool QuadTreeNode::isFull() const
{
	return full;
}

inline bool QuadTreeNode::canSplitNode(const size_t max_size) const
{
	return depth < max_size;;
}

inline std::vector<Physics::ICollider*>& QuadTreeNode::get()
{
	return nodeObjects;
}

inline const std::vector<Physics::ICollider*>& QuadTreeNode::get() const
{
	return nodeObjects;
}

inline QuadTree::QuadTree(const float width, const float height) : QuadTree(0.f, 0.f, width, height)
{
}

inline QuadTree::QuadTree(const float x, const float y, const float width, const float height) : root(0)
{
	root.rect = Core::FloatRect(x, y, width, height);
}

inline bool QuadTree::insert(Physics::ICollider * object)
{
	if (rInsert(object, &root))
	{
		allObjects.push_back(object);
		return true;
	}
	return false;
}

inline bool QuadTree::remove(Physics::ICollider * object)
{
	bool removed = rRemove(object, &root);
	if (removed)
		allObjects.erase(std::find(allObjects.begin(), allObjects.end(), object));
	return removed;
}

inline std::vector<Physics::ICollider*> QuadTree::collidesWith(Physics::ICollider * object)
{
	std::vector<Physics::ICollider*> colliders;
	checkLeaf(object, &root, colliders);
	return colliders;
}

inline void QuadTree::update()
{
	for (size_t i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i]->needUpdate())
		{
			rRemove(allObjects[i], allObjects[i]->node);
			rInsert(allObjects[i], allObjects[i]->node->parent == nullptr ? allObjects[i]->node : allObjects[i]->node->parent);
			allObjects[i]->update = false;
		}
	}
}

inline bool QuadTree::rInsert(Physics::ICollider * object, QuadTreeNode* node)
{
	if (object == nullptr || node == nullptr) return false;
	if (node->isLeaf())
	{
		if (!node->add(object))
		{
			if (!node->canSplitNode(MAX_DEPTH))
			{
				node->add(object, true);
				object->node = node;
				return true;
			}
			else
			{
				node->split();
				return rInsert(object, node);
			}
		}
		object->node = node;
		return true;
	}
	else
	{
		for (size_t i = 0; i < QuadTreeNode::SPLIT_SIZE; ++i)
		{
			if (node->operator[](i)->nodeCollides(object))
				return rInsert(object, node->operator[](i));
		}
	}
	return node->parent == nullptr ? false : rInsert(object, node->parent);
}

inline bool QuadTree::rRemove(Physics::ICollider * object, QuadTreeNode* node)
{
	if (node->isLeaf())
		return node->remove(object);
	else
		for (size_t i = 0; i < QuadTreeNode::SPLIT_SIZE; ++i)
			if (this->rRemove(object, node->operator[](i)))
				return true;
	return false;
}

inline void QuadTree::checkLeaf(const Physics::ICollider * object, const QuadTreeNode* node, std::vector<Physics::ICollider*>& collidesWith) const
{
	if (node->isLeaf())
	{
		const std::vector<Physics::ICollider*>& v = node->get();
		std::vector<Physics::ICollider*>::const_iterator cit = v.cbegin();
		std::vector<Physics::ICollider*>::const_iterator ceit = v.cend();
		for (cit; cit != ceit; cit++)
		{
			if ((*cit) != object && (*cit)->collides(*object)) 
				collidesWith.push_back(*cit);
		}
	}
	else
	{
		for (size_t i = 0; i < QuadTreeNode::SPLIT_SIZE; i++)
		{
			checkLeaf(object, node->operator[](i), collidesWith);
		}
	}
}
