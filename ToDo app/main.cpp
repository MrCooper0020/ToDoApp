#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>

using namespace std;

struct TodoItem
{
	string title;
	string description;
	bool isFinished = false;
};

void renderUi(int screen, int listPosition, list<TodoItem>* list ) {
	int index = 0;
	TodoItem newItem;

	system("cls");

	switch (screen) {
	case 3:
		//todo Create a screen to create a item
		//! Warning, is needed pointer to edit the todo list
		printf("New Item\nname:");
		cin >> newItem.title;
		printf("description:");
		cin >> newItem.description;
		(*list).push_back(newItem);
		printf("\n\nSaved, press space to continue!");
		break;
	case 2:
		printf("ToDo list:\n");
		for (TodoItem item : *list){
			printf("    %s - %s %s", item.title.c_str(), (item.isFinished ? "done" : "pending"), (listPosition == index ? "<-\n" : "\n"));
			index = index++;
		}
		printf("\n\nCommands: D - change status to done, P - change status to pending, N - new item");
		break;
	default:
		printf("Welcome to ToDo app!\n\nPress space key to continue!\n\nMade by Matheus H. Potrich");
		break;
	}
}

int main() {
	int actualScreen = 0;
	int screenPostion = 1;
	int listPosition = 0;
	list<TodoItem> toDos;

	TodoItem newItem;
	newItem.title = "Teste 1";
	newItem.description = "This is a test!";
	newItem.isFinished = false;

	TodoItem newItemT;
	newItemT.title = "Teste 2";
	newItemT.description = "This is a test!";
	newItemT.isFinished = false;

	toDos.push_back(newItem);
	toDos.push_back(newItemT);

	while (true) {
		//! verify if the screen is rended, if not will render the screen
		if (actualScreen != screenPostion){
			renderUi(screenPostion, listPosition, &toDos);

			//x On press debug
			//printf("\n\nList position: %i\n\n", listPosition);

			actualScreen = screenPostion;
		}

		if (screenPostion == 1){
			if (GetKeyState(0x20) & 0x8000){
				screenPostion = 2;
			}
		}
		else if (screenPostion == 2) {
			if (GetKeyState(0x1B) & 0x8000) {
				screenPostion = 1;
			}

			if (GetKeyState(0x26) & 0x8000) {
				if ((listPosition + 1) < toDos.size()) {
					listPosition = listPosition + 1;
					actualScreen = 0;
				}
			}

			if (GetKeyState(0x28) & 0x8000) {
				if ((listPosition - 1) >= 0) {
					listPosition = listPosition - 1;
					actualScreen = 0;
				}
			}

			if (GetKeyState(0x44) & 0x8000) {
				//! is needed to recreate the todo list with pointers to make possible to make changes in each item!
				int index = 0;
				for (TodoItem item : toDos){
					if (index == listPosition) {
						item.isFinished = true;
					}

					index = index++;
				}
				actualScreen = 0;
			}

			if (GetKeyState(0x4E) & 0x8000) {
				screenPostion = 3;
			}
		}
		else if (screenPostion == 3) {
			if (GetKeyState(0x20) & 0x8000) {
				screenPostion = 2;
			}
		}

		Sleep(250);
	}

	return 0;
}