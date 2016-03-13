#include "routines/FaladorMining.h"
#include "routines/EvilChickenMining.h"
#include "routines/SkillChompaHunting.h"
#include "routines/Agility.h"
#include "routines/Magic.h"
#include "routines/Drop.h"
#include "routines/Fletching.h"
#include "routines/Fishing.h"
#include "routines/Smithing.h"
#include "routines/SaveInventory.h"
#include "routines/Crafting.h"
#define ZOOM_IN_KEY 65369
#define ZOOM_OUT_KEY 65397
#define VIEW_UP_KEY 65391
#define VIEW_DOWN_KEY 65396
using namespace std;

int main(int argc, char** argv )
{
	time_t t;
	srand((unsigned) time(&t));


    vector<string> strings;
    strings.push_back("Form");
    strings.push_back("Fire");
    strings.push_back("UseClaySink");
    strings.push_back("UseBank");
    strings.push_back("Net");
    strings.push_back("Drop");
    strings.push_back("DropUncut");
    strings.push_back("DropFishingbait");
    strings.push_back("Withdr");
    strings.push_back("DropBarbarianrod");
    strings.push_back("DropLeapingsalmon");
    strings.push_back("DropWoodcutti");
    strings.push_back("OepositAllStro");
    strings.push_back("OepositStro");
    strings.push_back("Cancel");
    strings.push_back("Mine");
    strings.push_back("MineRocks");
    strings.push_back("FaceSouth");
    strings.push_back("Clim");
    strings.push_back("Climb");
    strings.push_back("Bank");
    strings.push_back("Check");
    strings.push_back("Rebuild");
    strings.push_back("Lay");
    strings.push_back("Deposit-All");
    strings.push_back("OepositAll");
    strings.push_back("Oeposit");
    strings.push_back("Deposit");
    strings.push_back("Smith");
    strings.push_back("Enter");
    strings.push_back("Exit");

    // Create a SimString database with two person names.
    simstring::ngram_generator gen(strings.size(), false);
    simstring::writer_base<std::string> dbw(gen, "../simstring/words.db");

    // Output the retrieved strings separated by ", ".
    for (int i = 0;i < (int)strings.size();++i) {
        dbw.insert(strings[i]);
    }
    
    dbw.close();
    unique_ptr<Scene> scene(new Scene());
    unique_ptr<FaladorMining> mining(new FaladorMining());
    unique_ptr<SkillChompaHunting> hunting(new SkillChompaHunting());
    unique_ptr<EvilChickenMining> evilChickenMining(new EvilChickenMining());
    unique_ptr<Agility> agility(new Agility());
    unique_ptr<Magic> magic(new Magic());
    unique_ptr<Drop> drop(new Drop());
    unique_ptr<Fletching> fletching(new Fletching());
    unique_ptr<Fishing> fishing(new Fishing());
    unique_ptr<Smithing> smithing(new Smithing());
    unique_ptr<SaveInventory> saveInventory(new SaveInventory());
    unique_ptr<Crafting> crafting(new Crafting());

    scene->getScreen();
    if (argc == 0) {
        cout << "NO ACTION" << endl;
    } else if (strcmp(argv[1], "MINING") == 0) {
        mining->run();
    } else if (strcmp(argv[1], "HUNTING") == 0) {
        hunting->run();
    } else if (strcmp(argv[1], "EVIL_CHICKEN_MINING") == 0) {
        evilChickenMining->run();
    } else if (strcmp(argv[1], "MAGIC") == 0) {
        magic->run();
    } else if (strcmp(argv[1], "DROP") == 0) {
        drop->run();
    } else if (strcmp(argv[1], "FLETCHING") == 0) {
        fletching->run();
    } else if (strcmp(argv[1], "FISHING") == 0) {
        fishing->run();
    } else if (strcmp(argv[1], "SMITHING") == 0) {
        smithing->run();
    } else if (strcmp(argv[1], "SAVE_INVENTORY") == 0) {
        saveInventory->run();
    } else if (strcmp(argv[1], "CRAFTING") == 0) {
        crafting->run();
    } else {
        cout << "NO ACTION" << endl;
    }

    cout << "Finished!!" << endl;
    cv::waitKey(0);
    return 0;
}