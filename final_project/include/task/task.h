#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <chrono>
#include <ctime>

//определяет уровень приоритета задачи важно/желательно/не важно
enum class Priority {
    Low,
    Medium,
    High
};

//определяет категорию задачи работа/учеба/личное
enum class Category {
    Study,
    Work,
    Personal
};

class Task {
public:
    // Конструкторы
    Task(const std::string& description, const std::string& dueDate = "", Priority priority = Priority::Medium, Category category = Category::Personal, bool completed = false);
    
    // Методы для работы с задачей
    void markCompleted(); //отмечает задачу как выполненную
    void markPending(); //отмечает задачу как невыполненную
    void updateDescription(const std::string& newDescription); //обновляет описание задачи
    void updateDueDate(const std::string& newDueDate); //обновляет дату дедлайна задачи
    void setPriority(Priority newPriority); //устанавливает приоритет задачи
    void setCategory(Category newCategory); //устанавливает категорию задачи
    void addTag(const std::string& tag); //добавляет тег задаче(более детальная категория задачи митап/проект/встреча с друзьями)
    void removeTag(const std::string& tag); //удаляет тег

    // Геттеры
    std::string getDescription() const; //возвращает описание
    std::string getDueDate() const; //возвращает дату дедлайна
    Priority getPriority() const; //возвращает приоритет задачи
    Category getCategory() const; //возвращает категорию задачи
    bool isCompleted() const; //статус выполнена/не выполнена
    std::vector<std::string> getTags() const; //возвращает список тегов задачи

    // Методы для работы с временем
    std::time_t getCreationTime() const; //время создания
    std::time_t getCompletionTime() const; //время завершения

private:
    std::string description;
    std::string dueDate;
    Priority priority;
    Category category;
    bool completed;
    std::time_t creationTime;
    std::time_t completionTime;
    std::vector<std::string> tags;
};

#endif