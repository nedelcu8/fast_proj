#pragma once
#include <string>
#include <vector>
struct task
{
	std::string description;
	bool done;



};

void safeTaskToFile(const std::vector<task>& tasks, const std::string& fileName);
std::vector<task> loadTasksFromFile(const std::string& fileName);
