#include "taskmanager.hpp"
#include <algorithm>
#include <unordered_map>


struct TaskManager::Impl {
    std::vector<Task> tasks;
    std::unordered_map<std::string, size_t> description_index;
};

TaskManager::TaskManager() : pImpl(std::make_unique<Impl>()) {}
TaskManager::~TaskManager() = default;

std::vector<Task>::iterator TaskManager::findTask(const std::string& description) {
    auto it = pImpl->description_index.find(description);
    if (it != pImpl->description_index.end() && it->second < pImpl->tasks.size()) {
        return pImpl->tasks.begin() + it->second;
    }
    return pImpl->tasks.end();
}

void TaskManager::addTask(const Task& task) {
    const auto& desc = task.getDescription();
    if (pImpl->description_index.find(desc) == pImpl->description_index.end()) {
        pImpl->description_index[desc] = pImpl->tasks.size();
        pImpl->tasks.push_back(task);
    }
}

void TaskManager::removeTask(const std::string& description) {
    auto it = findTask(description);
    if (it != pImpl->tasks.end()) {
        pImpl->description_index.erase(description);
        for (auto& [desc, idx] : pImpl->description_index) {
            if (idx > std::distance(pImpl->tasks.begin(), it)) {
                --idx;
            }
        }
        pImpl->tasks.erase(it);
    }
}

void TaskManager::markTaskCompleted(const std::string& description) {
    if (auto it = findTask(description); it != pImpl->tasks.end()) {
        it->markCompleted();
    }
}

// Методы обновления
void TaskManager::updateTaskDescription(const std::string& oldDesc, const std::string& newDesc) {
    if (auto it = findTask(oldDesc); it != pImpl->tasks.end() && 
        pImpl->description_index.find(newDesc) == pImpl->description_index.end()) {
        pImpl->description_index.erase(oldDesc);
        it->updateDescription(newDesc);
        pImpl->description_index[newDesc] = std::distance(pImpl->tasks.begin(), it);
    }
}

void TaskManager::updateTaskDueDate(const std::string& description, const std::string& newDueDate) {
    if (auto it = findTask(description); it != pImpl->tasks.end()) {
        it->updateDueDate(newDueDate);
    }
}

void TaskManager::updateTaskPriority(const std::string& description, Priority newPriority) {
    if (auto it = findTask(description); it != pImpl->tasks.end()) {
        it->setPriority(newPriority);
    }
}

void TaskManager::updateTaskCategory(const std::string& description, Category newCategory) {
    if (auto it = findTask(description); it != pImpl->tasks.end()) {
        it->setCategory(newCategory);
    }
}

void TaskManager::addTagToTask(const std::string& description, const std::string& tag) {
    if (auto it = findTask(description); it != pImpl->tasks.end()) {
        it->addTag(tag);
    }
}

void TaskManager::removeTagFromTask(const std::string& description, const std::string& tag) {
    if (auto it = findTask(description); it != pImpl->tasks.end()) {
        it->removeTag(tag);
    }
}

// Методы получения
std::vector<Task> TaskManager::getTasks() const {
    return pImpl->tasks;
}

std::vector<Task> TaskManager::getTasksByPriority(Priority priority) const {
    std::vector<Task> result;
    std::copy_if(pImpl->tasks.begin(), pImpl->tasks.end(), std::back_inserter(result),
        [priority](const Task& t) { return t.getPriority() == priority; });
    return result;
}

std::vector<Task> TaskManager::getTasksByCategory(Category category) const {
    std::vector<Task> result;
    std::copy_if(pImpl->tasks.begin(), pImpl->tasks.end(), std::back_inserter(result),
        [category](const Task& t) { return t.getCategory() == category; });
    return result;
}

std::vector<Task> TaskManager::getTasksByTag(const std::string& tag) const {
    std::vector<Task> result;
    std::copy_if(pImpl->tasks.begin(), pImpl->tasks.end(), std::back_inserter(result),
        [&tag](const Task& t) { 
            const auto& tags = t.getTags();
            return std::find(tags.begin(), tags.end(), tag) != tags.end();
        });
    return result;
}

std::vector<Task> TaskManager::getCompletedTasks() const {
    std::vector<Task> result;
    std::copy_if(pImpl->tasks.begin(), pImpl->tasks.end(), std::back_inserter(result),
        [](const Task& t) { return t.isCompleted(); });
    return result;
}

std::vector<Task> TaskManager::getPendingTasks() const {
    std::vector<Task> result;
    std::copy_if(pImpl->tasks.begin(), pImpl->tasks.end(), std::back_inserter(result),
        [](const Task& t) { return !t.isCompleted(); });
    return result;
}

// Очистка
void TaskManager::clearCompletedTasks() {
    auto new_end = std::remove_if(pImpl->tasks.begin(), pImpl->tasks.end(),
        [](const Task& t) { return t.isCompleted(); });
 
    pImpl->description_index.clear();
    for (size_t i = 0; i < std::distance(pImpl->tasks.begin(), new_end); ++i) {
        pImpl->description_index[pImpl->tasks[i].getDescription()] = i;
    }
    
    pImpl->tasks.erase(new_end, pImpl->tasks.end());
}

void TaskManager::clearAllTasks() {
    pImpl->tasks.clear();
    pImpl->description_index.clear();
}