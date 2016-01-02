
#include "ImageObject.h"
#include "Inventory.h"
#include "Scene.h"
#include "Map.h"
#include "FaladorLadder.h"
#include "FaladorBank.h"
#include "MiningGuildLadder.h"
#include "Minesite.h"
#include "WindowFilter.h"
#include "CornerFilter.h"
#include "ErodeFilter.h"
#define ZOOM_IN_KEY 65369
#define ZOOM_OUT_KEY 65397
#define VIEW_UP_KEY 65391
using namespace std;

int main(int argc, char** argv )
{
	time_t t;
	srand((unsigned) time(&t));


    vector<string> strings;
    strings.push_back("Drop");
    strings.push_back("DropUncut");
    strings.push_back("Cancel");
    strings.push_back("Examine");
    strings.push_back("Use");
    strings.push_back("Craft");
    strings.push_back("Mine");
    strings.push_back("MineRocks");
    strings.push_back("Yournanage");
    strings.push_back("YouSiving");
    strings.push_back("Youmanage");
    strings.push_back("Youswing");
    strings.push_back("Clim");
    strings.push_back("Climb");
    strings.push_back("Bank");
    strings.push_back("Deposit-All");
    strings.push_back("OepositAll");
    strings.push_back("Oeposit");

    // Create a SimString database with two person names.
    simstring::ngram_generator gen(strings.size(), false);
    simstring::writer_base<std::string> dbw(gen, "../simstring/words.db");

    // Output the retrieved strings separated by ", ".
    for (int i = 0;i < (int)strings.size();++i) {
        dbw.insert(strings[i]);
    }
    
    dbw.close();

    Scene *scene = new Scene();
    scene->getScreen();

    unique_ptr<Object> compass(new Object());
    compass->width = 19;
    compass->height = 19;
    unique_ptr<ImageObject> worldMap (new ImageObject("../images/WorldMap.png"));
    if (worldMap->initialize()) {
        compass->topLeft = cv::Point(worldMap->topLeft.x - 154, worldMap->topLeft.y - 150);
    } else {
        unique_ptr<ImageObject> helpButton (new ImageObject("../images/HelpButton.png"));
        if (helpButton->initialize()) {
            compass->topLeft = cv::Point(worldMap->topLeft.x - 154, worldMap->topLeft.y);
        } else {
            string error = "Could not locate compass";
            cout << error << endl;
            throw(error);
        }
    }
    compass->initialize();
    // compass->clickOn();
    // nsleep(5);
    // keypress(ZOOM_OUT_KEY, 3000);
    // keypress(VIEW_UP_KEY, 3000);

    unique_ptr<Inventory> inventory(new Inventory());
    unique_ptr<FaladorLadder> faladorLadder(new FaladorLadder());
    unique_ptr<FaladorBank> bank(new FaladorBank());
    unique_ptr<MiningGuildLadder> miningGuildLadder(new MiningGuildLadder());
    unique_ptr<Map> interfaceMap(new Map());
    unique_ptr<Minesite> minesite(new Minesite());
    while (true) {
        interfaceMap->initialize();
        inventory->initialize();

        if (inventory->full) {
            cout << "INVENTORY IS FULL" << endl;
            if (interfaceMap->currentPlane == "FALADOR") {
                while (true) {
                    if (interfaceMap->goTo("FALADOR_BANK", 10)) {
                        break;
                    }
                }
                while(true) {
                    bank->use();
                    if (bank->open()) {
                        break;
                    }
                }
                inventory->bankAllItems();

                while (true) {
                    bank->close();
                    if (!bank->open()) {
                        break;
                    }
                }
            } else {
                while (true) {
                    if (interfaceMap->goTo("MINING_GUILD_LADDER")) {
                        break;
                    }
                }
                while(true) {
                    if (miningGuildLadder->use()) {
                        break;
                    }
                }
            }
        } else {
            if (interfaceMap->currentPlane == "FALADOR") {
                while (true) {
                    if (interfaceMap->goTo("FALADOR_LADDER")) {
                        break;
                    }
                }
                while(true) {
                    if (faladorLadder->use()) {
                        break;
                    }
                }
            } else {
                while (true) {
                    if (interfaceMap->goTo("MINING_GUILD_1")) {
                        break;
                    }
                }
                minesite->mine("MINING_GUILD_1");
            }

        }
    }

    cout << "Finished!!" << endl;
    cv::waitKey(0);
    return 0;
}