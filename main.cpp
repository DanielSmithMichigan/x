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
    strings.push_back("Mine");

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

    vector<ImageObject*> imageObjects;

    ImageObject *silverRock1 = new ImageObject();
    silverRock1->addTemplate(new ImageTemplate("../images/rocks/silver_01/1.png"));
    silverRock1->addTemplate(new ImageTemplate("../images/rocks/silver_01/2.png"));
    silverRock1->addTemplate(new ImageTemplate("../images/rocks/silver_01/3.png"));
    silverRock1->addTemplate(new ImageTemplate("../images/rocks/silver_01/4.png"));
    silverRock1->addTemplate(new ImageTemplate("../images/rocks/silver_01/5.png"));

    ImageObject *silverRock2 = new ImageObject();
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/1.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/2.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/3.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/4.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/5.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/6.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/7.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/8.png"));
    silverRock2->addTemplate(new ImageTemplate("../images/rocks/silver_02/9.png"));

    ImageObject *tinRock1 = new ImageObject();
    tinRock1->addTemplate(new ImageTemplate("../images/rocks/tin_01/1.png"));
    tinRock1->addTemplate(new ImageTemplate("../images/rocks/tin_01/2.png"));
    tinRock1->addTemplate(new ImageTemplate("../images/rocks/tin_01/3.png"));
    tinRock1->addTemplate(new ImageTemplate("../images/rocks/tin_01/4.png"));

    imageObjects.push_back(silverRock1);
    imageObjects.push_back(silverRock2);
    imageObjects.push_back(tinRock1);

    Dialog* dialog = new Dialog();

    Inventory *inventory = new Inventory();
    int x = 50;
    while(--x > 0) {
        scene->redraw();
        inventory->initialize();
        if (inventory->full) {
            inventory->dropAllItems();
        }
        for(std::vector<ImageObject*>::iterator iter = imageObjects.begin(); iter != imageObjects.end(); ++iter) {
            if ((*iter)->initialize()) {
                (*iter)->clickOn(RIGHT_CLICK);
                nsleep(5);
                dialog->initialize();
                if (dialog->select("Mine")) {
                    nsleep(20000);
                    break;
                } else{
                  dialog->select("Cancel");
                }
            }
        }

        imshow("W", scene->getSceneImage());
        cv::waitKey(100);
    }
    cout << "Finished!!" << endl;
    cv::waitKey(0);
    return 0;
}