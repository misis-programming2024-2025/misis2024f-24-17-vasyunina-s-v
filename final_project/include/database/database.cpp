#include "database.hpp"
#include <QFile>
#include <QDebug>
#include <ctime>

Database::Database(const QString& filename) 
    : filename_(filename), db_(nullptr) {}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
    }
}

bool Database::save(const TaskManager& manager) {
    if (sqlite3_open(filename_.toUtf8().constData(), &db_) != SQLITE_OK) {
        qCritical() << "Ошибка открытия БД:" << sqlite3_errmsg(db_);
        return false;
    }
    
    executeQuery("BEGIN TRANSACTION;");
    executeQuery("DELETE FROM tasks;");
    
    const auto tasks = manager.getTasks();
    for (const auto& task : tasks) {
        QString query = QString(
            "INSERT INTO tasks (title, description, due_date, priority, category, completed, creation_date, completion_date) "
            "VALUES ('%1', '%2', '%3', %4, %5, %6, %7, %8);")
            .arg(QString::fromStdString(task.getTitle()).replace("'", "''"))
            .arg(QString::fromStdString(task.getDescription()).replace("'", "''"))
            .arg(QString::fromStdString(task.getDueDate()).replace("'", "''"))
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
    
    executeQuery("COMMIT;");
    sqlite3_close(db_);
    db_ = nullptr;
    return true;
}

bool Database::load(TaskManager& manager) {
    if (!exists()) {
        return createDatabase();
    }
    
    if (sqlite3_open(filename_.toUtf8().constData(), &db_) != SQLITE_OK) {
        qCritical() << "Ошибка открытия БД:" << sqlite3_errmsg(db_);
        return false;
    }
    
    auto callback = [](void* manager, int argc, char** data, char**) -> int {
        TaskManager* m = static_cast<TaskManager*>(manager);
        
        // Проверяем, что есть все необходимые поля
        if (argc < 8) return 1;
        
        // Создаем временные std::string из char*
        std::string title = data[0] ? data[0] : "";
        std::string description = data[1] ? data[1] : "";
        std::string dueDate = data[2] ? data[2] : "";
        
        Task task(
            title,                // std::string title
            description,          // std::string description
            dueDate,              // std::string dueDate
            static_cast<Priority>(atoi(data[3])), // priority
            static_cast<Category>(atoi(data[4])), // category
            atoi(data[5]) == 1    // completed
        );
        
        if (data[6]) task.setCreationTime(atol(data[6]));
        if (data[7]) task.setCompletionTime(atol(data[7]));
        m->addTask(task);
        return 0;
    };
    
    char* error = nullptr;
    if (sqlite3_exec(db_, 
        "SELECT title, description, due_date, priority, category, completed, creation_date, completion_date FROM tasks;", 
        callback, &manager, &error) != SQLITE_OK) {
        qCritical() << "Ошибка загрузки:" << error;
        sqlite3_free(error);
        return false;
    }
    
    sqlite3_close(db_);
    db_ = nullptr;
    return true;
}

bool Database::createDatabase() {
    if (sqlite3_open(filename_.toUtf8().constData(), &db_) != SQLITE_OK) {
        return false;
    }
    
    QString createTable = 
        "CREATE TABLE tasks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "description TEXT NOT NULL, "
        "due_date TEXT, "
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

bool Database::executeQuery(const QString& query) {
    char* error = nullptr;
    if (sqlite3_exec(db_, query.toUtf8().constData(), nullptr, nullptr, &error) != SQLITE_OK) {
        qCritical() << "Ошибка SQL:" << error << "Запрос:" << query;
        sqlite3_free(error);
        return false;
    }
    return true;
}

bool Database::exists() const {
    return QFile::exists(filename_);
}