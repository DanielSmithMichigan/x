#ifndef utilities_cpp
#define utilities_cpp
    #include "utilities.h"

    float distanceTo(int x1, int y1, int x2, int y2) {
        return sqrt(
            (abs(x1 - x2) * abs(x1 - x2))
            + (abs(y1 - y2) * abs(y1 - y2))
        );
    }

    int randomBetween(int min, int max) {
        return rand()%(max-min + 1) + min;
    }

    void nsleep(long milliseconds)
    {
       milliseconds += randomBetween(0, milliseconds * .5);
       cout << "Sleep time: " << milliseconds << endl;
       struct timespec req, rem;

       if(milliseconds > 999)
       {   
            req.tv_sec = (int)(milliseconds / 1000);                            /* Must be Non-Negative */
            req.tv_nsec = (milliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
       }   
       else
       {   
            req.tv_sec = 0;                         /* Must be Non-Negative */
            req.tv_nsec = milliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
       }   

       nanosleep(&req , &rem);
    }

    bool chance(int n) {
        return randomBetween(0, n+2) > n;
    }

    int absMax(int amount, int maxAmount) {
        if (amount > 0) {
            amount = min(amount, maxAmount);
        } else {
            amount = max(amount, -1 * maxAmount);
        }
        return amount;
    }

    void getFilesInFolder(string path, vector<string> &output) {
        DIR *dirObj = opendir(path.c_str());

        struct dirent *entry;

        while ((entry = readdir(dirObj)) != NULL)
        {
            if (entry->d_name[0] == '.') {
                continue;
            }
            if (entry->d_type == DT_DIR) {
                getFilesInFolder(path + "/" + entry->d_name, output);            
            } else {
                output.push_back(path + "/" + entry->d_name);
            }
        }

        closedir(dirObj);
    }

    double getRotationFromPoints(double x1, double y1, double x2, double y2) {
        double width = x2 - x1;
        double height = y2 - y1;
        double h = hypotenuse(width, height);
        return cosineLaw(height, width, h);
    }

    double getScalingFromPoints(double x1, double y1, double x2, double y2, double origWidth) {
        double width = x2 - x1;
        double height = y2 - y1;
        double h = hypotenuse(width, height);
        return h / origWidth;
    }

    double hypotenuse(double a, double b) {
        return sqrt(a * a + b * b);
    }

    double findAngle(double x1, double y1, double x2, double y2, double x3, double y3) {
        double d = abs(y2 - y1);
        double e = abs(x2 - x1);
        double f = abs(x3 - x2);
        double g = abs(y3 - y2);
        double a = hypotenuse(d, e);
        double b = hypotenuse(f, g);
        double h = abs(x3 - x1);
        double i = abs(y3 - y1);
        double c = hypotenuse(h, i);
        return cosineLaw(c, a, b);
    }

    double cosineLaw(double b, double a, double c) {
        double numerator = a * a - b * b + c * c;
        double denominator = 2 * a * c;
        return acos(numerator / denominator);
    }

    void writeToFile(double text, string filename) {
        std::ofstream outfile;
        outfile.open(filename, ios_base::app);
        outfile << text; 
        outfile << "\n";
    }

#endif