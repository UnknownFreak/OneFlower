#include "../Logic/Physics/BoundingBox.hpp"
struct Attack
{
	Attack();
	enum AttackType
	{
		Projectile,
		Melee,
		Defensive,
		Other,
	};
	// Damage of the attack (negative will heal)
	int damage;
	// The timestamp after the execution the attack will be created
	double timeframe;
	// If Attacktype not equals Projectile, this value is used
	Physics::BoundingBox hitbox;
	// Duration of the hitbox
	double duration = 1;

	AttackType type = Other;

	// If Attacktype equals projectile this says which ID the projectile has (this is a prefab ID)
	std::pair<std::string, unsigned int> projectileID;
	// The maximum distance the projectile can travel before despawning
	double ProjectileDistance;
protected:
	template<class Archive>
	friend void save(Archive& ar, const Attack& mySkill);
	template<class Archive>
	friend void load(Archive& ar, Attack& mySkill);
};