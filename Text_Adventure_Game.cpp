#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// created a riddle struct so that If I need to add some more questions in future I can

struct Riddle{
    string question;
    string answer;
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
void Reach(Player& p, Room& r) {
    cout << "\n--- " << r.name << " ---" << endl;
    cout << r.description << endl;
}
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
        return Player(name, "Mage", 20, 15, 8, 2);
    }
    else {

        return Player(name, "Warrior", 25, 0, 12, 15);
    }
}

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
    char playAgain;
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

            Reach(myPlayer, Gallery);

            break;
        }


    }
    return 0;
}

