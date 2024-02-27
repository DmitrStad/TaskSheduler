#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <thread>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std::chrono;

class Task
{
private:
	std::string title;
	std::string description;
	std::chrono::time_point<std::chrono::system_clock> time;
	std::chrono::time_point<std::chrono::system_clock> completion_time;
	bool complete;

public:
	Task(std::string title, std::string description);
	void MarkComplete();
	bool IsComplete();
	void SetTime();
	std::chrono::time_point<std::chrono::system_clock> GetTime();
	void Display();
	void WriteInFile();
	void ReadFromFile();
};

class TaskSheduler {
private:
	std::vector<Task> tasks;
public:
	void AddTask(Task task);
	void DisplayTasks();
	void MarkTaskComplete(int index);
	void MarkTaskComplete(Task task);
	void RemoveCompletedTasks();
	void WriteInFile();
};

