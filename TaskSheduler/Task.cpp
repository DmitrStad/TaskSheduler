#include "Task.h"

Task::Task(std::string title, std::string description) {
	std::time_t start;
	this->title = title;
	this->description = description;
	this->complete = false;
	this->time = std::chrono::system_clock::now();
}
void Task::MarkComplete() {
	this->complete = true;
	this->time = std::chrono::system_clock::now();
	
 }
bool Task::IsComplete() {
	return this->complete;
}

void Task::SetTime() {
	this->time = std::chrono::system_clock::now();
}

std::chrono::time_point<std::chrono::system_clock> Task::GetTime() {
	return this->time;
}

void Task::Display() {
	
	std::cout << ": " << this->title << "\n";
	std::cout << "Описание: " << this->description << "\n";
	std::cout << "Статус: ";// << (this->complete ? "Завершено" : "Не завершено") << "\n";
	if (this->complete) {
		std::cout << "Завершено\n";
	}
	else {
		std::cout << "Не завершено\n";
		this->time = std::chrono::system_clock::now();
	}
	std::time_t time = std::chrono::system_clock::to_time_t(this->time);
#ifdef _CRT_SECURE_NO_WARNINGS
	#pragma warning(disable : 4996)
#endif
	std::tm* tm = localtime(& time);
#ifdef _CRT_SECURE_NO_WARNINGS
	#pragma warning(default : 4996)
#endif
	std::cout << "Time " << tm->tm_mday<< "."<< tm->tm_mon+1<<"."<<tm->tm_year+1900<<", "<<tm->tm_hour<<" hours, "<<tm->tm_min<<" minutes, "<<tm->tm_sec <<" seconds\n";
	
}

void Task::WriteInFile() {
	std::ofstream out;
	out.open("time.txt");
	if (out.is_open()) {
		std::time_t time = std::chrono::system_clock::to_time_t(this->time);
#ifdef _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif
		std::tm* tm = localtime(&time);
#ifdef _CRT_SECURE_NO_WARNINGS
#pragma warning(default : 4996)
#endif
		out << "Time " << tm->tm_mday << "." << tm->tm_mon + 1 << "." << tm->tm_year + 1900 << ", " << tm->tm_hour << " hours, " << tm->tm_min << " minutes, " << tm->tm_sec << " seconds\n";
	}
	out.close();
}


void TaskSheduler::WriteInFile() {
	for (int i = 0; i < tasks.size(); i++) {
		tasks[i].WriteInFile();
	}
}

void TaskSheduler::AddTask(Task task) {
	tasks.push_back(task);
}

void TaskSheduler::DisplayTasks() {
	std::cout << "------------------------------------------------------\n" << "List to do:\n";
	for (int i = 0; i < tasks.size(); i++) {
		std::cout << "Задача " << i + 1 << "\n";
		tasks[i].Display();
		std::cout << "\n";
	}
	std::cout  << "------------------------------------------------------\n";
}

void TaskSheduler::MarkTaskComplete(int index){
	if (index >= 1 && index <= tasks.size()) {
		tasks[index - 1].MarkComplete();
		std::cout << "Задача " << index << " помечена как завершённая" << "\n";
	}
	else {
		std::cout << "Неверный индекс" << "\n";
	}
}

void TaskSheduler::RemoveCompletedTasks() {
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	for (int i = tasks.size() - 1; i >= 0; i--) {
		if (tasks[i].IsComplete() && currentTime - tasks[i].GetTime() >= std::chrono::hours(12)) {
			tasks.erase(tasks.begin() + i);
		}
	}
}

/*
void TaskSheduler::MarkTaskComplete(Task task){
	int index = 0;
	auto itr = std::find(tasks.begin(), tasks.end(), task);
	if (itr != tasks.end()) {
		index = std::distance(tasks.begin(), itr);
		tasks[index - 1].MarkComplete();
		std::cout << "Task " << index << " marked as completed" << "\n";
	}
	else {
		std::cout << "Invalid Task"<<"\n";
	}
}
*/