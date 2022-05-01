//
// Created by hakki on 4/15/2022.
//
#include "../include/Oyun.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
void* eliminatePlayer(const Oyun, const Kisi);
void* readNextNumber(const Oyun oyun);

Oyun new_Oyun() {
	Oyun oyun = (Oyun)malloc(sizeof(struct Oyun));

	oyun->round = 0;
	oyun->winnerNumber = -1;
	oyun->house = 0;
	oyun->playerSize = 0;

	oyun->players = (Kisi*)calloc(1, sizeof(Kisi));
	oyun->getRound = &getRound;
	oyun->incrRound = &incrRound;
	oyun->getWinnerNumber = &getWinnerNumber;
	oyun->getWinnerNumbers = &getWinnerNumbers;
	oyun->getHouse = &getHouse;
	oyun->setHouse = &setHouse;
	oyun->getPlayers = &getPlayers;
	oyun->getPlayerSize = &getPlayerSize;
	oyun->setPlayers = &setPlayers;

	oyun->nextRound = &nextRound;
	oyun->playGame = &playGame;
	oyun->printStatus = &printStatus;

	oyun->joinGame = &joinGame;

	oyun->winnerNumbers = new_Dosya("./Sayilar.txt");

	return oyun;
}



int* getRound(const Oyun oyun) {
	return &oyun->round;
}

void* incrRound(const Oyun oyun) {
	oyun->round += 1;
}

int* getWinnerNumber(const Oyun oyun) {
	return &oyun->winnerNumber;
}

long double* getHouse(const Oyun oyun){
	return &oyun->house;
}

void* setHouse(const Oyun oyun, const long double value){
	oyun->house = value;
}

Dosya getWinnerNumbers(const Oyun oyun){
	return oyun->winnerNumbers;
}

Kisi* getPlayers(const Oyun oyun){
	return oyun->players;
}

int* getPlayerSize(const Oyun oyun){
	return &oyun->playerSize;
}

void* setPlayers(const Oyun oyun, Kisi* players){
	oyun->players = players;
}

//48528976.54
void* nextRound(const Oyun oyun) {
	printf("::%d\n", *oyun->getRound(oyun));
	Kisi* players = oyun->getPlayers(oyun);
	readNextNumber(oyun);
	oyun->incrRound(oyun);
	Kisi* temporaryElimitaneList = calloc(*(oyun->getPlayerSize(oyun)), sizeof(Kisi));
	int eliminateIndex = 0;
	double transaction = 0;
	for(int index = 0; index < *(oyun->getPlayerSize(oyun));index++) {
		Kisi kisi = players[index];

		transaction = (*(kisi->getTotalMoney(kisi))) * (*(kisi->getSpendMoneyEachRound(kisi)));

		*(kisi->getTotalMoney(kisi)) -= transaction;
		*(oyun->getHouse(oyun)) += transaction;

		if(*(kisi->getLuckyNumber(kisi)) == *(oyun->getWinnerNumber(oyun))) {
			*(kisi->getTotalMoney(kisi)) += (transaction * 10.0);
			*(oyun->getHouse(oyun)) -= (transaction * 10.0);
		}

		if(*(kisi->getTotalMoney(kisi)) <= 1000) {
			temporaryElimitaneList[eliminateIndex++] = kisi;
		}
	}
	for(int index = 0;index < eliminateIndex;index++) {
		eliminatePlayer(oyun, temporaryElimitaneList[index]);
	}
	free(temporaryElimitaneList);
}

void* playGame(const Oyun oyun, const Arayuz arayuz) {
	while(1){
		oyun->nextRound(oyun);
		oyun->printStatus(oyun, arayuz);
		if(*(oyun->getPlayerSize(oyun)) < 1) {
			break;
		}
	    //Sleep(1000/5);
	}
}


void* printStatus(const Oyun oyun, const Arayuz arayuz){
	Kisi* players = oyun->getPlayers(oyun);

	if(*oyun->getPlayerSize(oyun) > 1) {
		Kisi topRich = players[0];
		for(int index = 1; index < *(oyun->getPlayerSize(oyun));index++) {
			if (*(topRich->getTotalMoney(topRich)) < *(players[index]->getTotalMoney(players[index]))){
				topRich = players[index];
			}
		}
		arayuz->writeStatus(arayuz, 
			*(oyun->getWinnerNumber(oyun)), 
			*(oyun->getRound(oyun)),
			*(oyun->getHouse(oyun)),
			topRich
			);
	}
	arayuz->cleanScreen(arayuz);
	arayuz->writeFinish(arayuz, 
		*(oyun->getRound(oyun)),
		*(oyun->getHouse(oyun))
		);
}

void* joinGame(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	players = (Kisi*)realloc(players, (*(oyun->getPlayerSize(oyun)) + 2) * sizeof(Kisi));
	players[*(oyun->getPlayerSize(oyun))] = kisi;
	oyun->setPlayers(oyun, players);
	*(oyun->getPlayerSize(oyun)) += 1;
	return 0;
}

void* eliminatePlayer(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	int length = *(oyun->getPlayerSize(oyun));
	int searchinIngex = 0;

	for(; searchinIngex < length;searchinIngex++){
		Kisi searchingUser = players[searchinIngex];
		if(searchingUser == kisi) {
			break;
		}
	}
	Kisi tempKisi = players[length - 1];
	players[length - 1] = kisi;
	players[searchinIngex] = tempKisi;

	delete_Kisi(kisi);
	players = (Kisi*)realloc(players, (length - 1) * sizeof(Kisi));
	oyun->setPlayers(oyun, players);
	*(oyun->getPlayerSize(oyun)) -= 1;
}

void* readNextNumber(const Oyun oyun){
	if(feof(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)))) {
		oyun->getWinnerNumbers(oyun)->reload(oyun->getWinnerNumbers(oyun));
	}
	fscanf(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)), "%d", oyun->getWinnerNumber(oyun));
}