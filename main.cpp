#include "ImageObject.h"
#include "Inventory.h"
#include "Scene.h"
using namespace std;

int main(int argc, char** argv )
{
	time_t t;
	srand((unsigned) time(&t));
    Scene *scene = new Scene();
    scene->redraw();
	// moveToPosition(0, 0);
 //    cv::Mat sceneImage = ImageFromDisplay(1640, 1050);
 //    // ImageObject *compass = new ImageObject("../images/compass.png", imgScene);
 //    // compass->initialize();
 //    // compass->draw();
 //    // compass->clickOn();

    Inventory *inventory = new Inventory();
    inventory->initialize();
    inventory->dropAllItems();
    imshow( "W", scene->getSceneImage());
    cv::waitKey(0);
    return 0;
}