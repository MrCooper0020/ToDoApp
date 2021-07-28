#ifndef TODO_H
#define TODO_H
#include <string>
#include <list>

struct TodoItem{
	std::string title;
	std::string description;
	bool isFinished = false;
};

void changeStatus(bool tgStatus, int tgPosition, std::list<TodoItem*>* list);
bool createItem(std::string title, std::string description, std::list<TodoItem*>* list);
bool editItem(int position, std::string newTitle, std::string newDescription, std::list<TodoItem*>* list);
#endif