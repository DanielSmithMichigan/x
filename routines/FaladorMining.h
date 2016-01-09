#ifndef faladormining_h
#define faladormining_h
	#include "../Inventory.h"
	#include "../Map.h"
	#include "../FaladorLadder.h"
	#include "../FaladorBank.h"
	#include "../MiningGuildLadder.h"
	#include "../Minesite.h"

	using namespace std;

	class FaladorMining {
		private:
		    unique_ptr<Inventory> inventory;
		    unique_ptr<FaladorLadder> faladorLadder;
		    unique_ptr<FaladorBank> bank;
		    unique_ptr<MiningGuildLadder> miningGuildLadder;
		    unique_ptr<Map> interfaceMap;
		    unique_ptr<Minesite> minesite;
		protected:
		public:
			FaladorMining();
			virtual ~FaladorMining();
			void run();
	};
#endif