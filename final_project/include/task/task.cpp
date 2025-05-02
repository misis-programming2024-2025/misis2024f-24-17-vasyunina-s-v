#include "task.hpp"
#include <ctime>

Task::Task(const std::string& title, const std::string& description,
           const std::string& dueDate, Priority priority,
           Category category, bool completed)
    : title(title), description(description), dueDate(dueDate),
      priority(priority), category(category), completed(completed),
      creationTime(std::time(nullptr)), completionTime(0) {}

void Task::setTitle(const std::string& title) {
    this->title = title;
}

void Task::setDescription(const std::string& description) {
    this->description = description;
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

void Task::markCompleted() {
    completed = true;
    completionTime = std::time(nullptr);
}

void Task::markPending() {
    completed = false;
    completionTime = 0;
}

void Task::addTag(const std::string& tag) {
    tags.push_back(tag);
}

void Task::removeTag(const std::string& tag) {
    for (auto it = tags.begin(); it != tags.end(); ) {
        if (*it == tag) {
            it = tags.erase(it);
        } else {
            ++it;
        }
    }
}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

std::string Task::getDueDate() const {
    return dueDate;
}

Priority Task::getPriority() const {
    return priority;
}

Category Task::getCategory() const {
    return category;
}

bool Task::isCompleted() const {
    return completed;
}

std::vector<std::string> Task::getTags() const {
    return tags;
}

std::time_t Task::getCreationTime() const {
    return creationTime;
}

std::time_t Task::getCompletionTime() const {
    return completionTime;
}

void Task::setCreationTime(std::time_t time) {
    creationTime = time;
}

void Task::setCompletionTime(std::time_t time) {
    completionTime = time;
}