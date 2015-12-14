
#include "ImageObject.h"
#include "Inventory.h"
#include "Scene.h"
#define ZOOM_IN_KEY 65369
#define ZOOM_OUT_KEY 65397
#define VIEW_UP_KEY 65391
using namespace std;

void waitForMiningFinished(Scene *scene, OcrObject *eventLine, int retries = 20) {
    if (retries <= 0) {
        return;
    }
    cout << "Waiting to get ore. Try: " << retries << endl;
    nsleep(1000);
    scene->redraw();
    eventLine->initialize();
    cout << "Event line best guess: " << eventLine->bestGuess << endl;
    if (!eventLine->match("Yournanage") && !eventLine->match("Youmanage")) {
        waitForMiningFinished(scene, eventLine, --retries);
    }
}

void waitForSwing(Scene *scene, OcrObject *eventLine, int retries = 5) {
    if (retries <= 0) {
        return;
    }
    cout << "Waiting for pick to swing. Try: " << retries << endl;
    nsleep(1000);
    scene->redraw();
    eventLine->initialize();
    cout << "Event line best guess: " << eventLine->bestGuess << endl;
    if (!eventLine->match("YouSiving") && !eventLine->match("Youswing")) {
        waitForSwing(scene, eventLine, --retries);
    } else {
        waitForMiningFinished(scene, eventLine);
    }
}

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
    strings.push_back("MineClay");
    strings.push_back("MineClag");
    strings.push_back("Yournanage");
    strings.push_back("YouSiving");
    strings.push_back("Youmanage");
    strings.push_back("Youswing");

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
    compass->clickOn();
    keypress(ZOOM_OUT_KEY, 3000);
    keypress(VIEW_UP_KEY, 3000);

    vector<ImageObject*> imageObjects;

    DIR *dirObj = opendir("../images/Rocks");
    struct dirent *entry;
    vector<string> rockImages;
    while ((entry = readdir(dirObj)) != NULL)
    {
        if (entry->d_name[0] == '.') {
            continue;
        }

        getFilesInFolder((string)"../images/Rocks/" + entry->d_name, rockImages);
        ImageObject *currRock = new ImageObject();
        for(vector<string>::iterator iter = rockImages.begin(); iter != rockImages.end(); ++iter) {
            unique_ptr<ImageTemplate> tempObj(new ImageTemplate(*iter));
            currRock->clickMarginHeight = 10;
            currRock->clickMarginWidth = 10;
            currRock->addTemplate(move(tempObj));
        }
        imageObjects.push_back(currRock);
        rockImages.clear();
    }

    closedir(dirObj);

    ImageObject *chatUpArrow = new ImageObject("../images/ChatUpArrow.png");
    cout << "Finding chat up arrow" << endl;
    chatUpArrow->initialize();
    OcrObject *eventLine = new OcrObject();
    eventLine->threshold = 150;
    eventLine->width = 528;
    eventLine->height = 16;
    eventLine->topLeft = cv::Point(chatUpArrow->topLeft.x - 528, chatUpArrow->topLeft.y + 126);
    cout << "Finding event line" << endl;
    eventLine->initialize();
    cout << "MADE IT" << endl;
    cout << flush;

    Dialog* dialog = new Dialog();

    Inventory *inventory = new Inventory();
    while(true) {
        if (chance(1000)) {
            nsleep(1000 * 60);
        }
        if (chance(100)) {
            nsleep(1000 * 30);
        }
        scene->redraw();
        inventory->initialize();
        if (inventory->full) {
            inventory->dropAllItems();
        }
        cout << "Running: " << endl;
        random_shuffle(imageObjects.begin(), imageObjects.end());
        for(std::vector<ImageObject*>::iterator iter = imageObjects.begin(); iter != imageObjects.end(); ++iter) {
            if ((*iter)->initialize()) {
                (*iter)->clickOn(RIGHT_CLICK);
                nsleep(5);
                if (dialog->initialize()) {
                    if (dialog->match("MineRocks") || dialog->match("MineClay") || dialog->match("MineClag")) {
                        dialog->select("Cancel");
                        continue;
                    } else if (dialog->select("Mine")) {
                        waitForSwing(scene, eventLine);
                        break;
                    } else{
                        dialog->select("Cancel");
                    }
                }
            }
        }

        cv::waitKey(100);
    }
    cout << "Finished!!" << endl;
    cv::waitKey(0);
    return 0;
}