#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

struct Typewriter : public streambuf {
    streambuf* dest;
    int delay;

    Typewriter(streambuf* d, int ms) : dest(d), delay(ms) {}

protected:
    virtual int_type overflow(int_type ch) override {
        if (ch != traits_type::eof()) {
            this_thread::sleep_for(chrono::milliseconds(delay));
            dest->sputc(ch);
            dest -> pubsync();
        }
        return ch;

    }
};
// created a riddle struct so that If I need to add some more questions in future I can

struct Riddle{
    string question;
    string answer;
};

struct Enemy {
    string name;
    int health;
    int attackPower;
    int blockMeter{ 0 };
};

class Room {
public:
    string name;
    string description;
    string type;


    Room(const string& room_name, const string& room_description, const string& room_type) // constructor
        :name(room_name), description(room_description), type(room_type) {
    }
};
class Player {
public:
    vector<string> inventory;
    string name;
    string characterClass;
    int health;
    int mana;
    int durability;
    int strength;

    // initalized the variables with constructor so that its easy to call and reassign value again
    Player(const string& n, const string& cclass, int h, int m, int d, int s)
        : name(n), characterClass(cclass), health(h), mana(m), durability(d), strength(s) {
    }

    //To tell user there attributes based on their choice

    void Intro() {
        cout << "\nWelcome " << characterClass << ", " << name << "!" << endl;
        if (characterClass == "Warrior") {
            cout << "You are strong enough to move mountains: " << strength << " STR." << endl;
            cout << "Durable enough to shield a meteor: " << health << " HP." << endl;
        }
        else {
            cout << "You have power enough to nuke a village: " << mana << " MANA." << endl;
            cout << "But a little vulnerable: " << durability << " HP." << endl;
        }
    }
    // checks if an item is available in inventory, linear search, will consume O(n) time but for a small game it shall work perfectly
    bool hasItem(const string& ItemName) {
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i] == ItemName)  return true;
        }
        return false;
    }
};
// Introduces player
Player setupPlayer() {
    string name;
    int choice;

    cout << "Welcome to the World of No Lights" << endl;
    cout << "Do you want to be 'Mage (1)' or 'Warrior (2)': ";

    cin >> choice;

    cout << "Enter yout character's name";
    cin >> name;

    if (choice == 1) {

        //assigns attributes to character based on player choice (int health, int mana, int durability, int strength)
        return Player(name, "Mage", 22, 15, 8, 2);
    }
    else {

        return Player(name, "Warrior", 25, 0, 12, 15);
    }
}


// Room 1
// Blood Gate has a special condition , as they ask sacrifice so they got a function
//It asks for sacrifice from player and based on their character choice , It deducts 
// their strenght (for warrior) and mana (for mage)
// we made it bool so that we can 
bool Blood_Gate(Player& p, Room& r) {
    string action;
    bool choice;

    cout << "\n--- " << r.name << " ---" << endl;
    cout << r.description << endl;
    cout << "The gate demands a sacrifice. Type 'offer' to place your hand on the iron: ";
    cin >> action;

    if (action == "offer") {

        cout << "\nThe gate takes part of your uniquq stats..." << endl;

        if (p.characterClass == "Warrior") {

            p.strength -= 5;
            cout << "Your Durability drops to " << p.strength << endl;
        }
        else if (p.characterClass == "Mage") {

            p.mana -= 4;
            cout << "Your Mana drops to.." << p.mana << endl;
        }


        cout << "The scarlet iron grinds open." << endl;
        return true;
    }
    else {

        cout << "\nYou refuse, and the gate remains shut tight." << endl;
        return false;
    }

}
//created a function for courtyard still because i can get a specfific condition for it in future

//Room 2
void Courtyard_Event(Player& p, Room& r) {
    cout << "\n--- " << r.name << " ---" << endl;
    cout << r.description << endl;

    string choice;
    cout << "You see a massive stone in the middle of the courtyard, imprinted some ancient language. Do you INVESTIGATE";
    cin >> choice;

    // We use .compare() or just ==. Professional tip: convert to lowercase later, 
    // but for now, your OR check is fine!

    if (choice == "Investigate" || choice == "INVESTIGATE")
    {
        cout << "\nThe ston glows. Do you want to [1] Take Artifact or [2] Restore your Stats";
        int subChoice;
        cin >> subChoice;

        // player gets their artifact based on their character class

        if (subChoice == 1) {
            if (p.characterClass == "Warrior") {
                p.inventory.push_back("Greatsword");
                cout << "You get a Big ahh Greatsword" << endl;
            }
            else {
                p.inventory.push_back("Moonstaff");
                cout << "You get the power of Moon in your hands" << endl;
            }
        }
        // player gets their stats restored based on their character class so that they do not get additional stats
        else {
            if (p.characterClass == "Warrior") {
                p.strength += 5;

                cout << "You have regained your strength: " << p.strength << endl;
            }
            else {
                p.mana += 4;
                cout << "You have regained your Magic: " << p.mana << "Magic" << endl;
            }
        }
    }

}
// Room 3
void whispering_Gallery(Player& p, Room& r) {

    // object using riddle struct
    vector<Riddle> riddleList = {
    {"What has keys but no locks?", "piano"},
    {"What gets wetter as it dries?", "towel"}
    };

    cout << "\n--- " << r.name << " ---" << endl;
    cout << r.description << endl;

    cout << " You see a picture " << endl;
    cout << " A mysterious fog captures you:\n" << "Do you possess the key" << endl;

    if (p.hasItem("key")) {
        cout << "Great! You possess the key '\n'" << " The Fog disappears " << endl;
    }
    else {
        cout << "The mist asks for your blood ";
        p.health -= 3;
    }

    cout << " You hear a echoing voice , The image suddenly appears to be moving " << endl;
    cout << " You must answer my questions for opeining the next gate or thee shall be burned alive '\n' ";
    cout << "For each wrong answer Thee shall be punished and for every wrong answer You shall be burned " << endl;

    cout << "--- Do you want to move ---" << endl;
    string move;

    // if the function is not yes then gate will be locked and I used transform to make the string in lower case doesnt matter what user writes

    while (move != "yes") {
        cout << "The gate is locked. Try again: ";
        cin >> move;
        transform(move.begin(), move.end(), move.begin(), ::tolower);
    }
    //goes through riddleList one by one

    for (const auto& r : riddleList ){
     
        cout << r.question;
        string playerAnswer;
        cin >> playerAnswer;
        transform(playerAnswer.begin(), playerAnswer.end(), playerAnswer.begin(), ::tolower);
        if ( playerAnswer == r.answer){
            cout << "Bravo!, You are right."<< endl;
        }
        else {  
            cout << "You are a fool, You shall be punished" << endl;
            p.health -= 2;
            cout << " Your life decreases: " << p.health << endl;
            if (p.health <= 0) {
                cout << "YOU DIED";
                return;
            }
        }
        
    }
    
}
void Boss_Fight(Player& p, Room& r) {
    cout << "\n--- " << r.name << " ---" << endl;
    cout << r.description << endl;

    Enemy Sentinel = { "The Dracula", 100, 30 };

    cout << "You come face with " << Sentinel.name << endl;
    bool isStunned{ false };

    while(p.health <= 0 && Sentinel.health <= 0){
        int playerChoice;
        int draculaIntent = rand() % 100;
        string moveDescription;

        if (draculaIntent < 60) moveDescription = "Dracula is lunging forward!"; // ATTACK
        else if (draculaIntent < 90) moveDescription = "Dracula is bracing behind his cloak..."; // DEFEND
        else moveDescription = "The air grows cold and dark..."; // SPECIAL

        cout << "\n[INTENT]: " << moveDescription << endl;

        cout << "Choose your action " << endl;
        cout << "1.Attack >> 2. Heal(only 1 potion avail.) >> 3. Defend >> Use ultimate(charge req) " << endl;

        int playerAttack = 0;

        switch (playerChoice) {
        case 1: 
            if (draculaIntent >= 60 && draculaIntent < 90) { 
                Sentinel.blockMeter -= 10;
                cout << "You hit his cloak! Block Meter: " << Sentinel.blockMeter << endl;
                if (Sentinel.blockMeter <= 0) isStunned = true;
            }
            else {
                Sentinel.health -= 15;
                cout << "You landed a clean hit!" << endl;
            }
            break;

        case 2: 
            if (draculaIntent < 60) { // Only works against Attacks
                cout << "CLANG! You parried him!" << endl;
                isStunned = true;
            }
            else {
                cout << "You parried thin air! You're wide open!" << endl;
                p.health -= 5; // Penalty for missing a parry
            }
            break;
        }

         
        if (Sentinel.health <= 0) {
            cout << "The Dracula has been defeated!" << endl;
            break;
        }

        if (isStunned) {
            cout << "\nDracula is reeling from your impact! He recovers his stance." << endl;
            isStunned = false; // 
            Sentinel.blockMeter = 30; 
        }
        else if (draculaIntent < 60) {
            cout << "\nDracula lunges at you!" << endl;
            int bossAttack = rand() % 10 + 5;
            p.health -= bossAttack;
            cout << "You took " << bossAttack << " damage! Current Health: " << p.health << endl;
        }
        else if (draculaIntent >= 90) {
            p.health -= 2;
            Sentinel.health += 5;
            cout << "\nDracula siphons your life force!" << endl;
        }
        else {
            cout << "\nDracula holds his defensive stance, watching your every move..." << endl;
        }
    }

}
// Displays player informations
void displayHUD(const Player& p) {

    cout << "\n========================================" << endl;
    cout << " NAME: " << p.name << " | CLASS: " << p.characterClass << endl;
    cout << " HP: " << p.health << " | MANA: " << p.mana << " | STR: " << p.strength << endl;
    cout << " INVENTORY: [ ";
    for (const string& item : p.inventory) {
        cout << item << " ";
    }
    cout << "]" << endl;
    cout << "========================================" << endl;
}


int main() {
    streambuf* original = std::cout.rdbuf();
    Typewriter tw(cout.rdbuf(), 50);
    cout.rdbuf(&tw);

    srand(time(0));
    int location{ 1 };

    Player myPlayer = setupPlayer();


    myPlayer.Intro();

    while (myPlayer.health > 0) {
        displayHUD(myPlayer);

        Room gate("Blood_Gate", "A 5,000-year-old scarlet gate of rusted iron.", "Vampiric");
        Room Courtyard("Courtyard", "", "");
        Room Gallery("Whispering Gallery", "", "");
        Room Sentinel("Sentinel's Reach", "", "");

        if (location == 1) {
            if (Blood_Gate(myPlayer, gate)) {

                location = 2; // Only move to Courtyard if Blood_Gate returns true

            }
        }


        else if (location == 2) {


            Courtyard_Event(myPlayer, Courtyard);

            cout << "To the NORTH, you see a glowing statue. Move? ";
            string move;
            cin >> move;
            if (move == "north") location = 3;

        }
        else if (location == 3) {

            whispering_Gallery(myPlayer, Gallery);


            string move;
            cin >> move;
            if (move == "west") location = 4;

        }
        else if (location == 4) {

            Boss_Fight(myPlayer, Gallery);

            break;
        }


    }
    return 0;
}

