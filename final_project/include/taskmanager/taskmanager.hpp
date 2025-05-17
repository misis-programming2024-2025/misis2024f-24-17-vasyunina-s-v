#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP


#include "task/task.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

/**
 * @brief Класс TaskManager управляет коллекцией задач.
 * 
 * Предоставляет методы для добавления, удаления, обновления и фильтрации задач 
 * по приоритету, категории, тегам и статусу выполнения.
 */
class TaskManager {
public:
    /**
     * @brief Конструктор
     */
    TaskManager();
    ~TaskManager();

    // === Методы для управления задачами ===
    /**
     * @brief Добавляет задачу в менеджер.
     * @param task Объект задачи (копируется).
     */
    void addTask(const Task& task);
    
    /**
     * @brief Удаляет задачу по описанию.
     * @param description Описание задачи для удаления.
     * @note Удаляет первую задачу с совпадающим описанием.
     */
    void removeTask(const std::string& description);
    
    /**
     * @brief Отмечает задачу как выполненную.
     * @param description Описание задачи.
     */
    void markTaskCompleted(const std::string& description);
    void markTaskPending(const std::string& title);
    
    /**
     * @brief Обновляет описание задачи.
     * @param oldDescription Текущее описание.
     * @param newDescription Новое описание.
     */
    void updateTaskDescription(const std::string& oldDescription, const std::string& newDescription);
    
    /**
     * @brief Полностью обновляет задачу
     * @param task Новая версия задачи
     */
    void updateTask(const Task& task);
    
    /**
     * @brief Обновляет срок выполнения задачи.
     * @param description Описание задачи.
     * @param newDueDate Новая дата (формат: "YYYY-MM-DD").
     */
    void updateTaskDueDate(const std::string& description, const std::string& newDueDate);
    
    /**
     * @brief Изменяет приоритет задачи.
     * @param description Описание задачи.
     * @param newPriority Новый приоритет (Low/Medium/High).
     */
    void updateTaskPriority(const std::string& description, Priority newPriority);
    
    /**
     * @brief Изменяет категорию задачи.
     * @param description Описание задачи.
     * @param newCategory Новая категория (Study/Work/Personal).
     */
    void updateTaskCategory(const std::string& description, Category newCategory);
    
    /**
     * @brief Добавляет тег к задаче.
     * @param description Описание задачи.
     * @param tag Тег (например, "Проект").
     */
    void addTagToTask(const std::string& description, const std::string& tag);
    
    /**
     * @brief Удаляет тег у задачи.
     * @param description Описание задачи.
     * @param tag Тег для удаления.
     */
    void removeTagFromTask(const std::string& description, const std::string& tag);

    // === Методы для поиска и фильтрации ===
    /**
     * @brief Возвращает все задачи.
     * @return std::vector<Task> Копия списка задач.
     */
    std::vector<Task> getTasks() const;
    
    /**
     * @brief Фильтрует задачи по приоритету.
     * @param priority Приоритет (Low/Medium/High).
     * @return std::vector<Task> Задачи с указанным приоритетом.
     */
    std::vector<Task> getTasksByPriority(Priority priority) const;
    
    /**
     * @brief Фильтрует задачи по категории.
     * @param category Категория (Study/Work/Personal).
     * @return std::vector<Task> Задачи с указанной категорией.
     */
    std::vector<Task> getTasksByCategory(Category category) const;
    
    /**
     * @brief Фильтрует задачи по тегу.
     * @param tag Искомый тег.
     * @return std::vector<Task> Задачи с указанным тегом.
     */
    std::vector<Task> getTasksByTag(const std::string& tag) const;
    
    /**
     * @brief Возвращает выполненные задачи.
     * @return std::vector<Task> Задачи со статусом "completed".
     */
    std::vector<Task> getCompletedTasks() const;
    
    /**
     * @brief Возвращает невыполненные задачи.
     * @return std::vector<Task> Задачи со статусом "pending".
     */
    std::vector<Task> getPendingTasks() const;

    // === Методы для массовых операций ===
    /**
     * @brief Удаляет все выполненные задачи.
     */
    void clearCompletedTasks();
    
    /**
     * @brief Удаляет все задачи (очищает менеджер).
     */
    void clearAllTasks();

private:
    std::vector<Task> tasks; ///< Вектор для хранения задач.
    struct Impl;///< Вспомогательная структура для быстрого поиска
    std::unique_ptr<Impl> pImpl;
    std::vector<Task>::iterator findTask(const std::string& description);///< Быстрый поиск задач по описанию
};
#endif 