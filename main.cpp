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
#include "routines/DragonhideCrafting.h"
#include "routines/GoldSmithing.h"
#define ZOOM_IN_KEY 65369
#define ZOOM_OUT_KEY 65397
#define VIEW_UP_KEY 65391
#define VIEW_DOWN_KEY 65396
using namespace std;

int main(int argc, char** argv )
{
	time_t t;
	srand((unsigned) time(&t));
    
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
    unique_ptr<DragonhideCrafting> dragonhideCrafting(new DragonhideCrafting());
    unique_ptr<GoldSmithing> goldSmithing(new GoldSmithing());

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
    } else if (strcmp(argv[1], "DRAGONHIDE_CRAFTING") == 0) {
        dragonhideCrafting->run();
    } else if (strcmp(argv[1], "GOLD_SMITHING") == 0) {
        goldSmithing->run();
    } else {
        cout << "NO ACTION" << endl;
    }

    cout << "Finished!!" << endl;
    return 0;
}