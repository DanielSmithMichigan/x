#include "utilities.h"
#include "interface.h"
#include "ClickableObject.h"

using namespace std;

int main(int argc, char** argv )
{
    cv::Mat img_scene = ImageFromDisplay(1640, 1050);
    ClickableObject *compass = new ClickableObject("../images/compass.png", img_scene, CV_RGB(255, 255, 255));
    compass->initialize();
    compass->clickOn();
    // imshow( "Good Matches & Object detection", img_scene );
    cv::waitKey(0);
    return 0;
}