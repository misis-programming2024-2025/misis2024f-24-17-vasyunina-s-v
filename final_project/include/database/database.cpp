#include "database.hpp"
#include <QFile>
#include <QDebug>

/**
 * @brief Конструктор класса Database
 * @param filename Путь к файлу базы данных
 */
Database::Database(const QString& filename) 
    : filename_(filename), db_(nullptr) {}

/**
 * @brief Деструктор класса Database
 */
Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
    }
}

/**
 * @brief Сохраняет задачи в базу данных
 */
bool Database::save(const TaskManager& manager) {
    // Открываем соединение с БД
    if (sqlite3_open(filename_.toUtf8().constData(), &db_) != SQLITE_OK) {
        qCritical() << "Ошибка открытия БД:" << sqlite3_errmsg(db_);
        return false;
    }
    
    // Начинаем транзакцию для надежного сохранения
    executeQuery("BEGIN TRANSACTION;");
    executeQuery("DELETE FROM tasks;"); // Очищаем старые данные
    
    // Сохраняем все задачи
    const auto tasks = manager.getTasks();
    for (const auto& task : tasks) {
        QString query = QString(
            "INSERT INTO tasks (description, priority, category, completed, creation_date, completion_date) "
            "VALUES ('%1', %2, %3, %4, %5, %6);")
            .arg(task.getDescription().c_str())
            .arg(static_cast<int>(task.getPriority()))
            .arg(static_cast<int>(task.getCategory()))
            .arg(task.isCompleted() ? 1 : 0)
            .arg(task.getCreationTime())
            .arg(task.getCompletionTime());
        
        if (!executeQuery(query)) {
            executeQuery("ROLLBACK;");
            return false;
        }
    }
    
    // Завершаем транзакцию
    executeQuery("COMMIT;");
    sqlite3_close(db_);
    db_ = nullptr;
    return true;
}

/**
 * @brief Загружает задачи из базы данных
 */
bool Database::load(TaskManager& manager) {
    if (!exists()) {
        return createDatabase();
    }
    
    if (sqlite3_open(filename_.toUtf8().constData(), &db_) != SQLITE_OK) {
        qCritical() << "Ошибка открытия БД:" << sqlite3_errmsg(db_);
        return false;
    }
    
    // Callback-функция для обработки результатов запроса
    auto callback = [](void* manager, int, char** data, char**) -> int {
        TaskManager* m = static_cast<TaskManager*>(manager);
        
        Task task(
            data[0], // description
            "", // date (можно добавить парсинг)
            static_cast<Priority>(atoi(data[1])),
            static_cast<Category>(atoi(data[2])),
            atoi(data[3]) == 1 // completed
        );
        
        m->addTask(task);
        return 0;
    };
    
    char* error = nullptr;
    if (sqlite3_exec(db_, "SELECT * FROM tasks;", callback, &manager, &error) != SQLITE_OK) {
        qCritical() << "Ошибка загрузки:" << error;
        sqlite3_free(error);
        return false;
    }
    
    sqlite3_close(db_);
    db_ = nullptr;
    return true;
}

/**
 * @brief Создает новую базу данных
 */
bool Database::createDatabase() {
    if (sqlite3_open(filename_.toUtf8().constData(), &db_) != SQLITE_OK) {
        return false;
    }
    
    QString createTable = 
        "CREATE TABLE tasks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "description TEXT NOT NULL, "
        "priority INTEGER NOT NULL, "
        "category INTEGER NOT NULL, "
        "completed INTEGER DEFAULT 0, "
        "creation_date INTEGER, "
        "completion_date INTEGER);";
    
    if (!executeQuery(createTable)) {
        return false;
    }
    
    sqlite3_close(db_);
    db_ = nullptr;
    return true;
}

/**
 * @brief Выполняет SQL-запрос
 */
bool Database::executeQuery(const QString& query) {
    char* error = nullptr;
    if (sqlite3_exec(db_, query.toUtf8().constData(), nullptr, nullptr, &error) != SQLITE_OK) {
        qCritical() << "Ошибка SQL:" << error << "Запрос:" << query;
        sqlite3_free(error);
        return false;
    }
    return true;
}

/**
 * @brief Проверяет существование файла БД
 */
bool Database::exists() const {
    return QFile::exists(filename_);
}