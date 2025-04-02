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