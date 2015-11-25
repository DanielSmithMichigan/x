#include "utilities.h"
#include "interface.h"
#include "ImageObject.h"

using namespace std;

int main(int argc, char** argv )
{
    cv::Mat imgScene = ImageFromDisplay(1640, 1050);
    ImageObject *compass = new ImageObject("../images/compass.png", imgScene);
    compass->initialize();
    compass->draw();
    compass->clickOn();
    imshow( "Good Matches & Object detection", imgScene );
    cv::waitKey(0);
    return 0;
}