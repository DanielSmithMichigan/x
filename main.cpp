#include "utilities.cpp"
#include "interface.cpp"

using namespace std;

int main(int argc, char** argv )
{
    // cv::Mat tin = cv::imread("../images/tin.png", CV_LOAD_IMAGE_COLOR);
    // if (!tin.data) {
    //     throw("Error reading scene");
    // }
    // cv::Mat tin_mined = cv::imread("../images/tin_mined.png", CV_LOAD_IMAGE_COLOR);
    // if (!tin_mined.data) {
    //     throw("Error reading scene");
    // }
    // cv::Mat img_scene;
    // while(true) {
    //     cv::waitKey(100);
    //     cv::Mat img_scene = ImageFromDisplay(800, 800);
    //     img_scene = MatchAgainst(img_scene, tin, CV_RGB(255, 255, 255), "TIN");
    //     img_scene = MatchAgainst(img_scene, tin_mined, CV_RGB(255, 0, 0), "MINED");
    //     imshow( "Good Matches & Object detection", img_scene );
    // }
    click(RIGHT_CLICK);
    return 0;
}