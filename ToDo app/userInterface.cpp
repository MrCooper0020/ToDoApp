#include <list>
#include <string>
#include <iostream>
#include "Todo.h"

void renderUi(int screen, int listPosition, std::list<TodoItem*>* list) {
	int index = 0;
	std::string title = "";
	std::string description = "";

	system("cls");

	switch (screen) {
	case 4:
		printf("========Edit Item========\ntitle: ");
		std::getline(std::cin, title);
		printf("description: ");
		std::getline(std::cin, description);

		if (editItem(listPosition, title, description, list)) {
			printf("\nSaved, press space to continue!");
		}
		else {
			printf("\nError: something wrong happened!");
		}
		break;
	case 3:
		printf("========New Item========\ntitle: ");
		std::getline(std::cin, title);
		printf("description: ");
		std::getline(std::cin, description);

		if (createItem(title, description, list)) {
			printf("\nSaved, press space to continue!");
		}
		else {
			printf("\nError: something wrong happened!");
		}
		break;
	case 2:
		printf("========ToDo list:========\n");
		for (TodoItem* item : *list) {
			printf("|%s: %s - %s %s|\n", (*item).title.c_str(), (*item).description.c_str(), ((*item).isFinished ? "done" : "pending"), (listPosition == index ? "<-" : ""));
			index = index++;
		}
		printf("\n\nCommands: D - change status to done, P - change status to pending, N - new item, E - edit item");
		break;
	default:
		printf("Welcome to ToDo app!\n\nPress space key to continue!\n\nMade by Matheus H. Potrich");
		break;
	}
};