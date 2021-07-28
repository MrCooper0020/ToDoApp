#include <string>
#include <list>
#include "Todo.h"

void changeStatus(bool tgStatus, int tgPosition, std::list<TodoItem*>* list) {
	int index = 0;
	for (TodoItem* item : *list) {
		if (index == tgPosition) {
			(*item).isFinished = tgStatus;
		}

		index = index++;
	}
};

bool createItem(std::string title, std::string description, std::list<TodoItem*>* list) {
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

bool editItem(int position, std::string newTitle, std::string newDescription, std::list<TodoItem*>* list) {
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