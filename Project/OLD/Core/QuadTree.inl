#include <algorithm>
#include "QuadTree.hpp"
template<typename T>
inline QuadTreeNode<T>::QuadTreeNode(const size_t depth) : parent(nullptr), full(false), depth(depth)
{
	children.reserve(4);
	nodeObjects.clear();
}

template<class T>
inline QuadTreeNode<T>::~QuadTreeNode()
{
	if (hasChildren()) destroyChildNodes();
	nodeObjects.clear();

}

template<class T>
inline QuadTreeNode<T> * QuadTreeNode<T>::operator[](size_t index)
{
	if (isLeaf()) return nullptr;
	return children[clamp<size_t>(index, 0, SPLIT_SIZE - 1)];
}

template<class T>
inline const QuadTreeNode<T> * QuadTreeNode<T>::operator[](size_t index) const
{
	if (isLeaf()) return nullptr;
	return children[clamp<size_t>(index, 0, SPLIT_SIZE - 1)];
}

template<class T>
inline bool QuadTreeNode<T>::add(T * object, const bool forceAdd)
{
	if (full && !forceAdd) return false;
	nodeObjects.push_back(object);
	full = nodeObjects.size() >= QuadTree<T>::MAX_OBJECTS;
	return true;
}

template<class T>
inline bool QuadTreeNode<T>::remove(T * object)
{
	std::vector<T*>::iterator it = nodeObjects.begin();
	std::vector<T*>::iterator eit = nodeObjects.end();
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

template<class T>
inline void QuadTreeNode<T>::removeChildNodesIfPossible()
{
	size_t TotalChildObjectCount = 0;
	for each(QuadTreeNode<T>* child in children)
	{
		if (child->children.size() != 0)
			return;
		TotalChildObjectCount += child->nodeObjects.size();
	}
	if (TotalChildObjectCount == 0)
	{
		for each(QuadTreeNode<T>* child in children)
			delete child;
		children.clear();
		children.reserve(4);
		if(parent)
			parent->removeChildNodesIfPossible();
	}
}


template<class T>
inline void QuadTreeNode<T>::split()
{
	if (!isLeaf()) destroyChildNodes();
	children.resize(SPLIT_SIZE);

	Core::Vector2 start = Core::Vector2(rect.x, rect.y);

	for (size_t i = 0; i < SPLIT_SIZE; i++)
	{
		size_t d = parent == nullptr ? 0 : parent->depth + 1;
		QuadTreeNode<T>* current = new QuadTreeNode(d);
		current->parent = this;
		current->rect = Core::FloatRect(start.x, start.y, rect.w / 2, rect.h / 2);
		
		std::vector<T*>::iterator it = nodeObjects.begin();
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

template<class T>
inline bool QuadTreeNode<T>::nodeCollides(const T * object) const
{
	return object->collides(rect);
}

template<class T>
inline bool QuadTreeNode<T>::childCollides(const T * object) const
{
	if (!hasChildren()) return false;
	for (size_t i = 0; i < SPLIT_SIZE; i++)
		if (object->collides(children[i]->rect))
			return true;
	return false;
}

template<class T>
inline bool QuadTreeNode<T>::childCollides(const Core::Rect<const float&> & rect) const
{
	if (!hasChildren()) return false;
	for (size_t i = 0; i < SPLIT_SIZE; i++)
		if (rect.intersects(children[i]->rect))
			return true;
	return false;
}

template<class T>
inline void QuadTreeNode<T>::destroyChildNodes()
{
	for (size_t i = 0; i < SPLIT_SIZE; ++i)
	{
		std::vector<T*>::iterator it = children[i]->nodeObjects.begin();
		std::vector<T*>::iterator eit = children[i]->nodeObjects.end();
		for (it; it != eit; ++it)
			nodeObjects.push_back(*it);

		delete children[i];
	}
	children.clear();
}

template<class T>
inline bool QuadTreeNode<T>::hasChildren() const
{
	return !children.empty();;
}

template<class T>
inline bool QuadTreeNode<T>::isLeaf() const
{
	return children.empty();
}

template<class T>
inline bool QuadTreeNode<T>::isFull() const
{
	return full;
}

template<class T>
inline bool QuadTreeNode<T>::canSplitNode(const size_t max_size) const
{
	return depth < max_size;;
}

template<class T>
inline void QuadTreeNode<T>::setMaxNodes(const size_t max_size)
{
}

template<class T>
inline std::vector<T*>& QuadTreeNode<T>::get()
{
	return nodeObjects;
}

template<class T>
inline const std::vector<T*>& QuadTreeNode<T>::get() const
{
	return nodeObjects;
}

template<class T>
inline QuadTree<T>::QuadTree(const float width, const float height) : QuadTree(0.f, 0.f, width, height)
{
}

template<class T>
inline QuadTree<T>::QuadTree(const float x, const float y, const float width, const float height) : root(0)
{
	root.rect = Core::FloatRect(x, y, width, height);
}

template<class T>
inline bool QuadTree<T>::insert(T * object)
{
	if (rInsert(object, &root))
	{
		allObjects.push_back(object);
		return true;
	}
	return false;
}

template<class T>
inline bool QuadTree<T>::remove(T * object)
{
	bool removed = rRemove(object, &root);
	allObjects.erase(std::find(allObjects.begin(), allObjects.end(), object));
	return removed;
}

template<class T>
inline std::vector<T*> QuadTree<T>::collidesWith(T * object)
{
	std::vector<T*> colliders;
	checkLeaf(object, &root, colliders);
	return colliders;
}

template<class T>
inline void QuadTree<T>::update()
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

template<class T>
inline bool QuadTree<T>::rInsert(T * object, QuadTreeNode<T>* node)
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
		for (size_t i = 0; i < QuadTreeNode<T>::SPLIT_SIZE; ++i)
		{
			if (node->operator[](i)->nodeCollides(object))
				return rInsert(object, node->operator[](i));
		}
	}
	return node->parent == nullptr ? false : rInsert(object, node->parent);
}

template<class T>
inline bool QuadTree<T>::rRemove(T * object, QuadTreeNode<T>* node)
{
	if (node->isLeaf())
		return node->remove(object);

	else
		for (size_t i = 0; i < QuadTreeNode<T>::SPLIT_SIZE; ++i)
			if (this->rRemove(object, node->operator[](i)))
				return true;
	return false;
}

template<class T>
inline void QuadTree<T>::checkLeaf(const T * object, const QuadTreeNode<T>* node, std::vector<T*>& collidesWith) const
{
	if (node->isLeaf())
	{
		const std::vector<T*>& v = node->get();
		std::vector<T*>::const_iterator cit = v.cbegin();
		std::vector<T*>::const_iterator ceit = v.cend();
		for (cit; cit != ceit; cit++)
		{
			if ((*cit) != object && (*cit)->collides(object)) 
				collidesWith.push_back(*cit);
		}
	}
	else
	{
		for (size_t i = 0; i < QuadTreeNode<T>::SPLIT_SIZE; i++)
		{
			checkLeaf(object, node->operator[](i), collidesWith);
		}
	}
}
