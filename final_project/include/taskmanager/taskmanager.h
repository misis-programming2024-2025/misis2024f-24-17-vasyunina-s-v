#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include "task/task.h"
#include <vector>
#include <string>
#include <algorithm>


//работает со всем списком задач
class TaskManager {
public:
    TaskManager() = default;

    // Методы для управления задачами
    void addTask(const Task& task);
    void removeTask(const std::string& description);
    void markTaskCompleted(const std::string& description);
    void updateTaskDescription(const std::string& oldDescription, const std::string& newDescription);
    void updateTaskDueDate(const std::string& description, const std::string& newDueDate);
    void updateTaskPriority(const std::string& description, Priority newPriority);
    void updateTaskCategory(const std::string& description, Category newCategory);
    void addTagToTask(const std::string& description, const std::string& tag);
    void removeTagFromTask(const std::string& description, const std::string& tag);

    // Методы для поиска и фильтрации задач
    std::vector<Task> getTasks() const;
    std::vector<Task> getTasksByPriority(Priority priority) const;
    std::vector<Task> getTasksByCategory(Category category) const;
    std::vector<Task> getTasksByTag(const std::string& tag) const;
    std::vector<Task> getCompletedTasks() const;
    std::vector<Task> getPendingTasks() const;

    // Методы для работы со всеми задачами
    void clearCompletedTasks();
    void clearAllTasks();

private:
    std::vector<Task> tasks;
};

#endif