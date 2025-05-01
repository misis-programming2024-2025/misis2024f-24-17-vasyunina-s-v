/**
 * @file database.hpp
 * @brief Класс для работы с базой данных SQLite
 */

 #pragma once

 #include "task/task.hpp"
 #include "taskmanager/taskmanager.hpp"
 #include <QString>
 #include <sqlite3.h>
 #include <vector>
 
 class Database {
 public:
     /**
      * @brief Конструктор класса Database
      * @param filename Путь к файлу базы данных
      * @details Создает объект для работы с указанным файлом БД
      */
     explicit Database(const QString& filename);
     
     /**
      * @brief Деструктор класса
      * @details Автоматически закрывает соединение с БД при уничтожении объекта
      */
     ~Database();
     
     /**
      * @brief Сохраняет задачи в базу данных
      * @param manager Ссылка на менеджер задач
      * @return true если сохранение прошло успешно
      * @details Сохраняет все задачи из менеджера в SQLite базу данных
      */
     bool save(const TaskManager& manager);
     
     /**
      * @brief Загружает задачи из базы данных
      * @param manager Ссылка на менеджер задач для загрузки
      * @return true если загрузка прошла успешно
      * @details Загружает задачи из БД в указанный менеджер задач
      */
     bool load(TaskManager& manager);
     
     /**
      * @brief Проверяет существование файла базы данных
      * @return true если файл БД существует
      */
     bool exists() const;
 
 private:
     QString filename_;       ///< Путь к файлу базы данных
     sqlite3* db_;            ///< Указатель на соединение с БД
     
     /**
      * @brief Создает новую базу данных с нужной структурой
      * @return true если создание прошло успешно
      * @details Создает таблицу tasks с необходимыми полями
      */
     bool createDatabase();
     
     /**
      * @brief Выполняет SQL-запрос
      * @param query Текст SQL-запроса
      * @return true если запрос выполнен успешно
      * @details Используется для выполнения запросов без возврата данных
      */
     bool executeQuery(const QString& query);
 };