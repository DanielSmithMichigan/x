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
        int randNum = rand()%(max-min + 1) + min;
    }

    void nsleep(long miliseconds)
    {
       struct timespec req, rem;

       if(miliseconds > 999)
       {   
            req.tv_sec = (int)(miliseconds / 1000);                            /* Must be Non-Negative */
            req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000; /* Must be in range of 0 to 999999999 */
       }   
       else
       {   
            req.tv_sec = 0;                         /* Must be Non-Negative */
            req.tv_nsec = miliseconds * 1000000;    /* Must be in range of 0 to 999999999 */
       }   

       nanosleep(&req , &rem);
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

#endif