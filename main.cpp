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
    Inventory *inventory = new Inventory();
    inventory->initialize();
    inventory->dropAllItems();
    cv::waitKey(0);
    return 0;
}