#include "classes.cpp"
#include <vector>

string playerChooseName(){
	string name;
	cout << "What is your character name?" << endl; 
	cin >> name;

	cout << endl;
	system("CLS");
	
	return name;
}
void introduceEnemyAndBattleStats(const shared_ptr<Character>& enemy, const shared_ptr<Character>& player){
		enemy->introduction();

		lineBreak();
		player->printStats();
		cout << endl;
		enemy->printStats();
		lineBreak();

}

void decideFirstTurn(const shared_ptr<Character>& enemy, const shared_ptr<Character>& player, bool& firstPlayer, bool& secondPlayer){
	player->firstTurn();
	enemy->firstTurn();

	// decides first turn
	while (firstPlayer == false && secondPlayer == false) {
		if (player->getFirstTurn() > enemy->getFirstTurn()) {
			firstPlayer = true;
		}
		else if (player->getFirstTurn() < enemy->getFirstTurn()) {
			secondPlayer = true;
		}
		else {
			cout << endl;
			cout << "Both characters rolled the same number. Rerolling..." << endl; 
			cout << endl;
			player->firstTurn();
			enemy->firstTurn();
		}
	}
}

void battleTurn(shared_ptr<Character> &enemy, shared_ptr<Character> &player, bool &firstPlayer, bool &secondPlayer){
	while (enemy->getHP() > 0 && player->getHP() > 0) {
		int choice;
		if (firstPlayer) {
			
			cout << endl << "Your Move:" << endl;
			cout << "What will you do?" << endl;
			cout << "1: Attack" << endl;
			cout << "2: Exit" << endl;
			cin >> choice;
			while (choice != 1 && choice != 2) {
				try {
					throw choice;
				}
				catch (...) {
					cout << "Invalid output." << endl;
					cin >> choice;
				}
			}

			cout << endl;

			// player chooses attack
			if (choice == 1) {
				player->rollAttkDie(); 
				enemy->receiveDamage(player->getAttkDamage()); 

				if (enemy->getHP() > 0) {
					firstPlayer = false;
					secondPlayer = true;
				}
			}
			else if (choice == 2){
				cout << "Exiting..." << endl;
				exit(1);
			}
		}
		// enemy attacks
		else if (secondPlayer) {
			enemy->rollAttkDie(); 
			player->receiveDamage(enemy->getAttkDamage()); 

			if (player->getHP() > 0) {
				firstPlayer = true;
				secondPlayer = false;
			}
		}
	}
}
void endBattle(shared_ptr<Character> &enemy, shared_ptr<Character> &player){
	if (player->getHP() == 0) {
		player->endFight();
		exit(1);
	}
	else {
		enemy->endFight();
	}

	system("pause");
	system("CLS");
	
	enemy = make_shared<Monster>(); // new enemy
}
void battleSequence() {
	shared_ptr<Character> player = makeClass(chooseClass()); // initialize player
	shared_ptr<Character> enemy = makeClass(0); // initialize enemy 

	player->introduction();

	while (true) {
		bool firstPlayer = false, secondPlayer = false;

		introduceEnemyAndBattleStats(enemy, player);
		decideFirstTurn(enemy, player, firstPlayer, secondPlayer);
		battleTurn(enemy, player, firstPlayer, secondPlayer);
		endBattle(enemy, player);
	}
}

size_t chooseClass() {
	vector<string> class_list = { "Warrior" };
	size_t user_class_choice;

	cout << "Choose a Class! (Please Enter Digit!):" << endl;

	for (int i = 0; i < class_list.size(); i++) {
		cout << i + 1 << " " << class_list.at(i) << endl;
	}

	do {
		cin >> user_class_choice;

		if (user_class_choice <= 0 || user_class_choice > class_list.size()) {
			cout << "Invalid Option, Please Choose Again." << endl;
		}

	} while (user_class_choice <= 0 || user_class_choice > class_list.size());
	
	return user_class_choice;
}

shared_ptr<Character> makeClass(int value){
	shared_ptr<Character> result;

	switch (value) {
		case 0 : 
			result = make_shared<Monster>();
			break;
		case 1 :
			result = make_shared<Warrior>(playerChooseName());
			break;
		default:
			result = make_shared<Warrior>(playerChooseName());
	}
	return result;
}

int main() {
	srand((unsigned int)time(0));
	
	battleSequence(); 
	
	system("pause");
	return 0;
}
