#ifndef Minesite_cpp
#define Minesite_cpp
	#include "Minesite.h"

	Minesite::Minesite() {
        interfaceMap.reset(new Map());
        interfaceMap->initialize();
        scene.reset(new Scene());
        inventory.reset(new Inventory());
        dialog.reset(new Dialog());
        vector<unique_ptr<ImageObject>>().swap(rocks);

        DIR *dirObj = opendir("../images/Rocks");
        struct dirent *entry;
        vector<string> rockImages;
        while ((entry = readdir(dirObj)) != NULL)
        {
            if (entry->d_name[0] == '.') {
                continue;
            }

            getFilesInFolder((string)"../images/Rocks/" + entry->d_name, rockImages);
            unique_ptr<ImageObject> rock(new ImageObject());
            for(vector<string>::iterator iter = rockImages.begin(); iter != rockImages.end(); ++iter) {
                unique_ptr<Template> tempObj(new Template(*iter));
                rock->clickMarginHeight = 10;
                rock->clickMarginWidth = 10;
                rock->addTemplate(move(tempObj));
            }
            rocks.push_back(move(rock));
            rockImages.clear();
        }

        closedir(dirObj);
	}

	Minesite::~Minesite() {
	}

    void Minesite::mine(string miningLocation) {
        while(!inventory->full) {
            if (chance(1000)) {
                nsleep(1000 * 60);
            }
            if (chance(100)) {
                nsleep(1000 * 30);
            }
            inventory->initialize();
            random_shuffle(rocks.begin(), rocks.end());
            for(vector<unique_ptr<ImageObject>>::iterator iter = rocks.begin(); iter != rocks.end(); ++iter) {
                if ((*iter)->initialize()) {
                    (*iter)->clickOn(RIGHT_CLICK);
                    nsleep(5);
                    if (dialog->initialize()) {
                        if (dialog->match("MineRocks")) {
                            dialog->select("Cancel");
                            continue;
                        } else if (dialog->select("Mine")) {
                            scene->redraw();
                            inventory->markEmptyCells();
                            waitForOre(inventory->numItems);
                            interfaceMap->goTo(miningLocation, 45);
                            break;
                        } else{
                            dialog->select("Cancel");
                        }
                    }
                }
                scene->redraw();
            }

            nsleep(100);
        }
    }

    void Minesite::waitForOre(int startingAmount, int retries) {
        cout << "Retries: " << retries << endl;
        if (retries <= 0) {
            return;
        }
        if (inventory->numItems > startingAmount) {
            return;
        }
        nsleep(1000);
        scene->redraw();
        inventory->markEmptyCells();
        waitForOre(startingAmount, --retries);
    }
#endif