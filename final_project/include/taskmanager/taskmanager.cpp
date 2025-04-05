/**
 * @file taskmanager.cpp
 * @brief Реализация класса TaskManager
 */

 #include "taskmanager.hpp"
 #include <algorithm>
 #include <unordered_map>
 
 /**
  * @brief Внутренняя структура реализации (Pimpl idiom)
  * 
  * Содержит:
  * - Вектор задач
  * - Хеш-таблицу для быстрого поиска по описанию
  */
 struct TaskManager::Impl {
     std::vector<Task> tasks;                      ///< Основное хранилище задач
     std::unordered_map<std::string, size_t> description_index; ///< Индекс для быстрого поиска
 };
 
 /**
  * @brief Конструктор TaskManager
  * 
  */
 TaskManager::TaskManager() : pImpl(std::make_unique<Impl>()) {}
 
 /**
  * @brief Деструктор TaskManager
  * 
  * Автоматически удаляет внутренние данные благодаря unique_ptr.
  */
 TaskManager::~TaskManager() = default;
 
 /**
  * @brief Внутренний метод поиска задачи по описанию
  * @param description Описание искомой задачи
  * @return Итератор на найденную задачу или tasks.end() если не найдена
  * 
  * Использует хеш-таблицу для поиска за O(1).
  * Проверяет валидность индекса перед возвратом.
  */
 std::vector<Task>::iterator TaskManager::findTask(const std::string& description) {
     auto it = pImpl->description_index.find(description);
     if (it != pImpl->description_index.end() && it->second < pImpl->tasks.size()) {
         return pImpl->tasks.begin() + it->second;
     }
     return pImpl->tasks.end();
 }
 
 /**
  * @brief Добавляет новую задачу
  * @param task Задача для добавления
  * 
  * Не добавляет задачи с дублирующимися описаниями.
  * Обновляет индекс поиска.
  */
 void TaskManager::addTask(const Task& task) {
     const auto& desc = task.getDescription();
     if (pImpl->description_index.find(desc) == pImpl->description_index.end()) {
         pImpl->description_index[desc] = pImpl->tasks.size();
         pImpl->tasks.push_back(task);
     }
 }
 
 /**
  * @brief Удаляет задачу по описанию
  * @param description Описание удаляемой задачи
  * 
  * Если задача найдена:
  * - Удаляет из вектора
  * - Обновляет индексы оставшихся задач
  */
 void TaskManager::removeTask(const std::string& description) {
     auto it = findTask(description);
     if (it != pImpl->tasks.end()) {
         pImpl->description_index.erase(description);
         for (auto& [desc, idx] : pImpl->description_index) {
             if (idx > std::distance(pImpl->tasks.begin(), it)) {
                 --idx;
             }
         }
         pImpl->tasks.erase(it);
     }
 }
 
 /**
  * @brief Отмечает задачу как выполненную
  * @param description Описание задачи
  */
 void TaskManager::markTaskCompleted(const std::string& description) {
     if (auto it = findTask(description); it != pImpl->tasks.end()) {
         it->markCompleted();
     }
 }
 
 /**
  * @brief Обновляет описание задачи
  * @param oldDesc Текущее описание
  * @param newDesc Новое описание
  * 
  * Проверяет что:
  * 1. Задача с oldDesc существует
  * 2. Задачи с newDesc не существует
  */
 void TaskManager::updateTaskDescription(const std::string& oldDesc, const std::string& newDesc) {
     if (auto it = findTask(oldDesc); it != pImpl->tasks.end() && 
         pImpl->description_index.find(newDesc) == pImpl->description_index.end()) {
         pImpl->description_index.erase(oldDesc);
         it->updateDescription(newDesc);
         pImpl->description_index[newDesc] = std::distance(pImpl->tasks.begin(), it);
     }
 }
 
 /**
  * @brief Возвращает копию вектора всех задач
  * @return std::vector<Task> Копия текущего списка задач
  */
 std::vector<Task> TaskManager::getTasks() const {
     return pImpl->tasks;
 }
 
 /**
  * @brief Фильтрует задачи по приоритету
  * @param priority Приоритет для фильтрации
  * @return Вектор задач с указанным приоритетом
  */
 std::vector<Task> TaskManager::getTasksByPriority(Priority priority) const {
     std::vector<Task> result;
     std::copy_if(pImpl->tasks.begin(), pImpl->tasks.end(), std::back_inserter(result),
         [priority](const Task& t) { return t.getPriority() == priority; });
     return result;
 }
 
 /**
  * @brief Удаляет все выполненные задачи
  * 
  * Перестраивает индекс поиска после удаления.
  */
 void TaskManager::clearCompletedTasks() {
     auto new_end = std::remove_if(pImpl->tasks.begin(), pImpl->tasks.end(),
         [](const Task& t) { return t.isCompleted(); });
     
     pImpl->description_index.clear();
     for (size_t i = 0; i < std::distance(pImpl->tasks.begin(), new_end); ++i) {
         pImpl->description_index[pImpl->tasks[i].getDescription()] = i;
     }
     
     pImpl->tasks.erase(new_end, pImpl->tasks.end());
 }
 
 /**
  * @brief Полностью очищает список задач
  * 
  * Удаляет все задачи и очищает индекс.
  */
 void TaskManager::clearAllTasks() {
     pImpl->tasks.clear();
     pImpl->description_index.clear();
 }