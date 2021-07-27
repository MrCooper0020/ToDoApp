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

void changeStatus(bool tgStatus, int tgPosition, list<TodoItem*>* list) {
	int index = 0;
	for (TodoItem* item : *list) {
		if (index == tgPosition) {
			(*item).isFinished = tgStatus;
		}

		index = index++;
	}
};

bool createItem(string title, string description, list<TodoItem*>* list) {
	try {
		TodoItem newItem;
		newItem.title = title;
		newItem.description = description;
		(*list).push_back(&newItem);
		return true;
	}
	catch (...) {
		throw;
	}
};

bool editItem(int position, string newTitle, string newDescription, list<TodoItem*>* list) {
	try {
		int index = 0;

		for (TodoItem* item : *list) {
			if (position == index) {
				item->title = newTitle;
				item->description = newDescription;
				break;
			}

			index = index++;
		}

		return true;
	}
	catch (...) {
		throw;
	}
}

void renderUi(int screen, int listPosition, list<TodoItem*>* list) {
	int index = 0;
	string title = "";
	string description = "";

	system("cls");

	switch (screen) {
	case 4:
		printf("Edit Item\ntitle: ");
		cin >> title;
		printf("description: ");
		cin >> description;

		if (editItem(listPosition, title, description, list)) {
			printf("\nSaved, press space to continue!");
		}
		else {
			printf("\nError: something wrong happened!");
		}
		break;
	case 3:
		printf("New Item\ntitle: ");
		cin >> title;
		printf("description: ");
		cin >> description;

		if (createItem(title, description, list)) {
			printf("\nSaved, press space to continue!");
		}
		else {
			printf("\nError: something wrong happened!");
		}
		break;
	case 2:
		printf("ToDo list:\n");
		for (TodoItem* item : *list) {
			printf("    %s - %s %s", (*item).title.c_str(), ((*item).isFinished ? "done" : "pending"), (listPosition == index ? "<-\n" : "\n"));
			index = index++;
		}
		printf("\n\nCommands: D - change status to done, P - change status to pending, N - new item, E - edit item");
		break;
	default:
		printf("Welcome to ToDo app!\n\nPress space key to continue!\n\nMade by Matheus H. Potrich");
		break;
	}
};

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

			//x On press debug
			//printf("\n\nList position: %i\n\n", listPosition);

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

		Sleep(250);
	}

	return 0;
};