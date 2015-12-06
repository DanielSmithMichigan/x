#include "ImageObject.h"
#include "Inventory.h"
#include "Scene.h"
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
    strings.push_back("Cancel");
    strings.push_back("Examine");
    strings.push_back("Use");
    strings.push_back("Craft");

    // Create a SimString database with two person names.
    simstring::ngram_generator gen(strings.size(), false);
    simstring::writer_base<std::string> dbw(gen, "../simstring/words.db");

    // Output the retrieved strings separated by ", ".
    for (int i = 0;i < (int)strings.size();++i) {
        dbw.insert(strings[i]);
    }
    
    dbw.close();

    Scene *scene = new Scene();
    scene->redraw();

    ImageObject *swordSymbol = new ImageObject("../images/sword_symbol.png");
    swordSymbol->initialize();
    Object *compass = new Object();
    compass->width = 17;
    compass->height = 17;
    compass->topLeft = cv::Point(swordSymbol->topLeft.x + 53, swordSymbol->topLeft.y - 660);
    compass->initialize();
    compass->clickOn();
    keypress(ZOOM_OUT_KEY, 3000);
    keypress(VIEW_UP_KEY, 3000);
    // Inventory *inventory = new Inventory();
    // inventory->initialize();
    // inventory->dropAllItems();
    cv::waitKey(0);
    return 0;
}