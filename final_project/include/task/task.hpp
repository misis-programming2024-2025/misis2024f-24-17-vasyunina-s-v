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
    Study,   ///< Учёба (например, домашние задания).
    Work,    ///< Работа (проекты, встречи).
    Personal ///< Личные дела (спорт, отдых).
};

/**
 * @brief Класс Task представляет задачу в менеджере задач.
 * 
 * Хранит описание, срок выполнения, приоритет, категорию, теги и статус выполнения.
 * Позволяет управлять этими параметрами через методы класса.
 */
class Task {
public:
    /**
     * @brief Конструктор задачи.
     * @param description Описание задачи.
     * @param dueDate Срок выполнения (формат: "YYYY-MM-DD"). По умолчанию — пустая строка.
     * @param priority Приоритет (Low/Medium/High). По умолчанию — Medium.
     * @param category Категория (Study/Work/Personal). По умолчанию — Personal.
     * @param completed Статус выполнения. По умолчанию — false.
     */
    Task(const std::string& description, const std::string& dueDate = "", 
         Priority priority = Priority::Medium, Category category = Category::Personal, 
         bool completed = false);
    
    // === Методы для изменения состояния задачи ===
    /**
     * @brief Отмечает задачу как выполненную.
     * @note Автоматически устанавливает время завершения (текущее время).
     */
    void markCompleted();
    
    /**
     * @brief Отмечает задачу как невыполненную.
     * @note Сбрасывает время завершения в 0.
     */
    void markPending();
    
    /**
     * @brief Обновляет описание задачи.
     * @param newDescription Новое описание.
     */
    void updateDescription(const std::string& newDescription);
    
    /**
     * @brief Обновляет срок выполнения задачи.
     * @param newDueDate Новая дата (формат: "YYYY-MM-DD").
     */
    void updateDueDate(const std::string& newDueDate);
    
    /**
     * @brief Устанавливает приоритет задачи.
     * @param newPriority Новый приоритет (Low/Medium/High).
     */
    void setPriority(Priority newPriority);
    
    /**
     * @brief Устанавливает категорию задачи.
     * @param newCategory Новая категория (Study/Work/Personal).
     */
    void setCategory(Category newCategory);
    
    /**
     * @brief Добавляет тег к задаче.
     * @param tag Тег (например, "Проект", "Встреча").
     */
    void addTag(const std::string& tag);
    
    /**
     * @brief Удаляет тег из задачи.
     * @param tag Тег для удаления.
     */
    void removeTag(const std::string& tag);

    // === Геттеры ===
    /**
     * @brief Возвращает описание задачи.
     * @return std::string Текущее описание.
     */
    std::string getDescription() const;
    
    /**
     * @brief Возвращает срок выполнения задачи.
     * @return std::string Дата в формате "YYYY-MM-DD".
     */
    std::string getDueDate() const;
    
    /**
     * @brief Возвращает приоритет задачи.
     * @return Priority Текущий приоритет.
     */
    Priority getPriority() const;
    
    /**
     * @brief Возвращает категорию задачи.
     * @return Category Текущая категория.
     */
    Category getCategory() const;
    
    /**
     * @brief Проверяет статус выполнения задачи.
     * @return true Если задача выполнена.
     */
    bool isCompleted() const;
    
    /**
     * @brief Возвращает список тегов задачи.
     * @return std::vector<std::string> Копия вектора тегов.
     */
    std::vector<std::string> getTags() const;

    // === Методы для работы с временем ===
    /**
     * @brief Возвращает время создания задачи (в Unix-времени).
     * @return std::time_t Время в секундах с 1970 года.
     */
    std::time_t getCreationTime() const;
    
    /**
     * @brief Возвращает время завершения задачи (если выполнена).
     * @return std::time_t Время в секундах или 0, если задача не завершена.
     */
    std::time_t getCompletionTime() const;

private:
    std::string description;      ///< Текстовое описание задачи.
    std::string dueDate;          ///< Срок выполнения (формат: "YYYY-MM-DD").
    Priority priority;            ///< Приоритет задачи.
    Category category;            ///< Категория задачи.
    bool completed;              ///< Статус выполнения.
    std::time_t creationTime;     ///< Время создания (Unix-время).
    std::time_t completionTime;   ///< Время завершения (0, если не завершена).
    std::vector<std::string> tags; ///< Список тегов (например, "Проект", "Срочно").
};
