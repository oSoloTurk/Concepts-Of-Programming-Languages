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
	oyun->house = 0.0;
	oyun->playerSize = 0;

	oyun->players = malloc(sizeof(Kisi));

	oyun->getRound = &getRound;
	oyun->getWinnerNumber = &getWinnerNumber;
	oyun->getWinnerNumbers = &getWinnerNumbers;
	oyun->getHouse = &getHouse;
	oyun->getPlayers = &getPlayers;

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
	Dosya winnerNumbers = oyun->getWinnerNumbers(oyun);
	readNextNumber(oyun);
	for(int index = 0; index < oyun->playerSize;index++) {
		Kisi kisi = players[index];
		float transaction = (*kisi->getTotalMoney(kisi));
		transaction *= (*kisi->getSpendMoneyEachRound(kisi));
		*kisi->getTotalMoney(kisi) -= transaction;
		if(*kisi->getLuckyNumber(kisi) == *oyun->getWinnerNumber(oyun)) {
			*kisi->getTotalMoney(kisi) += (transaction * 10);
			*oyun->getHouse(oyun) -= (transaction * 9);
		} else {
			*oyun->getHouse(oyun) += transaction;
		}
		if(*kisi->getTotalMoney(kisi) < 1000) {
			eliminatePlayer(oyun, kisi);
		}
	}
	*oyun->getRound(oyun) += 1;
}

void* playGame(const Oyun oyun, const Arayuz arayuz) {
	while(1){
		oyun->nextRound(oyun);
		if(oyun->playerSize <= 1) {
			break;
		}
		oyun->printStatus(oyun, arayuz);
	    sleep(1 / 3);
	}
}

void* printStatus(const Oyun oyun, const Arayuz arayuz){
	Kisi* kisiler = oyun->getPlayers(oyun);
	Kisi topRich = kisiler[0];
	for(int index = 0; index < oyun->playerSize;index++) {
		Kisi kisi = kisiler[index];
		if (*(topRich->getTotalMoney(topRich)) < *(kisi->getTotalMoney(kisi))){
			topRich = kisi;
		}
	}
	arayuz->cleanScreen(arayuz);
	arayuz->writeStatus(arayuz, 
		*(oyun->getWinnerNumber(oyun)), 
		*(oyun->getRound(oyun)),
		*(oyun->getHouse(oyun)),
		topRich
		);
}

void* joinGame(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	players = realloc(players, (oyun->playerSize + 1) * sizeof(Kisi));
	*(players + sizeof(Kisi) * oyun->playerSize) = kisi;
	oyun->setPlayers(oyun, players);
	oyun->playerSize++;
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

void* setPlayers(const Oyun oyun, Kisi* players){ 
	oyun->players = players;
}

void* eliminatePlayer(const Oyun oyun, const Kisi kisi) {
	Kisi* players = oyun->getPlayers(oyun);
	int length = oyun->playerSize;
	int searchinIngex = 0;

	for(; searchinIngex < length;searchinIngex++){
		Kisi searchingUser = *(players + sizeof(Kisi) * searchinIngex);
		if(searchingUser == kisi) {
			break;
		}	
	}
	struct Kisi tempKisi = **(players + sizeof(Kisi) * (length - 1));
	**(players + sizeof(Kisi) * (length - 1)) = *kisi;
	**(players + sizeof(Kisi) * searchinIngex) = tempKisi;

	players = realloc(players, (length - 1) * sizeof(Kisi));
	oyun->setPlayers(oyun, players);
	oyun->playerSize--;
	return 0;
}

void* readNextNumber(const Oyun oyun){
	fscanf(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)), "%d", oyun->getWinnerNumber(oyun));
}