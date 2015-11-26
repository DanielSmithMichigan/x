#ifndef imageUtilities_cpp
#define imageUtilities_cpp
    #include "imageUtilities.h"

    using namespace std;

    cv::Mat ImageFromDisplay(int Width, int Height)
    {
        Display* display = XOpenDisplay(NULL);
        Window root = DefaultRootWindow(display);
        XWindowAttributes attributes = {0};
        XGetWindowAttributes(display, root, &attributes);
        XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
        if (!img->data) {
            cout << "No image data";
            throw("No image data");
        }
        cv::Mat scene = cv::Mat(Height, Width, img->bits_per_pixel > 24 ? CV_8UC4 : CV_8UC3, img->data);
        if (!scene.data) {
            cout << "Error reading scene";
            throw("Error reading scene");
        }
        cvtColor(scene, scene, CV_BGRA2BGR);
        XFree(img);
        XCloseDisplay(display);
        return scene;
    }

    void findImage(cv::Mat &img_scene, cv::Mat &img_object, cv::Point &topLeft, float threshold)
    {
        cv::Mat result;
        matchTemplate( img_scene, img_object, result, CV_TM_SQDIFF_NORMED );
        double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
        imshow("W", img_scene);
        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
        if (minVal < threshold) {
            topLeft.x = minLoc.x;
            topLeft.y = minLoc.y;
        }
    }


#endif