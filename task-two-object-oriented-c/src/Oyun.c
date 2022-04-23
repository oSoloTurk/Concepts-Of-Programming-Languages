//
// Created by hakki on 4/15/2022.
//
#include "../include/Oyun.h"

void* eliminatePlayer(const Oyun, const Kisi);

Oyun new_Oyun() {
	Oyun oyun = (Oyun)malloc(sizeof(Oyun));

	oyun->round = 0;
	oyun->winnerNumber = -1;
	oyun->house = 0.0;

	oyun->getRound = &getRound;
	oyun->getWinnerNumber = &getWinnerNumber;
	oyun->getHouse = &getHouse;
	oyun->getPlayers = &getPlayers;

	oyun->nextRound = &nextRound;
	oyun->playGame = &playGame;
	oyun->printStatus = &printStatus;

	oyun->joinGame = &joinGame;

	oyun->winnerNumbers = new_Dosya("./Sayilar.txt");

	return oyun;
}

void* nextRound(const Oyun oyun) {
	Kisi* players = oyun->getPlayers(oyun);
	for(int index = 0; index < (sizeof(players) / sizeof(Kisi));index++) {
		Kisi kisi = players[index];
		float transaction = *kisi->getTotalMoney(kisi) * *kisi->getSpendMoneyEachRound(kisi);
		if(*kisi->getLuckyNumber(kisi) == *oyun->getWinnerNumber(oyun)) {
			*kisi->getTotalMoney(kisi) += (transaction * 10);
			*oyun->getHouse(oyun) -= (transaction * 10);
		} else {
			*kisi->getTotalMoney(kisi) -= transaction;
		}
		if(*kisi->getTotalMoney(kisi) < 1000) {
			eliminatePlayer(oyun, kisi);
			printf("Oyuncu %s Elendi.\n", kisi->getName(kisi));
		}
	}
	*oyun->getRound(oyun) += 1;
}

void* playGame(const Oyun oyun, const Arayuz arayuz) {
	while(1){
		oyun->nextRound(oyun);
		if(oyun->getPlayers(oyun) == NULL) {
			break;
		}
		oyun->printStatus(oyun, arayuz);
	}
}

void* printStatus(const Oyun oyun, const Arayuz arayuz){
	Kisi* kisiler = oyun->getPlayers(oyun);
	Kisi topRich = kisiler[0];
	for(int index = 0; index < (sizeof(kisiler) / sizeof(Kisi));index++) {
		if (*topRich->getTotalMoney(topRich) < *kisiler[index]->getTotalMoney(kisiler[index])){
			topRich = kisiler[index];
		}
	}
	arayuz->cleanScreen(arayuz);
	arayuz->writeStatus(arayuz, 
		*oyun->getWinnerNumber(oyun), 
		*oyun->getRound(oyun),
		*oyun->getHouse(oyun),
		topRich
		);
}

void* joinGame(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	int index = (sizeof(players) / sizeof(Kisi));
	players = realloc(players, (index + 1) * sizeof(Kisi));
	players[index] = kisi;
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

void* eliminatePlayer(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	int length = (sizeof(players) / sizeof(Kisi));
	int searchinIngex = 0;
	for(; searchinIngex < length;searchinIngex++){
		if(players[searchinIngex] == kisi) {
			break;
		}
	}
	Kisi temp = players[searchinIngex];
	players[searchinIngex] = players[length - 1];
	players = realloc(players, (length - 1) * sizeof(Kisi));
	free(temp);
	return 0;
}

void* readNextNumber(const Oyun oyun){
	fscanf(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)), "%d", oyun->getWinnerNumber(oyun));
}