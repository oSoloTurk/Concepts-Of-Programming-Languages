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

	oyun->nextRound = &nextRound;
	oyun->getWinnerNumber = &getWinnerNumber;
	oyun->joinGame = &joinGame;

	oyun->winnerNumbers = new_Dosya("Sayilar.txt");

	return oyun;
}

void* nextRound(const Oyun oyun) {
	fscanf(oyun->winnerNumbers->getFile(oyun->winnerNumbers), "%d", &oyun->winnerNumber);
	for(int index = 0; index < (sizeof(oyun->players) / sizeof(Kisi));index++) {
		Kisi kisi = oyun->players[index];
		float transaction = kisi->getTotalMoney(kisi) * kisi->getSpendMoneyEachRound(kisi);
		if(kisi->getLuckyNumber(kisi) == *oyun->getWinnerNumber(oyun)) {
			oyun->players[index]->totalMoney += (transaction * 10);
			oyun->house -= (transaction * 10);
		} else {
			kisi->totalMoney -= transaction;
		}
		if(kisi->getTotalMoney(kisi) < 1000) {
			eliminatePlayer(oyun, kisi);
			printf("Oyuncu %s Elendi.\n", kisi->toString(kisi));
		}
	}
	oyun->round += 1;
}

void* joinGame(const Oyun oyun, const Kisi kisi, const float price) {
	int index = (sizeof(oyun->players) / sizeof(Kisi));
	int newLength = index + 1;
	oyun->players = realloc(oyun->players, newLength * sizeof(Kisi));
	oyun->players[index] = kisi;
	return 0;
}

void* eliminatePlayer(const Oyun oyun, const Kisi kisi) {
	int length = (sizeof(oyun->players) / sizeof(Kisi));
	int searchinIngex = 0;
	for(; searchinIngex < length;searchinIngex++){
		if(oyun->players[searchinIngex] == kisi) {
			break;
		}
	}
	Kisi temp = oyun->players[searchinIngex];
	oyun->players[searchinIngex] = oyun->players[length - 1];
	oyun->players = realloc(oyun->players, (length - 1) * sizeof(Kisi));
	free(temp);
	return 0;
}

int* getWinnerNumber(const Oyun oyun) {
	return &oyun->winnerNumber;
}