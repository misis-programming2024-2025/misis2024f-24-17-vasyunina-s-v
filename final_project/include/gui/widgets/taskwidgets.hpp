/**
 * @file taskwidget.hpp
 * @brief Виджет для отображения и взаимодействия с отдельной задачей
 */

 #pragma once

 #include <QWidget>
 #include <QLabel>
 #include <QPushButton>
 #include <QHBoxLayout>
 #include "../task/task.hpp"
 
 /**
  * @class TaskWidget
  * @brief Виджет, отображающий одну задачу с возможностью взаимодействия
  * 
  * Отображает:
  * - Описание задачи
  * - Приоритет (с цветовой индикацией)
  * - Статус выполнения
  * - Даты создания и завершения
  * 
  * Поддерживает:
  * - Редактирование по двойному клику
  * - Быстрое изменение статуса
  * - Визуальное выделение просроченных задач
  */
 class TaskWidget : public QWidget {
     Q_OBJECT
 
 public:
     /**
      * @brief Конструктор виджета задачи
      * @param task Объект задачи для отображения
      * @param parent Родительский виджет
      */
     explicit TaskWidget(const Task& task, QWidget *parent = nullptr);
 
     /**
      * @brief Обновляет отображаемую задачу
      * @param task Новые данные задачи
      */
     void updateTask(const Task& task);
 
     /**
      * @brief Возвращает текущую отображаемую задачу
      * @return Константная ссылка на задачу
      */
     const Task& getTask() const;
 
 signals:
     /**
      * @brief Сигнал запроса на редактирование
      * @param taskId Идентификатор задачи (может быть заменен на description)
      */
     void editRequested(const std::string& taskDescription);
 
     /**
      * @brief Сигнал изменения статуса задачи
      * @param taskId Идентификатор задачи
      * @param completed Новый статус
      */
     void statusChanged(const std::string& taskDescription, bool completed);
 
 protected:
     void mouseDoubleClickEvent(QMouseEvent *event) override;
 
 private:
     void setupUI();
     void updateStyle();
 
     Task task_;
 
     QHBoxLayout *mainLayout_;
     QLabel *descriptionLabel_;
     QLabel *priorityLabel_;
     QLabel *datesLabel_;
     QPushButton *statusButton_;
     QPushButton *editButton_;
 
     QString priorityToColor(Priority priority) const;
     QString formatDates() const;
 };