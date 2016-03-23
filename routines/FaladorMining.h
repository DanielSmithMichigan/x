#ifndef faladormining_h
#define faladormining_h
	#include "../Inventory.h"
	#include "../Map.h"
	#include "../objects/FaladorLadder.h"
	#include "../objects/FaladorBank.h"
	#include "../objects/MiningGuildLadder.h"
	#include "../BankScreen.h"
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
		    unique_ptr<BankScreen> bankScreen;
		protected:
		public:
			FaladorMining();
			virtual ~FaladorMining();
			void run();
	};
#endif