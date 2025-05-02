#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <chrono>
#include <ctime>

/**
 * @brief Уровень приоритета задачи.
 */
enum class Priority {
    Low,    ///< Низкий приоритет.
    Medium, ///< Средний приоритет.
    High    ///< Высокий приоритет.
};

/**
 * @brief Категория задачи.
 */
enum class Category {
    Study,   ///< Учёба 
    Work,    ///< Работа 
    Personal ///< Личные дела 
};

/**
 * @brief Класс Task представляет задачу в менеджере задач.
 * 
 * Хранит заголовок, описание, срок выполнения, приоритет, категорию, теги и статус выполнения.
 */
class Task {
public:
    /**
     * @brief Конструктор задачи.
     * @param title Заголовок задачи.
     * @param description Описание задачи.
     * @param dueDate Срок выполнения (формат: "YYYY-MM-DD"). По умолчанию — пустая строка.
     * @param priority Приоритет (Low/Medium/High). По умолчанию — Medium.
     * @param category Категория (Study/Work/Personal). По умолчанию — Personal.
     * @param completed Статус выполнения. По умолчанию — false.
     */
    Task() = default;
    Task(const std::string& title, const std::string& description = "",
         const std::string& dueDate = "", Priority priority = Priority::Medium,
         Category category = Category::Personal, bool completed = false);
    
    // === Методы для изменения задачи ===
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void updateDueDate(const std::string& newDueDate);
    void setPriority(Priority newPriority);
    void setCategory(Category newCategory);
    void markCompleted();
    void markPending();
    void addTag(const std::string& tag);
    void removeTag(const std::string& tag);

    // === Геттеры ===
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getDueDate() const;
    Priority getPriority() const;
    Category getCategory() const;
    bool isCompleted() const;
    std::vector<std::string> getTags() const;
    std::time_t getCreationTime() const;
    std::time_t getCompletionTime() const;

    void setCreationTime(std::time_t time);
    void setCompletionTime(std::time_t time);

private:
    std::string title;           ///< Заголовок задачи.
    std::string description;      ///< Подробное описание.
    std::string dueDate;          ///< Срок выполнения.
    Priority priority;            ///< Приоритет задачи.
    Category category;            ///< Категория задачи.
    bool completed;              ///< Статус выполнения.
    std::time_t creationTime;     ///< Время создания.
    std::time_t completionTime;   ///< Время завершения.
    std::vector<std::string> tags; ///< Список тегов.
};

#endif