/**
 * @file mainwindow.hpp
 * @brief Главное окно приложения - центральный UI-компонент
 */

 #pragma once

 #include <QMainWindow>
 #include <QListWidget>
 #include <QToolBar>
 #include <QStatusBar>
 #include <QAction>
 #include "../taskmanager/taskmanager.hpp"
 #include "widgets/taskwidget.hpp"
 #include "dialogs/taskdialog.hpp"
 
 /**
  * @class MainWindow
  * @brief Основное окно приложения, управляющее интерфейсом
  *
  * Обеспечивает:
  * - Отображение списка задач
  * - Управление задачами (добавление/редактирование/удаление)
  * - Фильтрацию и сортировку
  * - Взаимодействие с TaskManager
  */
 class MainWindow : public QMainWindow {
     Q_OBJECT
 
 public:
     /**
      * @brief Конструктор главного окна
      * @param parent Родительский виджет
      */
     explicit MainWindow(QWidget *parent = nullptr);
 
     /**
      * @brief Загружает настройки окна
      */
     void loadSettings();
 
     /**
      * @brief Сохраняет настройки окна
      */
     void saveSettings();
 
 protected:
     void closeEvent(QCloseEvent *event) override;
 
 private slots:
     /**
      * @brief Слот для добавления новой задачи
      */
     void onAddTask();
 
     /**
      * @brief Слот для редактирования выбранной задачи
      */
     void onEditTask();
 
     /**
      * @brief Слот для удаления выбранной задачи
      */
     void onDeleteTask();
 
     /**
      * @brief Слот для обновления статуса задачи
      * @param taskDescription Описание задачи
      * @param completed Новый статус
      */
     void onTaskStatusChanged(const std::string& taskDescription, bool completed);
 
     /**
      * @brief Слот для фильтрации задач
      * @param filterType Тип фильтра (по приоритету, категории и т.д.)
      */
     void onFilterTasks(int filterType);
 
 private:
     // Основные методы
     void setupUI();
     void setupMenuBar();
     void setupToolBar();
     void setupConnections();
     void refreshTaskList();
 
     // Вспомогательные методы
     void showErrorMessage(const QString& message);
     Task* getSelectedTask() const;

     // Загрузка стилей
     void loadStyleSheet();
 
     // Данные
     TaskManager taskManager_;
     Database database_;
 
     // Основные виджеты
     QListWidget *taskList_;
     QToolBar *mainToolBar_;
     QStatusBar *statusBar_;
 
     // Действия
     QAction *addAction_;
     QAction *editAction_;
     QAction *deleteAction_;
     QAction *filterAction_;
     QAction *settingsAction_;
 
     // Фильтры
     QComboBox *filterCombo_;
 };