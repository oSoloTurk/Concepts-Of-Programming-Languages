//
// Created by hakki on 4/15/2022.
//
#include "../include/Oyun.h"

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
	oyun->getWinnerNumber = &getWinnerNumber;
	oyun->getWinnerNumbers = &getWinnerNumbers;
	oyun->getHouse = &getHouse;
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

void* nextRound(const Oyun oyun) {
	Kisi* players = oyun->getPlayers(oyun);
	readNextNumber(oyun);
	Kisi* temporaryElimitaneList = calloc(*(oyun->getPlayerSize(oyun)), sizeof(Kisi));
	int eliminateIndex = 0;
	for(int index = 0; index < *(oyun->getPlayerSize(oyun));index++) {
		Kisi kisi = players[index];

		float transaction = (*(kisi->getTotalMoney(kisi))) * (*(kisi->getSpendMoneyEachRound(kisi)));

		*(kisi->getTotalMoney(kisi)) -= transaction;
		*(oyun->getHouse(oyun)) += transaction;

		if(*(kisi->getLuckyNumber(kisi)) == *(oyun->getWinnerNumber(oyun))) {
			*(kisi->getTotalMoney(kisi)) += (transaction * 10.0);
			*(oyun->getHouse(oyun)) -= (transaction * 10.0);
		}

		if(*(kisi->getTotalMoney(kisi)) < 1000) {
			temporaryElimitaneList[eliminateIndex++] = kisi;
		}
	}
	for(int index = 0;index < eliminateIndex;index++) {
		eliminatePlayer(oyun, temporaryElimitaneList[index]);
	}
	*(oyun->getRound(oyun)) += 1;
}

void* playGame(const Oyun oyun, const Arayuz arayuz) {
	while(1){
		oyun->nextRound(oyun);
		oyun->printStatus(oyun, arayuz);
		if(*(oyun->getPlayerSize(oyun)) <= 1) {
			break;
		}
	    sleep(1/2);
	}
}


void* printStatus(const Oyun oyun, const Arayuz arayuz){
	Kisi* players = oyun->getPlayers(oyun);
	Kisi topRich = players[0];

	for(int index = 1; index < *(oyun->getPlayerSize(oyun));index++) {
		if (*(topRich->getTotalMoney(topRich)) < *(players[index]->getTotalMoney(players[index]))){
			topRich = players[index];
		}
	}

	arayuz->cleanScreen(arayuz);
	if(*(oyun->getPlayerSize(oyun)) <= 1) {
		arayuz->writeFinish(arayuz, 
		*(oyun->getRound(oyun)),
		*(oyun->getHouse(oyun))
		);
	} else {
		arayuz->writeStatus(arayuz, 
			*(oyun->getWinnerNumber(oyun)), 
			*(oyun->getRound(oyun)),
			*(oyun->getHouse(oyun)),
			topRich
			);
	}
}
void* joinGame(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	players = (Kisi*)realloc(players, (*(oyun->getPlayerSize(oyun)) + 2) * sizeof(Kisi));
	players[*(oyun->getPlayerSize(oyun))] = kisi;
	oyun->setPlayers(oyun, players);
	*(oyun->getPlayerSize(oyun)) += 1;
	return 0;
}

int* getRound(const Oyun oyun) {
	return &oyun->round;
}

int* getWinnerNumber(const Oyun oyun) {
	return &oyun->winnerNumber;
}

float* getHouse(const Oyun oyun){
	return &oyun->house;
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

	players = (Kisi*)realloc(players, (length - 1) * sizeof(Kisi));
	oyun->setPlayers(oyun, players);
	*(oyun->getPlayerSize(oyun)) -= 1;
	return 0;
}

void* readNextNumber(const Oyun oyun){
	if(feof(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)))) {
		oyun->getWinnerNumbers(oyun)->reload(oyun->getWinnerNumbers(oyun));
	}
	fscanf(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)), "%d", oyun->getWinnerNumber(oyun));
}