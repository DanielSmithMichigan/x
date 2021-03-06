#ifndef imageUtilities_cpp
#define imageUtilities_cpp
    #include "imageUtilities.h"

    using namespace std;

    bool imagesEqual(cv::Mat a, cv::Mat b, float threshold) 
    {    
        cv::Point topLeft;
        findImage(a, b, topLeft, threshold);
        return topLeft.x == 0 && topLeft.y == 0;
    }

    cv::Mat ImageFromDisplay(int Width, int Height, int x, int y)
    {
        Display* display = XOpenDisplay(NULL);
        Window root = DefaultRootWindow(display);
        XWindowAttributes attributes = {0};
        XGetWindowAttributes(display, root, &attributes);
        XImage* img = XGetImage(display, root, x, y, Width, Height, AllPlanes, ZPixmap);
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
        XDestroyImage(img);
        XCloseDisplay(display);
        return scene;
    }

    void findImage(cv::Mat &img_scene, cv::Mat &img_object, cv::Point &topLeft, float threshold)
    {
        cv::Mat result;
        matchTemplate( img_scene, img_object, result, CV_TM_SQDIFF_NORMED );
        double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
        topLeft.x = -1;
        topLeft.y = -1;
        if (minVal < threshold) {
            topLeft.x = minLoc.x;
            topLeft.y = minLoc.y;
        }
    }


#endif