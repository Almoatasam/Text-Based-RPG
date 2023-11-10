#include <iostream>
#include <cstdlib>
#include <ctime>

class Player {
public:
	std::string name;
	int level;
	int health;
	int gold;
	int defense;

	Player(std::string n) : name(n), level(1), health(100), gold(0), defense(10) {}

	void receiveGold(int amount) {
		gold += amount;
	}

	void takeDamage(int damage) {
		health -= damage;
		if (health < 0) {
			health = 0;
		}
	}

	void listItems() {
		std::cout << "Available items for purchase:\n";
		std::cout << "1. Defense Training (Cost: 20 gold, Defense Increase: 5)" << std::endl;
		std::cout << "2. Shield Orb (Cost: 15 gold, Defense Increase: 3)" << std::endl;
		// TODO: Exp Potion, Stregnth Potion, Health Orb.
	}

	void buyItem(int choice) {
		int cost;
		int defenseIncrease;

		switch (choice) {
		case 1:
			cost = 20;
			defenseIncrease = 5;
			break;
		case 2:
			cost = 15;
			defenseIncrease = 3;
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
			return;
		}

		if (gold >= cost) {
			gold -= cost;
			if (defenseIncrease > 0) {
				defense += defenseIncrease;
				std::cout << "You bought an item. Your defense increased by " << defenseIncrease << "." << std::endl;
			}
		}
		else {
			std::cout << "You don't have enough gold to buy this item." << std::endl;
		}
	}

	void printStats() {
		std::cout << "\nName: " << name << "\tLevel: " << level << "\tHealth: " << health << "\tGold: " << gold << "\t    Defense: " << defense << std::endl;
	}
};

class Location {
public:
	std::string name;
	std::string description;
	int minEnemyLevel;
	int maxEnemyLevel;
	int questGoldReward;
	int questExpReward;

	Location(std::string n, std::string desc, int minLvl, int maxLvl, int gold, int exp)
		: name(n), description(desc), minEnemyLevel(minLvl), maxEnemyLevel(maxLvl), questGoldReward(gold), questExpReward(exp) {}
};

class Enemy {
public:
	std::string name;
	int level;
	int health;
	int attack;
	int goldReward;

	Enemy(std::string n, int lvl, int h, int a, int g) : name(n), level(lvl), health(h), attack(a), goldReward(g) {}

	void attackPlayer(Player& player) {
		int damage = std::max(0, attack - player.defense);
		player.takeDamage(damage);
	}
};

void battleEnemy(Player& player, Enemy& enemy) {
	std::cout << "You encounter a level " << enemy.level << " " << enemy.name << "!" << std::endl;

	while (enemy.health > 0 && player.health > 0) {
		// Player's turn
		int playerChoice;
		std::cout << "1. Attack\n2. Heal\nEnter your choice: ";
		std::cin >> playerChoice;

		if (playerChoice == 1) {
			int damage = rand() % (player.level * 5) + 10; // Attack does random damage depending on level
			enemy.health -= damage;
			std::cout << "You deal " << damage << " damage to the " << enemy.name << "!" << std::endl;
		}
		else if (playerChoice == 2) {
			// Heal player
			player.health += 20;
			std::cout << "You use a healing potion to recover." << std::endl;
		}

		// Enemy's turn
		if (enemy.health > 0) {
			int damage = std::max(0, enemy.level + enemy.attack - player.defense);
			player.takeDamage(damage);
			std::cout << "The " << enemy.name << " attacks you and deals " << damage << " damage!" << std::endl;
		}

		// Display health/Current Stats
		std::cout << "\nYour health : " << player.health << " | Enemy's health: " << enemy.health << std::endl;
	}

	if (player.health <= 0) {
		std::cout << "You were defeated by the " << enemy.name << "!" << std::endl;
	}
	else {
		player.receiveGold(enemy.goldReward);
		std::cout << "You defeated the " << enemy.name << " and gained " << enemy.goldReward << " gold!" << std::endl;
	}
}

void exploreLocation(Player& player, Location& location) {
	std::cout << "You arrive at " << location.name << ". " << location.description << std::endl;
	int random = (location.maxEnemyLevel - location.minEnemyLevel + 1) + location.minEnemyLevel;
	Enemy locationEnemy("Mysterious Creature", rand() % random, random + 30, random + 7, 30);
	battleEnemy(player, locationEnemy);

	if (player.health > 0) {
		player.receiveGold(location.questGoldReward);
		player.level++;
		std::cout << "You completed the quest and gained " << location.questGoldReward << " gold and experience!\n";
	}
}

int main() {
	srand(time(0));

	std::cout << "\t\t\t\t\t   Get ready Adventurer, " << std::endl;
	std::cout << "\t\tyour about to embark on a journey to conquer the evil that resides in this  world!" << std::endl;
	std::string playerName;
	std::cout << "\t\t\t\t\tWhat will be your Hero Name? " << std::endl;
	std::cin >> playerName;

	Player player(playerName);

	Location forest("Amakane Forest", "A mystical forest filled with ancient trees.", 1, 15, 50, 100);
	Location cave("Dragon Spine", "A pitch-black cave with unknown creatures lurking in the shadows.", 3, 27, 70, 150);
	Location castle("Haunted House", "An eerie castle rumored to be haunted by restless spirits.", 5, 30, 100, 200);
	//Location Floating Island....

	while (player.health > 0) {
		player.printStats();

		std::cout << "\nLocations:" << std::endl;
		std::cout << "1. " << forest.name << " (Easy) " << std::endl;
		std::cout << "2. " << cave.name << " (Medium) " << std::endl;
		std::cout << "3. " << castle.name << " (Hard)" << std::endl;
		std::cout << "4. Floating Island (Coming soon...)" << std::endl;
		std::cout << "5. Shop" << std::endl;
		std::cout << "6. Quit" << std::endl;

		int choice;
		std::cout << std::endl << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			exploreLocation(player, forest);
			break;
		case 2:
			exploreLocation(player, cave);
			break;
		case 3:
			exploreLocation(player, castle);
			std::cout << "\n\nWell done Hero, you have beat the latest location\nFeel free to keep playing." << std::endl;
			break;
		case 4:
			// TODO: exploreLocation(player, Island);
			std::cout << "This location isn't finished yet. " << std::endl;
			break;
		case 5:
			player.listItems();
			int itemChoice;
			std::cout << "Enter the item number you want to buy" << std::endl;
			std::cin >> itemChoice;
			player.buyItem(itemChoice);
			break;
		case 6:
			std::cout << "Thank you for playing!" << std::endl;
			return 0;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	}

	std::cout << std::endl << "You have been defeated! Game over." << std::endl;
	return 0;
}


