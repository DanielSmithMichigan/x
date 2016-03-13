#ifndef Crafting_h
#define Crafting_h
	#include "../objects/CraftingFurnace.h"
	#include "../objects/mapObjects/CraftingGuildWaterSymbol.h"
	#include "../objects/Sink.h"
	#include "../objects/PottersWheel.h"
	#include "../Rock.h"
	#include "../Inventory.h"
	#include "../Scene.h"

	using namespace std;

	class Crafting {
		private:
		    unique_ptr<Scene> scene;
		    unique_ptr<Inventory> inventory;
		    unique_ptr<Rock> rock;
		    unique_ptr<PottersWheel> pottersWheel;
		    unique_ptr<Sink> sink;
		    unique_ptr<CraftingFurnace> craftingFurnace;
		    unique_ptr<CraftingGuildWaterSymbol> craftingGuildWaterSymbol;
		    cv::Mat clay;
		    cv::Mat softClay;
		    cv::Mat firedUrn;
		    cv::Mat unfiredUrn;
		protected:
		public:
			Crafting();
			virtual ~Crafting();
			void run();
	};
#endif