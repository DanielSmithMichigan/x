#include "routines/FaladorMining.h"
#include "routines/SkillChompaHunting.h"
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
    strings.push_back("DropUncut");
    strings.push_back("Cancel");
    strings.push_back("Mine");
    strings.push_back("MineRocks");
    strings.push_back("Clim");
    strings.push_back("Climb");
    strings.push_back("Bank");
    strings.push_back("Deposit-All");
    strings.push_back("OepositAll");
    strings.push_back("Oeposit");
    strings.push_back("Enter");
    strings.push_back("Exit");

    // Create a SimString database with two person names.
    simstring::ngram_generator gen(strings.size(), false);
    simstring::writer_base<std::string> dbw(gen, "../simstring/words.db");

    // Output the retrieved strings separated by ", ".
    for (int i = 0;i < (int)strings.size();++i) {
        dbw.insert(strings[i]);
    }
    
    dbw.close();
    unique_ptr<Scene> scene(new Scene());
    unique_ptr<FaladorMining> mining(new FaladorMining());
    unique_ptr<SkillChompaHunting> hunting(new SkillChompaHunting());

    scene->getScreen();
    if (argc == 0) {
        cout << "NO ACTION" << endl;
    } else if (strcmp(argv[1], "MINING") == 0) {
        mining->run();
    } else if (strcmp(argv[1], "HUNTING") == 0) {
        hunting->run();
    } else {
        cout << "NO ACTION" << endl;
    }

    cout << "Finished!!" << endl;
    cv::waitKey(0);
    return 0;
}