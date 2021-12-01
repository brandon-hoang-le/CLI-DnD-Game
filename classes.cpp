#include <iostream>
#include <string>
#include <memory>
#include <time.h>

using namespace std;

void lineBreak(){
	cout << "=========================================================" << endl;
}

class Character {
protected:
	string name;
	int health; 
	int armor; 
	int maxHealth; 
	int attkDmg; 
	int numberOfAttkDie; 
	int attkDieSides; 
	int firstTurnRoll; 
	int damageTaken;
	int fleeRoll; 
	bool fleeStatus;
public:
	Character() {}
	int getAttkDamage() {
		return attkDmg; 
	}
	int getHP() {
		return health; 
	}
	int getFirstTurn() {
		return firstTurnRoll; 
	}
	string getName() {
		return name; 
	}
	int getFleeRoll(){
		return fleeRoll;
	}
	bool getFleeStatus(){
		return fleeStatus;
	}
	virtual void firstTurn() {
		firstTurnRoll = rand() % 20 + 1; 
		cout << name << " rolls one die (1-20): Initiative score of " << firstTurnRoll << endl;

	}
	virtual void rollAttkDie() {
		int attkDmg = rand() % attkDieSides + 1;
		cout << name << " rolls one dice (1-" << attkDieSides << "): Damage score of " << attkDmg << "." << endl;
	}
	virtual void receiveDamage(int dmg) {
		damageTaken = dmg - armor; 

		health = health - damageTaken; 
		if (health < 0) {
			health = 0;
		}
		cout << name << "'s total HP now at: " << health << endl; 
	
	}
	virtual void introduction() = 0;
	virtual void runFromFight() = 0;
	virtual void endFight() = 0; 
	virtual void printStats() = 0; 
};

class Warrior : public Character {
private:
	int bonusAttk;

public:
	Warrior(string n) : Character() {
		name = n; 
		health = 20;
		armor = 5;
		maxHealth = 20;
		bonusAttk = 5;
		numberOfAttkDie = 1;
		attkDieSides = 6;
	}
	virtual void rollAttkDie() {
		int rolls[2];
		rolls[0] = rand() % attkDieSides + 1;
		rolls[1] = rand() % attkDieSides + 1;
		attkDmg = rolls[0] + rolls[1];
		cout << name << " rolls two dice (1-" << attkDieSides << "): Damage score of " << rolls[0] << " + " << rolls[1] << " + Strength modifier of " << bonusAttk << " for a total of " << attkDmg + bonusAttk << "." << endl;
		attkDmg += bonusAttk;
		
	}

	virtual void introduction() {
		cout << "You are " << name << ", a ferocious Warrior." << endl;
	}

	virtual void runFromFight() {
		fleeRoll =  rand() % 20 + 1;
		if (fleeRoll % 2 == 0){
			cout << "You have fled the fight!" << endl;
			fleeStatus = true;
		}
		else {
			cout << "You were unable to escape!" << endl;
			fleeStatus = false;
		}
	}

	virtual void endFight() {
		if (health == 0) {
			cout << "You have died..." << endl; 
		}
	}

	virtual void printStats() {
		cout << "Warrior " << name << "'s current stats: " << endl
			<< "Health: " << health << endl
			<< "Base Attack Die: " << numberOfAttkDie << " D " << attkDieSides << " S" << endl
			<< "Armor: " << armor << endl;
	}
};

class Monster : public Character{
public:
    Monster() : Character(){
		name = "Monster";
        health = 10;
		armor = 0;
		maxHealth = 10;
		attkDieSides = 4;
		numberOfAttkDie = 1; 
    }
	Monster(string n) : Character(){
		name = n;
        health = 10;
		attkDieSides = 4;
		armor = 3;
		numberOfAttkDie = 2; 
    }
    virtual void introduction() {
        cout << "An enemy " << name << " appears and is ready to battle!" << endl;
	}
	virtual void endFight() {
		if (health == 0)
		{
			cout << name << " has been slain!" << endl; 
            cout << "You won the fight!" << endl << endl;
		}
	}
	virtual void runFromFight() {
		cout << "Monsters don't run." << endl;
	}
	virtual void rollAttkDie() {
		int rolls[2];
		rolls[0] = rand() % attkDieSides + 1;
		rolls[1] = rand() % attkDieSides + 1;
		attkDmg = rolls[0] + rolls[1];
		cout <<  name << " rolls two dice (1-20): Damage score of " << rolls[0] << " + " << rolls[1] << " for a total of " << attkDmg << "." << endl;
		
	}
	virtual void printStats() {
		cout << name << "'s current stats: " << endl
			<< "Health: " << health << endl
			<< "Base Attack Die: " << numberOfAttkDie << " D " << attkDieSides << " S " << endl
			<< "Armor: " << armor << endl;
	}
};
