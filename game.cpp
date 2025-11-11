#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int randBetween(int a, int b) { return a + rand() % (b - a + 1); }

int main() {

    srand((unsigned)time(NULL));

    string name;
    int maxHP = 70;
    int hp = maxHP;
    int honor = 0;
    int choice;
    int potions = 2; // healing items
    int focus = 3;   // special attack resource
    int playerBuffTurns = 0; // from potion or focus: increases player damage for next N attacks
    int playerDamageBonus = 0;
    int enemyBuffTurns = 0; // when focus used, enemy does a bit more damage for N turns
    int enemyDamageBonus = 0;
    int potionResistTurns = 0; // when >0, enemy damage per hit is capped to 4

    cout << "Enter your Samurai's name: ";
    getline(cin, name);

    cout << "\n=== THE SAMURAI'S PATH ===\n";
    cout << "The wind carries stories of your past, " << name << ".\n";
    cout << "A past filled with betrayal, wandering… and unanswered questions.\n";

    // ----------- FOREST (HARDER) -----------
    cout << "\nYou walk through a misty forest.\n";
    cout << "A wounded ronin steps from behind a cedar tree.\n";
    cout << "\"Stay back... or I will strike!\" he snarls.\n";

    cout << "\n1) Fight him\n";
    cout << "2) Try to calm him\n";
    cout << "> ";
    cin >> choice;

    if(choice == 1) {
        int enemyHP = randBetween(35, 55); // stronger variability
        cout << "\nYou grip your katana. \"Then prepare yourself.\"\n";

        while(hp > 0 && enemyHP > 0) {
            cout << "\n-- Skirmish --\n";
            cout << "1) Quick Strike (- no focus)\n";
            cout << "2) Strong Strike (uses 1 focus)\n";
            cout << "3) Drink potion (" << potions << " left)\n";
            cout << "> ";
            cin >> choice;

            int lastPlayerDmg = 0;
            if(choice == 1) {
                int dmg = randBetween(8, 14);
                if(playerBuffTurns>0) dmg += playerDamageBonus;
                enemyHP -= dmg;
                lastPlayerDmg = dmg;
                cout << "You hit the ronin for " << dmg << " damage.\n";
                if(playerBuffTurns>0) { playerBuffTurns--; if(playerBuffTurns==0) playerDamageBonus=0; }
            } else if(choice == 2 && focus > 0) {
                int dmg = randBetween(18, 26);
                if(playerBuffTurns>0) dmg += playerDamageBonus;
                enemyHP -= dmg;
                focus -= 1;
                // applying short-term player buff and enemy increased aggression
                playerBuffTurns = 2; playerDamageBonus = 10; // player does +10 for next 2 attacks
                enemyBuffTurns = 2; enemyDamageBonus = 6;   // enemy does +6 for next 2 attacks
                lastPlayerDmg = dmg;
                cout << "You unleash a strong strike for " << dmg << " damage. (Focus " << focus << ")\n";
            } else if(choice == 2) {
                cout << "You lack focus and stumble.\n";
            } else if(choice == 3 && potions > 0) {
                int heal = 20;
                hp += heal;
                if(hp > maxHP) hp = maxHP;
                potions -= 1;
                // potion grants strength for next two attacks and 1-turn resistance
                playerBuffTurns = 2; playerDamageBonus = 12; // stronger bonus from potion
                potionResistTurns = 1;
                lastPlayerDmg = 0;
                cout << "You drink a potion, heal " << heal << " HP and feel strength for your next two attacks.\n";
            } else {
                cout << "Invalid action. You hesitate.\n";
            }

            if(enemyHP > 0) {
                int edmg = randBetween(8, 16);
                if(enemyBuffTurns>0) edmg += enemyDamageBonus;
                // enemy chance to critical
                if(randBetween(1, 10) > 8) { edmg += 6; cout << "He finds an opening! Critical damage.\n"; }
                // apply potion resistance cap
                if(potionResistTurns>0) {
                    if(edmg > 4) edmg = 4;
                    potionResistTurns = 0; // only for one enemy hit
                    cout << "Your resistance reduces the incoming blow!\n";
                }
                hp -= edmg;
                cout << "You dealt " << lastPlayerDmg << " damage; The ronin strikes back for " << (edmg>0?edmg:0) << " damage.\n";
                if(enemyBuffTurns>0) { enemyBuffTurns--; if(enemyBuffTurns==0) enemyDamageBonus=0; }
            }

            // clamp displayed HP to not show negatives
            int dispHP = hp>0?hp:0;
            int dispEnemy = enemyHP>0?enemyHP:0;
            cout << "Your HP: " << dispHP << " | Enemy HP: " << dispEnemy << "\n";
        }

        if(hp <= 0) {
            cout << "\nYou were felled by the ronin. Your path ends in the forest.\n";
            cout << "Final Honor Score: " << honor << "\n";
            return 0;
        }

        cout << "You finish the encounter. The ronin collapses.\n";
        honor -= 1;
        cout << "Your heart hardens. (-1 Honor)\n";
    }
    else {
        cout << "\n\"Put down the blade,\" you say.\n";
        cout << "He freezes… then breaks down, tears mixing with the mud.\n";
        cout << "\"Forgive me… I was afraid.\"\n";
        cout << "You guide him to safety.\n";
        honor += 2;
        cout << "(+2 Honor)\n";
    }

    // ----------- VILLAGE -----------
    cout << "\nYou approach a small village. Houses are burnt, children crying.\n";
    cout << "A farmer grabs your sleeve.\n";
    cout << "\"Samurai-sama, please… thieves have taken everything!\"\n";

    cout << "\n1) Help them\n2) Demand payment for help\n3) Refuse and leave\n> ";
    cin >> choice;

    if(choice == 1) {
        cout << "\nYou stand before the thieves.\n";
        cout << "\"Leave this place now,\" you warn.\n";
        cout << "They test you — a tougher fight than expected.\n";
        int thievesHP = randBetween(40, 65);
        while(hp > 0 && thievesHP > 0) {
            cout << "1) Attack\n2) Defend\n3) Use potion (" << potions << ")\n> ";
            cin >> choice;
            int lastPlayerDmg = 0;
            if(choice == 1) { 
                int pd = randBetween(10, 18);
                if(playerBuffTurns>0) pd += playerDamageBonus;
                thievesHP -= pd; 
                lastPlayerDmg = pd;
                if(playerBuffTurns>0) { playerBuffTurns--; if(playerBuffTurns==0) playerDamageBonus=0; }
            }
            else if(choice == 2) { hp += 5; if(hp > maxHP) hp = maxHP; }
            else if(choice == 3 && potions>0) { 
                int heal = 20; hp += heal; if(hp>maxHP) hp=maxHP; potions--; 
                playerBuffTurns = 2; playerDamageBonus = 12;
                potionResistTurns = 1;
                cout << "You drink a potion, heal "<<heal<<" HP and gain strength for your next two attacks. Your resistance rises for the next enemy blow.\n";
            }
            if(thievesHP>0) {
                int d=randBetween(10,18);
                if(enemyBuffTurns>0) d += enemyDamageBonus;
                if(potionResistTurns>0) { if(d>4) d=4; potionResistTurns=0; cout<<"Your resistance reduces the incoming blow!\n"; }
                hp -= d;
                cout << "You dealt "<< lastPlayerDmg <<" damage; They strike for "<<d<<"\n";
                if(enemyBuffTurns>0) { enemyBuffTurns--; if(enemyBuffTurns==0) enemyDamageBonus=0; }
            }
            int dispHP2 = hp>0?hp:0;
            int dispTh = thievesHP>0?thievesHP:0;
            cout << "Your HP:"<<dispHP2<<" | Thieves:"<<dispTh<<"\n";
        }
    if(hp<=0) { cout<<"You fall protecting the villagers."<<"\n"; return 0; }
        honor += 2;
        cout << "Villagers bow. (+2 Honor)\n";
    }
    else if(choice == 2) {
        cout << "\nThe villagers tremble as they hand you coins.\n";
        cout << "You protect them… for a price.\n";
        honor -= 1;
        cout << "(-1 Honor)\n";
    }
    else {
        cout << "\nYou walk past the suffering faces.\n";
        cout << "A child silently watches you disappear. (-1 Honor)\n";
        honor -= 1;
    }

    // ----------- MARKETPLACE: new situation -----------
    cout << "\nOn a dusty road you meet a traveling trader.\n";
    cout << "He offers a strange elixir for one coin and a map piece for free.\n";
    cout << "1) Buy elixir (gain 1 potion)\n2) Take the map and move on\n3) Ignore him\n> ";
    cin >> choice;
    if(choice == 1) { potions += 1; cout<<"You buy the elixir and pocket another potion.\n"; }
    else if(choice == 2) { honor += 1; cout<<"You accept the map; the trader thanks you. (+1 Honor)\n"; }
    else { cout<<"You ignore the trader and continue.\n"; }

    // ----------- SWAMP AMBUSH: new situation (adds length & danger) -----------
    cout << "\nA foul swamp crosses your path. Mist thick; something moves beneath it.\n";
    cout << "1) Move carefully\n2) Rush through\n> ";
    cin >> choice;
    if(choice == 1) {
        // careful: less damage but possible tripped
        if(randBetween(1,10) > 7) { int dmg=randBetween(8,14); hp-=dmg; cout<<"You slip on a root and are bitten by swamp leeches (-"<<dmg<<" HP).\n"; }
        else cout<<"You pass the swamp with only the chill in your bones.\n";
    } else {
        // rushing risks more damage but faster
        int dmg = randBetween(12, 22);
        hp -= dmg;
        cout << "The swamp grabs you; you push through but lose "<<dmg<<" HP.\n";
    }
    if(hp<=0) { cout<<"The swamp claims you.\n"; return 0; }

    // ----------- TEMPLE (riddle) -----------
    cout << "\nYou reach an abandoned temple.\n";
    cout << "A stone door with faded carvings whispers a riddle:\n";
    cout << "\"I speak without a mouth and hear without ears. What am I?\"\n";

    string answer;
    cout << "> ";
    cin >> answer;

    if(answer == "echo" || answer == "Echo") {
        cout << "The stone shifts open with a deep groan.\n";
        cout << "You feel clarity wash over your spirit.\n";
        honor += 1;
        focus += 1;
        cout << "(Focus +1)\n";
    }
    else {
        cout << "The door remains still. A cold presence pushes you back.\n";
        cout << "Your failure weighs on your mind.\n";
        honor -= 1;
    }

    // ----------- MOUNTAIN PASS: small choice that can lengthen journey -----------
    cout << "\nA narrow mountain pass stands between you and the fortress.\n";
    cout << "1) Take the high route (safer but longer)\n2) Take the low pass (quicker but dangerous)\n> ";
    cin >> choice;
    if(choice == 1) { cout << "You take the long route, the journey lengthens but you avoid an ambush.\n"; }
    else {
        cout << "You take the low pass and are ambushed by bandits!\n";
        int ambHP = randBetween(30,50);
        while(hp>0 && ambHP>0) {
            // player attacks (you fight through the ambush)
            int lastPlayerDmg = randBetween(10,16);
            if(playerBuffTurns>0) { lastPlayerDmg += playerDamageBonus; playerBuffTurns--; if(playerBuffTurns==0) playerDamageBonus=0; }
            ambHP -= lastPlayerDmg;
            if(ambHP>0) { 
                int d=randBetween(10,18); 
                if(enemyBuffTurns>0) d += enemyDamageBonus;
                if(potionResistTurns>0) { if(d>4) d=4; potionResistTurns=0; cout<<"Your resistance reduces the incoming blow!\n"; }
                hp -= d; 
                cout<<"You dealt "<<lastPlayerDmg<<"; They hit you for "<<d<<"\n"; 
                if(enemyBuffTurns>0) { enemyBuffTurns--; if(enemyBuffTurns==0) enemyDamageBonus=0; }
            } else {
                cout<<"You dealt "<<lastPlayerDmg<<" and defeated the ambushers.\n";
            }
        }
        if(hp<=0) { cout<<"You die in the pass.\n"; return 0; }
        honor -= 1; cout<<"You survive, scarred. (-1 Honor)\n";
    }

    // ----------- CASTLE - FINAL BATTLE (multi-phase) -----------
    cout << "\nYour journey leads to the old fortress where the traitor waits.\n";
    cout << "He steps from the shadows.\n\n";
    cout << "\"So… you survived. Come then. Let us finish this.\"\n";

    int enemyHP = 95; // tougher final boss
    int phase = 1;

    while(hp > 0 && enemyHP > 0) {
        if(enemyHP <= 40 && phase == 1) { phase = 2; cout<<"The traitor's eyes burn; he enters an enraged phase!\n"; }

        cout << "\n=== Duel (Phase "<<phase<<") ===\n";
        cout << "1) Attack\n2) Defend (recover small HP)\n3) Special Strike (uses 1 focus)\n4) Use potion ("<<potions<<")\n> ";
        cin >> choice;

        int lastPlayerDmg = 0;
        if(choice == 1) {
            int dmg = randBetween(10,18);
            if(playerBuffTurns>0) dmg += playerDamageBonus;
            enemyHP -= dmg;
            lastPlayerDmg = dmg;
            cout << "You slash for "<<dmg<<".\n";
            if(playerBuffTurns>0) { playerBuffTurns--; if(playerBuffTurns==0) playerDamageBonus=0; }
        } else if(choice == 2) {
            cout << "You take a defensive stance, study his moves.\n";
            hp += 6; if(hp>maxHP) hp = maxHP;
        } else if(choice == 3 && focus>0) {
            int dmg = randBetween(28,36);
            if(playerBuffTurns>0) dmg += playerDamageBonus;
            enemyHP -= dmg; focus--;
            // strong focus strike: immediate damage plus short buff and enemy gets more aggressive
            playerBuffTurns = 2; playerDamageBonus = 14; // strong focus gives +14 for next two attacks
            enemyBuffTurns = 2; enemyDamageBonus = 8;    // enemy deals +8 for next two attacks
            lastPlayerDmg = dmg;
            cout << "You unleash a focused strike for "<<dmg<<". (Focus "<<focus<<")\n";
        } else if(choice == 3) {
            cout << "You have no focus to fuel a special strike.\n";
        } else if(choice == 4 && potions>0) {
            int heal = 20; hp += heal; if(hp>maxHP) hp=maxHP; potions--; 
            playerBuffTurns = 2; playerDamageBonus = 12;
            potionResistTurns = 1;
            cout<<"You drink a potion, heal "<<heal<<" HP and gain strength for your next two attacks. Your resistance rises for the next enemy blow.\n";
        } else {
            cout << "You fumble and lose the initiative.\n";
        }

        if(enemyHP>0) {
            int edmg = randBetween(12, 22);
            if(phase==2) edmg += randBetween(4,10); // stronger in phase 2
            if(enemyBuffTurns>0) edmg += enemyDamageBonus;
            if(randBetween(1,10)>8) { cout<<"The traitor strikes true!\n"; edmg += 6; }
            if(potionResistTurns>0) { if(edmg>4) edmg = 4; potionResistTurns = 0; cout<<"Your resistance reduces the incoming blow!\n"; }
            hp -= edmg;
            cout<<"You dealt "<< lastPlayerDmg <<" damage; Enemy deals "<< (edmg>0?edmg:0) <<" damage.\n";
            if(enemyBuffTurns>0) { enemyBuffTurns--; if(enemyBuffTurns==0) enemyDamageBonus=0; }
        }

        int dispHP3 = hp>0?hp:0;
        int dispEnemy3 = enemyHP>0?enemyHP:0;
        cout << "Your HP: "<<dispHP3<<" | Enemy HP: "<<dispEnemy3<<" | Focus: "<<focus<<" | Potions: "<<potions<<"\n";
    }

    if(hp <= 0) {
        cout << "\nYou fall to your knees. Darkness closes in.\n";
        cout << "Your path ends here.\n";
        return 0;
    }

    cout << "\nThe traitor kneels, defeated.\n";
    cout << "\"End it… or show mercy. The choice is yours...\"\n";

    cout << "1) Spare him\n2) Kill him\n> ";
    cin >> choice;

    if(choice == 1) {
        cout << "\nYou lower your blade.\n";
        cout << "\"Live with your shame,\" you command.\n";
        honor += 2;
    }
    else {
        cout << "\nYour blade finds its mark.\n";
        cout << "Justice—cold and absolute.\n";
        honor -= 2;
    }

    // ----------- ENDINGS BASED ON TOTAL HONOR + FIGHT -----------

    cout << "\n=== Your Ending ===\n";

    if(honor >= 4) {
        cout << "Legend of Honor:\n";
        cout << "Your mercy, courage, and discipline spread across the land.\n";
        cout << "People speak your name with reverence.\n";
    }
    else if(honor <= -4) {
        cout << "Shadow of Vengeance:\n";
        cout << "Your blade delivered justice, but your heart grew dark.\n";
        cout << "Fear follows the whisper of your name.\n";
    }
    else {
        cout << "The Wandering Soul:\n";
        cout << "Neither hero nor monster… simply a man who walked his own path.\n";
    }

    cout << "\nFinal Honor Score: " << honor << "\n";
    cout << "=== THE END ===\n";

    return 0;
}
