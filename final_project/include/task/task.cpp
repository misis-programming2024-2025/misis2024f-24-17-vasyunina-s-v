#include <algorithm>
#include <ctime>
#include "task.hpp"


Task::Task(const std::string& description, const std::string& dueDate, 
    Priority priority, Category category, bool completed)
: description(description), dueDate(dueDate), priority(priority),
category(category), completed(completed) {
creationTime = std::time(nullptr);
completionTime = 0;
}

void Task::markCompleted() {
completed = true;
completionTime = std::time(nullptr);
}

void Task::markPending() {
completed = false;
completionTime = 0;
}

void Task::updateDescription(const std::string& newDescription) {
description = newDescription;
}

void Task::updateDueDate(const std::string& newDueDate) {
dueDate = newDueDate;
}

void Task::setPriority(Priority newPriority) {
priority = newPriority;
}

void Task::setCategory(Category newCategory) {
category = newCategory;
}

void Task::addTag(const std::string& tag) {
if (std::find(tags.begin(), tags.end(), tag) == tags.end()) {
 tags.push_back(tag);
}
}

void Task::removeTag(const std::string& tag) {
tags.erase(std::remove(tags.begin(), tags.end(), tag), tags.end());
}

std::string Task::getDescription() const { return description; }
std::string Task::getDueDate() const { return dueDate; }
Priority Task::getPriority() const { return priority; }
Category Task::getCategory() const { return category; }
bool Task::isCompleted() const { return completed; }
std::vector<std::string> Task::getTags() const { return tags; }
std::time_t Task::getCreationTime() const { return creationTime; }
std::time_t Task::getCompletionTime() const { return completionTime; }


