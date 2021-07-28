#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <list>
#include "Todo.h"
#include "UserInterface.h"

using namespace std;

int main() {
	int actualScreen = 0;
	int screenPostion = 1;
	int listPosition = 0;
	list<TodoItem*> toDos;

	TodoItem newItem;
	newItem.title = "Teste 1";
	newItem.description = "This is a test!";
	newItem.isFinished = false;

	TodoItem newItemT;
	newItemT.title = "Teste 2";
	newItemT.description = "This is a test!";
	newItemT.isFinished = false;

	toDos.push_back(&newItem);
	toDos.push_back(&newItemT);

	while (true) {
		//! verify if the screen is rended, if not will render the screen
		if (actualScreen != screenPostion) {
			renderUi(screenPostion, listPosition, &toDos);
			actualScreen = screenPostion;
		}

		if (screenPostion == 1) {
			if (GetKeyState(0x20) & 0x8000) {
				screenPostion = 2;
			}
		}
		else if (screenPostion == 2) {
			if (GetKeyState(0x1B) & 0x8000) {
				screenPostion = 1;
			}

			if (GetKeyState(0x26) & 0x8000) {
				if ((listPosition + 1) < toDos.size()) {
					listPosition = listPosition++;
					actualScreen = 0;
				}
			}

			if (GetKeyState(0x28) & 0x8000) {
				if ((listPosition - 1) >= 0) {
					listPosition = listPosition--;
					actualScreen = 0;
				}
			}

			if (GetKeyState(0x44) & 0x8000) {
				changeStatus(true, listPosition, &toDos);
				actualScreen = 0;
			}

			if (GetKeyState(0x50) & 0x8000) {
				changeStatus(false, listPosition, &toDos);
				actualScreen = 0;
			}

			if (GetKeyState(0x4E) & 0x8000) {
				screenPostion = 3;
			}

			if (GetKeyState(0x45) & 0x8000) {
				screenPostion = 4;
			}
		}
		else if (screenPostion == 3 || screenPostion == 4) {
			if (GetKeyState(0x20) & 0x8000) {
				screenPostion = 2;
			}
		}

		//Sleep(250);
	}

	return 0;
};