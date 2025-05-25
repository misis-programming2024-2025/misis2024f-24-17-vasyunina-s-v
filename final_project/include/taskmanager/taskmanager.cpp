#include "taskmanager.hpp"
#include <algorithm>
#include <unordered_map>
#include <iostream>

struct TaskManager::Impl {
    std::unordered_map<std::string, size_t> descriptionToIndex;
};

TaskManager::TaskManager() : pImpl(std::make_unique<Impl>()) {}
TaskManager::~TaskManager() = default;

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
    pImpl->descriptionToIndex[task.getDescription()] = tasks.size() - 1;
}

void TaskManager::removeTask(const std::string& description) {
    auto it = pImpl->descriptionToIndex.find(description);
    if (it != pImpl->descriptionToIndex.end()) {
        tasks.erase(tasks.begin() + it->second);
        pImpl->descriptionToIndex.erase(it);
        pImpl->descriptionToIndex.clear();
        for (size_t i = 0; i < tasks.size(); ++i) {
            pImpl->descriptionToIndex[tasks[i].getDescription()] = i;
        }
    }
}

void TaskManager::markTaskCompleted(const std::string& title) {
    std::cout << "TaskManager: Marking task as completed: " << title << std::endl;
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [&title](const Task& task) { return task.getTitle() == title; });
    
    if (it != tasks.end()) {
        std::cout << "TaskManager: Task found, marking as completed" << std::endl;
        it->markCompleted();
    } else {
        std::cout << "TaskManager: Task not found!" << std::endl;
    }
}

void TaskManager::updateTaskDescription(const std::string& oldDesc, 
                                      const std::string& newDesc) {
    auto it = findTask(oldDesc);
    if (it != tasks.end()) {
        pImpl->descriptionToIndex.erase(oldDesc);
        it->setDescription(newDesc);
        pImpl->descriptionToIndex[newDesc] = std::distance(tasks.begin(), it);
    }
}

void TaskManager::updateTask(const Task& task) {
    auto it = findTask(task.getDescription());
    if (it != tasks.end()) {
        // Сохраняем старые значения для обновления индекса
        std::string oldDesc = it->getDescription();
        
        // Обновляем все поля задачи
        it->setTitle(task.getTitle());
        it->setDescription(task.getDescription());
        it->updateDueDate(task.getDueDate());
        it->setPriority(task.getPriority());
        it->setCategory(task.getCategory());
        
        // Обновляем статус выполнения
        if (task.isCompleted() && !it->isCompleted()) {
            it->markCompleted();
        } else if (!task.isCompleted() && it->isCompleted()) {
            it->markPending();
        }
        
        // Обновляем индексы
        pImpl->descriptionToIndex.erase(oldDesc);
        pImpl->descriptionToIndex[task.getDescription()] = std::distance(tasks.begin(), it);
    }
}

void TaskManager::updateTaskDueDate(const std::string& description, 
                                   const std::string& newDueDate) {
    auto it = findTask(description);
    if (it != tasks.end()) {
        it->updateDueDate(newDueDate);
    }
}

void TaskManager::updateTaskPriority(const std::string& description, 
                                   Priority newPriority) {
    auto it = findTask(description);
    if (it != tasks.end()) {
        it->setPriority(newPriority);
    }
}

void TaskManager::updateTaskCategory(const std::string& description, 
                                   Category newCategory) {
    auto it = findTask(description);
    if (it != tasks.end()) {
        it->setCategory(newCategory);
    }
}

void TaskManager::addTagToTask(const std::string& description, 
                             const std::string& tag) {
    auto it = findTask(description);
    if (it != tasks.end()) {
        it->addTag(tag);
    }
}

void TaskManager::removeTagFromTask(const std::string& description, 
                                  const std::string& tag) {
    auto it = findTask(description);
    if (it != tasks.end()) {
        it->removeTag(tag);
    }
}

std::vector<Task> TaskManager::getTasks() const {
    return tasks;
}

std::vector<Task> TaskManager::getTasksByPriority(Priority priority) const {
    std::vector<Task> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [priority](const Task& t) { return t.getPriority() == priority; });
    return result;
}

std::vector<Task> TaskManager::getTasksByCategory(Category category) const {
    std::vector<Task> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [category](const Task& t) { return t.getCategory() == category; });
    return result;
}

std::vector<Task> TaskManager::getTasksByTag(const std::string& tag) const {
    std::vector<Task> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [&tag](const Task& t) {
            const auto& tags = t.getTags();
            return std::find(tags.begin(), tags.end(), tag) != tags.end();
        });
    return result;
}

std::vector<Task> TaskManager::getCompletedTasks() const {
    std::vector<Task> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [](const Task& t) { return t.isCompleted(); });
    return result;
}

std::vector<Task> TaskManager::getPendingTasks() const {
    std::vector<Task> result;
    std::copy_if(tasks.begin(), tasks.end(), std::back_inserter(result),
        [](const Task& t) { return !t.isCompleted(); });
    return result;
}

void TaskManager::clearCompletedTasks() {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
        [](const Task& t) { return t.isCompleted(); }), tasks.end());
    
    pImpl->descriptionToIndex.clear();
    for (size_t i = 0; i < tasks.size(); ++i) {
        pImpl->descriptionToIndex[tasks[i].getDescription()] = i;
    }
}

void TaskManager::clearAllTasks() {
    tasks.clear();
    pImpl->descriptionToIndex.clear();
}

std::vector<Task>::iterator TaskManager::findTask(const std::string& description) {
    auto it = pImpl->descriptionToIndex.find(description);
    if (it != pImpl->descriptionToIndex.end() && it->second < tasks.size()) {
        return tasks.begin() + it->second;
    }
    return std::find_if(tasks.begin(), tasks.end(),
        [&description](const Task& t) { return t.getDescription() == description; });
}

void TaskManager::markTaskPending(const std::string& title) {
    std::cout << "TaskManager: Marking task as pending: " << title << std::endl;
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [&title](const Task& task) { return task.getTitle() == title; });
    
    if (it != tasks.end()) {
        std::cout << "TaskManager: Task found, marking as pending" << std::endl;
        it->markPending();
    } else {
        std::cout << "TaskManager: Task not found!" << std::endl;
    }
}