#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/task/task.hpp"
#include "../include/taskmanager/taskmanager.hpp"
#include "../include/database/database.hpp"
#include <QString>
#include <QFile>
#include <memory>

// Тесты для класса Task
TEST_SUITE("Task") {
    TEST_CASE("Task creation and basic properties") {
        Task task("Test Task", "Test Description", "2024-03-20", 
                 Priority::High, Category::Work, false);
        
        CHECK(task.getTitle() == "Test Task");
        CHECK(task.getDescription() == "Test Description");
        CHECK(task.getDueDate() == "2024-03-20");
        CHECK(task.getPriority() == Priority::High);
        CHECK(task.getCategory() == Category::Work);
        CHECK_FALSE(task.isCompleted());
    }

    TEST_CASE("Task status changes") {
        Task task("Test Task");
        CHECK_FALSE(task.isCompleted());
        
        task.markCompleted();
        CHECK(task.isCompleted());
        CHECK(task.getCompletionTime() > 0);
        
        task.markPending();
        CHECK_FALSE(task.isCompleted());
        CHECK(task.getCompletionTime() == 0);
    }

    TEST_CASE("Task tags management") {
        Task task("Test Task");
        CHECK(task.getTags().empty());
        
        task.addTag("important");
        task.addTag("work");
        auto tags = task.getTags();
        CHECK(tags.size() == 2);
        CHECK(std::find(tags.begin(), tags.end(), "important") != tags.end());
        CHECK(std::find(tags.begin(), tags.end(), "work") != tags.end());
        
        task.removeTag("important");
        tags = task.getTags();
        CHECK(tags.size() == 1);
        CHECK(std::find(tags.begin(), tags.end(), "work") != tags.end());
    }

    TEST_CASE("Task property updates") {
        Task task("Original Title");
        
        task.setTitle("New Title");
        CHECK(task.getTitle() == "New Title");
        
        task.setDescription("New Description");
        CHECK(task.getDescription() == "New Description");
        
        task.updateDueDate("2024-12-31");
        CHECK(task.getDueDate() == "2024-12-31");
        
        task.setPriority(Priority::Low);
        CHECK(task.getPriority() == Priority::Low);
        
        task.setCategory(Category::Study);
        CHECK(task.getCategory() == Category::Study);
    }
}

// Тесты для класса TaskManager
TEST_SUITE("TaskManager") {
    TEST_CASE("Task addition and retrieval") {
        TaskManager manager;
        Task task1("Task 1", "Description 1");
        Task task2("Task 2", "Description 2");
        
        manager.addTask(task1);
        manager.addTask(task2);
        
        auto tasks = manager.getTasks();
        CHECK(tasks.size() == 2);
        CHECK(tasks[0].getTitle() == "Task 1");
        CHECK(tasks[1].getTitle() == "Task 2");
    }

    TEST_CASE("Task removal") {
        TaskManager manager;
        Task task("Task to remove", "Description");
        manager.addTask(task);
        
        CHECK(manager.getTasks().size() == 1);
        manager.removeTask("Description");
        CHECK(manager.getTasks().empty());
    }

    TEST_CASE("Task filtering by priority") {
        TaskManager manager;
        Task highTask("High Task", "High", "", Priority::High);
        Task mediumTask("Medium Task", "Medium", "", Priority::Medium);
        Task lowTask("Low Task", "Low", "", Priority::Low);
        
        manager.addTask(highTask);
        manager.addTask(mediumTask);
        manager.addTask(lowTask);
        
        auto highTasks = manager.getTasksByPriority(Priority::High);
        CHECK(highTasks.size() == 1);
        CHECK(highTasks[0].getTitle() == "High Task");
        
        auto mediumTasks = manager.getTasksByPriority(Priority::Medium);
        CHECK(mediumTasks.size() == 1);
        CHECK(mediumTasks[0].getTitle() == "Medium Task");
    }

    TEST_CASE("Task filtering by category") {
        TaskManager manager;
        Task workTask("Work Task", "Work", "", Priority::Medium, Category::Work);
        Task studyTask("Study Task", "Study", "", Priority::Medium, Category::Study);
        Task personalTask("Personal Task", "Personal", "", Priority::Medium, Category::Personal);
        
        manager.addTask(workTask);
        manager.addTask(studyTask);
        manager.addTask(personalTask);
        
        auto workTasks = manager.getTasksByCategory(Category::Work);
        CHECK(workTasks.size() == 1);
        CHECK(workTasks[0].getTitle() == "Work Task");
    }

    TEST_CASE("Task status management") {
        TaskManager manager;
        Task task("Test Task", "Description");
        manager.addTask(task);
        
        manager.markTaskCompleted("Test Task");
        auto completedTasks = manager.getCompletedTasks();
        CHECK(completedTasks.size() == 1);
        CHECK(completedTasks[0].getTitle() == "Test Task");
        
        manager.markTaskPending("Test Task");
        auto pendingTasks = manager.getPendingTasks();
        CHECK(pendingTasks.size() == 1);
        CHECK(pendingTasks[0].getTitle() == "Test Task");
    }

    TEST_CASE("Task updates") {
        TaskManager manager;
        Task task("Original", "Description");
        manager.addTask(task);
        
        Task updatedTask("Updated", "Description", "2024-12-31", 
                        Priority::High, Category::Work, true);
        manager.updateTask(updatedTask);
        
        auto tasks = manager.getTasks();
        CHECK(tasks.size() == 1);
        CHECK(tasks[0].getTitle() == "Updated");
        CHECK(tasks[0].getDueDate() == "2024-12-31");
        CHECK(tasks[0].getPriority() == Priority::High);
        CHECK(tasks[0].getCategory() == Category::Work);
        CHECK(tasks[0].isCompleted());
    }

    TEST_CASE("Clear tasks") {
        TaskManager manager;
        Task task1("Task 1", "Description 1");
        Task task2("Task 2", "Description 2");
        manager.addTask(task1);
        manager.addTask(task2);
        
        manager.markTaskCompleted("Task 1");
        manager.clearCompletedTasks();
        CHECK(manager.getTasks().size() == 1);
        CHECK(manager.getTasks()[0].getTitle() == "Task 2");
        
        manager.clearAllTasks();
        CHECK(manager.getTasks().empty());
    }
}

// Тесты для класса Database
TEST_SUITE("Database") {
    TEST_CASE("Database creation and basic operations") {
        // Используем временный файл для тестов
        QString testDbFile = "test_db.sqlite";
        QFile::remove(testDbFile); // Удаляем файл, если он существует
        
        Database db(testDbFile);
        TaskManager manager;
        
        // Создаем тестовые задачи
        Task task1("Task 1", "Description 1", "2024-03-20", 
                  Priority::High, Category::Work);
        Task task2("Task 2", "Description 2", "2024-03-21", 
                  Priority::Medium, Category::Study);
        
        manager.addTask(task1);
        manager.addTask(task2);
        
        // Тестируем сохранение
        CHECK(db.save(manager));
        
        // Создаем новый менеджер и загружаем задачи
        TaskManager loadedManager;
        CHECK(db.load(loadedManager));
        
        // Проверяем загруженные задачи
        auto tasks = loadedManager.getTasks();
        CHECK(tasks.size() == 2);
        CHECK(tasks[0].getTitle() == "Task 1");
        CHECK(tasks[1].getTitle() == "Task 2");
        
        // Очищаем после тестов
        QFile::remove(testDbFile);
    }

    TEST_CASE("Database error handling") {
        // Тест с неверным путем к файлу
        Database db("/invalid/path/database.sqlite");
        TaskManager manager;
        CHECK_FALSE(db.save(manager));
        
        // Тест с несуществующей базой данных
        Database nonExistentDb("non_existent.sqlite");
        TaskManager emptyManager;
        CHECK(nonExistentDb.load(emptyManager)); // Должно создать новую БД
        CHECK(emptyManager.getTasks().empty());
        
        // Очищаем после тестов
        QFile::remove("non_existent.sqlite");
    }

    TEST_CASE("Database task status persistence") {
        QString testDbFile = "test_status_db.sqlite";
        QFile::remove(testDbFile);
        
        Database db(testDbFile);
        TaskManager manager;
        
        // Создаем задачу и отмечаем её как выполненную
        Task task("Status Test", "Description");
        manager.addTask(task);
        manager.markTaskCompleted("Status Test");
        
        // Сохраняем и загружаем
        CHECK(db.save(manager));
        TaskManager loadedManager;
        CHECK(db.load(loadedManager));
        
        // Проверяем статус
        auto tasks = loadedManager.getTasks();
        CHECK(tasks.size() == 1);
        CHECK(tasks[0].isCompleted());
        
        // Очищаем после тестов
        QFile::remove(testDbFile);
    }
}

// Интеграционные тесты
TEST_SUITE("Integration") {
    TEST_CASE("TaskManager and Database integration") {
        QString testDbFile = "integration_test.sqlite";
        QFile::remove(testDbFile);
        
        Database db(testDbFile);
        TaskManager manager;
        
        // Создаем и сохраняем задачи
        Task task1("Integration Task 1", "Description 1", "2024-03-20", 
                  Priority::High, Category::Work);
        Task task2("Integration Task 2", "Description 2", "2024-03-21", 
                  Priority::Medium, Category::Study);
        
        manager.addTask(task1);
        manager.addTask(task2);
        CHECK(db.save(manager));
        
        // Изменяем задачи
        manager.markTaskCompleted("Integration Task 1");
        manager.updateTaskPriority("Description 2", Priority::High);
        CHECK(db.save(manager));
        
        // Загружаем и проверяем изменения
        TaskManager loadedManager;
        CHECK(db.load(loadedManager));
        
        auto tasks = loadedManager.getTasks();
        CHECK(tasks.size() == 2);
        
        // Проверяем первую задачу
        auto it1 = std::find_if(tasks.begin(), tasks.end(),
            [](const Task& t) { return t.getTitle() == "Integration Task 1"; });
        CHECK(it1 != tasks.end());
        CHECK(it1->isCompleted());
        
        // Проверяем вторую задачу
        auto it2 = std::find_if(tasks.begin(), tasks.end(),
            [](const Task& t) { return t.getTitle() == "Integration Task 2"; });
        CHECK(it2 != tasks.end());
        CHECK(it2->getPriority() == Priority::High);
        
        // Очищаем после тестов
        QFile::remove(testDbFile);
    }
}
