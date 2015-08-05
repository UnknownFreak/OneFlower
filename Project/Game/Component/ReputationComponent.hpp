#ifndef ReputationComponent_hpp
#define ReputationComponent_hpp
#include "IBaseComponent.hpp"
#include <string>
class GameObject;
class ReputationComponent :public IBaseComponent < ReputationComponent >
{
public:
	//Name of the friend you get Reputation with.
	std::string name = "No name";
	std::string repStanding = "Not Set";

	//Reputation
	int reputation = 9000;

	int level = 1;

	ReputationComponent();

	void attachOn(GameObject * go);
	void increaseReputation(std::string faction, int x);
	void decreaseReputation(std::string faction, int x);
	void addNewRep(std::string x, int y);
	void showRep(std::string a, int x, int  y);
	void removeRep(std::string a);
	//TODO low:  inline one day!!
	std::string getStanding();

private:
	std::string names[6];
	int requierment[6];

	//map
	std::map<std::string, int> rep;
	std::map<std::string, int> levels;

	template<class Archive>
	friend void save(Archive &ar, const ReputationComponent& rep);
	template<class Archive>
	friend void load(Archive &ar, ReputationComponent& rep);
};
#endif