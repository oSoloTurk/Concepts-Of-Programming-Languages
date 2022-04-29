//
// Created by hakki on 4/15/2022.
//
#include "../include/Oyun.h"
#include "../include/Queue.h"

void* eliminatePlayer(const Oyun, const Kisi);
void* readNextNumber(const Oyun oyun);

Oyun new_Oyun() {
	Oyun oyun = (Oyun)malloc(sizeof(struct Oyun));

	oyun->round = 0;
	oyun->winnerNumber = -1;
	oyun->house = 0.0;
	oyun->playerSize = 0;

	oyun->players = new_Queue();

	oyun->getRound = &getRound;
	oyun->getWinnerNumber = &getWinnerNumber;
	oyun->getWinnerNumbers = &getWinnerNumbers;
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
	Queue players = oyun->getPlayers(oyun);
	Dosya winnerNumbers = oyun->getWinnerNumbers(oyun);
	readNextNumber(oyun);
	for(int index = 0; index < oyun->playerSize;index++) {
		Kisi kisi = players->get(players, index);
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
	Queue players = oyun->getPlayers(oyun);
	Kisi topRich = players->get(players, 0);

	for(int index = 1; index < oyun->playerSize;index++) {
		Kisi kisi = players->get(players, index);
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
	oyun->getPlayers(oyun)->addItem(oyun->getPlayers(oyun), kisi);
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

Queue getPlayers(const Oyun oyun){
	return oyun->players;
}

void* eliminatePlayer(const Oyun oyun, const Kisi kisi) {
	oyun->getPlayers(oyun)->removeItem(oyun->getPlayers(oyun), kisi);
	oyun->playerSize--;
	return 0;
}

void* readNextNumber(const Oyun oyun){
	fscanf(oyun->getWinnerNumbers(oyun)->getFile(oyun->getWinnerNumbers(oyun)), "%d", oyun->getWinnerNumber(oyun));
}