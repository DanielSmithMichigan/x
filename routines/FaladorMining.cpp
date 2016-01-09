#ifndef faladormining_cpp
#define faladormining_cpp
	#include "FaladorMining.h"

	FaladorMining::FaladorMining() {
		inventory.reset(new Inventory());
		faladorLadder.reset(new FaladorLadder());
		bank.reset(new FaladorBank());
		miningGuildLadder.reset(new MiningGuildLadder());
		interfaceMap.reset(new Map());
		minesite.reset(new Minesite());
	}

	FaladorMining::~FaladorMining() {

	}

	void FaladorMining::run() {
	    while (true) {
	    	minesite->initialize();
	        interfaceMap->initialize();
	        inventory->initialize();

	        if (inventory->full) {
	            cout << "INVENTORY IS FULL" << endl;
	            if (interfaceMap->currentPlane == "FALADOR") {
	                while (true) {
	                    if (interfaceMap->goTo("FALADOR_BANK", 10)) {
	                        break;
	                    }
	                }
	                while(true) {
	                    bank->use();
	                    if (bank->open()) {
	                        break;
	                    }
	                }
	                inventory->bankAllItems();

	                while (true) {
	                    bank->close();
	                    if (!bank->open()) {
	                        break;
	                    }
	                }
	            } else {
	                while (true) {
	                    if (interfaceMap->goTo("MINING_GUILD_LADDER")) {
	                        break;
	                    }
	                }
	                while(true) {
	                    if (miningGuildLadder->use()) {
	                        break;
	                    }
	                }
	            }
	        } else {
	            if (interfaceMap->currentPlane == "FALADOR") {
	                while (true) {
	                    if (interfaceMap->goTo("FALADOR_LADDER")) {
	                        break;
	                    }
	                }
	                while(true) {
	                    if (faladorLadder->use()) {
	                        break;
	                    }
	                }
	            } else {
	                while (true) {
	                    if (interfaceMap->goTo("MINING_GUILD_1")) {
	                        break;
	                    }
	                }
	                minesite->mine("MINING_GUILD_1");
	            }

	        }
	    }
	}

#endif