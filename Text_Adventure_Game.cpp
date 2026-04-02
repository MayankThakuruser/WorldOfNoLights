#include <iostream>
#include <string>

using namespace std;

class Room {
public:
    string name;
    string description;
    string type;


    Room(const string& room_name, const string& room_description, const string& room_type)
        :name(room_name), description(room_description ), type (room_type){ }
};
class Player {
public:
    string inventory{"Empty"};
    string name;
    string characterClass;
    int health;
    int mana;
    int durability;
    int strength;

    // initalized the variables with constructor so that its easy to call and reassign value again
    Player(const string& n, const string& cclass, int h, int m, int d, int s)
        : name(n),characterClass(cclass), health(h), mana(m),durability(d),strength(s){ }
   
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

    if(action == "offer") {
        
        cout << "\nThe gate takes part of your uniquq stats..." << endl;

        if (p.characterClass == "Warrior") {

            p.strength -= 5;
            cout << "Your Durability drops to " << p.strength <<  endl;
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
void Courtyard_Event(Player& p, Room& r){
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
                p.inventory = "Greatsword";
                cout << "You get a Big ahh Greatsword" << endl;
            }
            else {
                p.inventory = "Moonstaff";
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


int main() {
    char playAgain; 
    int location{ 1 };

    cout << "Welcome to the World of No Lights" << endl;
    cout << "Do you want to be 'Mage (1)' or 'Warrior (2)': ";

    int choice;
    cin >> choice;

    string playerName;
    cout << "Enter yout character's name";
    cin >> playerName;

    Player myPlayer("Unknown", "None", 0, 0, 0, 0);

    //assigns attributes to character based on player choice (int health, int mana, int durability, int strength)
    if (choice == 1) {
        myPlayer = Player(playerName, "Mage", 20, 15, 8, 2); 
    }
    else if (choice == 2) {
        myPlayer = Player(playerName, "Warrior", 25, 0, 12, 15 );
    }
    else {
        cout << "Invalid choice. The darkness consumes you." << endl;
        return 0;
    }


    myPlayer.Intro();

    while (myPlayer.health > 0) {
        Room gate("Blood_Gate", "A 5,000-year-old scarlet gate of rusted iron.", "Vampiric");
        Room Courtyard("Courtyard", "", "");

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
            cout << "You reached the end of the demo! Congrats." << endl;
            break;
        }


    }
    return 0;
}
    
