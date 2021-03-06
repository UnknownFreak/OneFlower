#include "Physics.hpp"

#include <SFML\Graphics\Rect.hpp>

#include "Component\RigidComponent.hpp"
#include "Component\HitboxComponent.hpp"

#include "Movement.hpp"

#include <Core\Component\GameObject.h>
#include <Core\Component\TransformComponent.hpp>

#include <Core\EngineModule\EngineModuleManager.hpp>

#include <Graphic\Gfx.h>

void PhysicsEngine::update()
{
	//gravity();
	//simulation();
}
void PhysicsEngine::gravity()
{
	/*
	for(size_t i = 0; i < rigids.size(); i++)
	{
		if(rigid[i]->gravity)
		{
			TransformComponent* tc = rigid[i]->attachedOn->GetComponent<TransformComponent>();
			Vector2 past = tc->position;

			Vector2 direction(0,1);
			double velocity = (Gravity*PixelInOneMeter);
			//rigid[i]->movement.addTranslation(direction,velocity);
			//->GetComponent<>()->addForce(Vector2(0,1),velocity);
		}
	}
	//*/
}

void PhysicsEngine::simulation()
{
	/*
	for(size_t i = 0; i < rigid.size(); i++)
	{
		TransformComponent* tc = rigid[i]->attachedOn->GetComponent<TransformComponent>();
		{
			if(rigid[i]->inMotion())
			{
				double force = rigid[i]->force;
				Vector2 direction = rigid[i]->direction;
				std::pair<GameObject*,double> collider = collision(rigid[i],Vector2(direction.x*force,direction.y*force));
				//HIGH: Checking how force move object on google.PS check collision and pass throug hitbox but still tirgger
				if(collider.second >= 1)
					tc->move(direction,force);
				else
					tc->move(direction,force*collider.second);
			}
		}
		//rigid[i]->forceQueue.clear();
	}
	//*/
}

//LOW: Change owner
Physics::Collider PhysicsEngine::collision(Component::Transform* motion, Core::FloatRect bbox, Core::Vector2 speed)
{
	//When two object travel in the same direction, The one who "Update" first will decide the outcome. If its the chaser than it catches, if its the runner than it flee. Thats the simpliest way todo it
	Physics::Collider collider;

	/*
	for(size_t i = 0; i < hitboxes.size(); ++i)
	{
		HitboxComponent* hitbox = hitboxes[i];
		Physics::BoundingBox boxMoving(motion->position+speed,bbox.size);
		Physics::BoundingBox boxStatic
			(
				hitbox->attachedOn->GetComponent<TransformComponent>()->position,hitbox->bounding.size
			);

		//if(X1 + W1<X2 or X2 + W2<X1 or
		//Y1 + H1<Y2 or Y2 + H2<Y1) :

		#pragma region BroadPhase
		if(boxMoving.position.y +boxMoving.size.y < boxStatic.position.y)
			continue;
		else if(boxStatic.position.y + boxStatic.size.y < boxMoving.position.y)
			continue;
		else if(boxMoving.position.x + boxMoving.size.x < boxStatic.position.x)
			continue;
		else if(boxStatic.position.x + boxStatic.size.x < boxMoving.position.x)
			continue;
		#pragma endregion
		else
		{
			float timeCx = 9000;
			float timeCy = 9000;
			float distanceCx = 9000;
			float distanceCy = 9000;

			if(speed.x > 0)
				distanceCx = boxStatic.position.x - (boxMoving.position.x + boxMoving.size.x);
			else if(speed.x < 0)
				distanceCx = (boxStatic.position.x + boxStatic.size.x) - boxMoving.position.x;
			if(speed.y > 0)
				distanceCy = boxStatic.position.y - (boxMoving.position.y + boxMoving.size.y);
			else if(speed.y < 0)
				distanceCy = (boxStatic.position.y + boxStatic.size.y) - boxMoving.position.y;
			//HIGH: Remove this and make it just return the collision time and let the game decide what happends with multi collision, put this intersection inside boundingbox?

			//HIGH: this is somehow wrongs dont know any fixes yet
			float shortDist = distanceCx < distanceCy ? distanceCx : distanceCy;

			if(shortDist < collider.time)
			{
				collider.time = shortDist;
				collider.contact = hitbox->attachedOn;
			}
		}
	}
	//*/
	return collider;
}

#ifdef _DEBUG
void Gfx::drawGizmo() const
{
	if (drawHitboxes)
	{
		PhysicsEngine& phys = Engine::GetModule<PhysicsEngine>();
		for (size_t i = 0; i < phys.hitboxes.size(); i++)
		{
			Component::Transform* tc = phys.hitboxes[i]->attachedOn->GetComponent<Component::Transform>();
			hitbox.setPosition(tc->position.x, tc->position.y);

			//TopBar
			hitbox.setTextureRect(sf::IntRect(0, 0, phys.hitboxes[i]->bounding.x, 2));
			view.render.draw(hitbox);

			double hypno = std::sqrt((
				phys.hitboxes[i]->bounding.w*phys.hitboxes[i]->bounding.w +
				phys.hitboxes[i]->bounding.h*phys.hitboxes[i]->bounding.h
				));
			hitbox.setTextureRect(sf::IntRect(0, 0, (int)hypno, 2));

			float degree = (float)(std::asin(phys.hitboxes[i]->bounding.h / hypno) * 180) / 3.14159265f;

			hitbox.setRotation(degree);
			view.render.draw(hitbox);

			hitbox.setPosition(tc->position.x, tc->position.y + phys.hitboxes[i]->bounding.h);

			hitbox.setRotation(-degree);
			view.render.draw(hitbox);
			hitbox.setRotation(0);

			//BottomBar
			hitbox.setTextureRect(sf::IntRect(0, 0, phys.hitboxes[i]->bounding.w, 2));
			view.render.draw(hitbox);

			//LeftBar
			hitbox.setPosition(tc->position.x, tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0, 0, 2, phys.hitboxes[i]->bounding.h));
			view.render.draw(hitbox);

			//RightVBar

			//Engine::Graphic.view.render.draw(hitbox);
			hitbox.setPosition(tc->position.x + phys.hitboxes[i]->bounding.w, tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0, 0, 2, phys.hitboxes[i]->bounding.h));
			view.render.draw(hitbox);
		}
		for (size_t i = 0; i < phys.rigids.size(); i++)
		{
			Component::Transform* tc = phys.rigids[i]->attachedOn->GetComponent<Component::Transform>();
			hitbox.setPosition(tc->position.x, tc->position.y);

			//TopBar
			hitbox.setTextureRect(sf::IntRect(0, 0, phys.rigids[i]->bounding.w, 2));
			view.render.draw(hitbox);

			double hypno = std::sqrt((
				phys.rigids[i]->bounding.w*phys.rigids[i]->bounding.w +
				phys.rigids[i]->bounding.h*phys.rigids[i]->bounding.h
				));
			hitbox.setTextureRect(sf::IntRect(0, 0, (int)hypno, 2));

			float degree = (float)(std::asin(phys.rigids[i]->bounding.h / hypno) * 180) / 3.14159265f;

			hitbox.setRotation(degree);
			view.render.draw(hitbox);

			hitbox.setPosition(tc->position.x, tc->position.y + phys.rigids[i]->bounding.h);

			hitbox.setRotation(-degree);
			view.render.draw(hitbox);
			hitbox.setRotation(0);

			//BottomBar
			hitbox.setTextureRect(sf::IntRect(0, 0, phys.rigids[i]->bounding.w, 2));
			view.render.draw(hitbox);

			//LeftBar
			hitbox.setPosition(tc->position.x, tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0, 0, 2, phys.rigids[i]->bounding.h));
			view.render.draw(hitbox);

			//RightVBar

			//Engine::Graphic.view.render.draw(hitbox);
			hitbox.setPosition(tc->position.x + phys.rigids[i]->bounding.w, tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0, 0, 2, phys.rigids[i]->bounding.h));
			view.render.draw(hitbox);
		}
	}
}
#endif