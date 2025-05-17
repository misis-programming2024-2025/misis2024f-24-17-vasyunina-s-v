#include "mainwindow.hpp"
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>  

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      taskManager_(),
      database_("tasks.db"),
      taskList_(new QListWidget(this)),
      mainToolBar_(new QToolBar("Меню", this)),
      statusBar_(new QStatusBar(this)) 
{
    qDebug() << "=== Инициализация MainWindow ===";
    
    // Логирование базовых виджетов
    qDebug() << "Основные виджеты созданы:";
    qDebug() << " - taskList_:" << taskList_;
    qDebug() << " - mainToolBar_:" << mainToolBar_;
    qDebug() << " - statusBar_:" << statusBar_;

    // Загрузка стилей перед инициализацией UI
    qDebug() << "Загрузка стилей...";
    loadStyleSheet();
    
    // Инициализация UI
    qDebug() << "Настройка UI...";
    setupUI();
    setupMenuBar();

    qDebug() << "Настройка ToolBar...";
    setupToolBar();
    
    qDebug() << "Настройка соединений...";
    setupConnections();
    
    // Загрузка данных
    qDebug() << "Загрузка данных из БД...";
    database_.load(taskManager_);
    
    qDebug() << "Обновление списка задач...";
    refreshTaskList();
    
    // Восстановление настроек
    qDebug() << "Загрузка настроек...";
    loadSettings();

    // Дополнительная проверка виджетов после полной инициализации
    qDebug() << "\n=== Проверка виджетов после инициализации ===";
    qDebug() << "Все QListWidget:" << findChildren<QListWidget*>();
    qDebug() << "Все QToolBar:" << findChildren<QToolBar*>();
    qDebug() << "Все QPushButton:" << findChildren<QPushButton*>();
    qDebug() << "Все QAction:" << findChildren<QAction*>();

    qDebug() << "=== Инициализация завершена ===";
}

void MainWindow::setupUI() {
    qDebug() << "Настройка интерфейса...";

    if (!centralWidget()) {
        qDebug() << "Создание центрального виджета";
        setCentralWidget(new QWidget(this));
    }

    // Основные настройки окна
    setWindowTitle("Менеджер задач");
    setMinimumSize(800, 600);
    
    // Центральный виджет
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Список задач
    taskList_->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(taskList_);
    
    // Фильтры
    filterCombo_ = new QComboBox(this);
    filterCombo_->addItems({"Все задачи", "Приоритетные", "Выполненные", "В процессе"});
    mainLayout->addWidget(filterCombo_);
    
    setCentralWidget(centralWidget);
    setStatusBar(statusBar_);
}

void MainWindow::setupMenuBar() {
    QMenu *fileMenu = menuBar()->addMenu("Файл");
    
    addAction_ = fileMenu->addAction("Добавить задачу");
    editAction_ = fileMenu->addAction("Редактировать");
    deleteAction_ = fileMenu->addAction("Удалить");
    fileMenu->addSeparator();
    
    QAction *exitAction = fileMenu->addAction("Выйти");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
}

void MainWindow::setupToolBar() {
    addAction_->setIcon(QIcon(":/icons/add.svg"));
    editAction_->setIcon(QIcon(":/icons/edit.svg"));
    deleteAction_->setIcon(QIcon(":/icons/delete.svg"));
    
    mainToolBar_->addAction(addAction_);
    mainToolBar_->addAction(editAction_);
    mainToolBar_->addAction(deleteAction_);
    mainToolBar_->addWidget(filterCombo_);
    
    addToolBar(Qt::TopToolBarArea, mainToolBar_);
}

void MainWindow::setupConnections() {
    // Кнопки
    connect(addAction_, &QAction::triggered, this, &MainWindow::onAddTask);
    connect(editAction_, &QAction::triggered, this, &MainWindow::onEditTask);
    connect(deleteAction_, &QAction::triggered, this, &MainWindow::onDeleteTask);
    
    // Фильтрация
    connect(filterCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFilterTasks);
    
    // Двойной клик
    connect(taskList_, &QListWidget::itemDoubleClicked, 
            [this](){ 
                qDebug() << "MainWindow: Double click on list item";
                onEditTask(); 
            });
}

void MainWindow::refreshTaskList() {
    qDebug() << "MainWindow::refreshTaskList() started";
    qDebug() << "Clearing task list...";
    taskList_->clear();
    
    qDebug() << "Getting tasks from manager...";
    auto tasks = taskManager_.getTasks();
    qDebug() << "Number of tasks:" << tasks.size();
    
    for (const auto& task : tasks) {
        qDebug() << "Creating widget for task:" << QString::fromStdString(task.getTitle());
        try {
            QListWidgetItem *item = new QListWidgetItem();
            qDebug() << "Item created";
            
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable); 
            qDebug() << "Flags set";
            
            TaskWidget *widget = new TaskWidget(task);
            qDebug() << "TaskWidget created";
            
            connect(widget, &TaskWidget::editRequested, this, &MainWindow::onEditTask);
            connect(widget, &TaskWidget::statusChanged, this, &MainWindow::onTaskStatusChanged);
            qDebug() << "Signals connected";
            
            taskList_->addItem(item);
            qDebug() << "Item added to list";
            
            taskList_->setItemWidget(item, widget);
            qDebug() << "Widget set for item";
            
            item->setSizeHint(widget->sizeHint());
            qDebug() << "Size hint set";
            
            item->setData(Qt::DisplayRole, QVariant());
            qDebug() << "Display role cleared";
        } catch (const std::exception& e) {
            qDebug() << "Error creating task widget:" << e.what();
            throw;
        }
    }
    qDebug() << "MainWindow::refreshTaskList() completed";
}

// Реализация слотов
void MainWindow::onAddTask() {
    qDebug() << "MainWindow::onAddTask() called";
    TaskDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "MainWindow: Dialog accepted, getting task data...";
        try {
            Task newTask = dialog.getTask();
            qDebug() << "MainWindow: Task created, adding to manager...";
            taskManager_.addTask(newTask);
            qDebug() << "MainWindow: Refreshing task list...";
            refreshTaskList();
            qDebug() << "MainWindow: Saving to database...";
            database_.save(taskManager_);
            qDebug() << "MainWindow: Task added successfully";
        } catch (const std::exception& e) {
            qDebug() << "MainWindow: Error adding task:" << e.what();
            QMessageBox::critical(this, tr("Error"), tr("Failed to add task: %1").arg(e.what()));
        }
    }
}

void MainWindow::onEditTask() {
    qDebug() << "MainWindow::onEditTask() called";
    const Task* selectedTask = getSelectedTask();
    if (!selectedTask) {
        qDebug() << "MainWindow: No task selected, trying to get task from sender";
        // Попробуем получить задачу из отправителя сигнала
        if (auto* widget = qobject_cast<TaskWidget*>(sender())) {
            qDebug() << "MainWindow: Got task from widget:" << QString::fromStdString(widget->getTask().getTitle());
            TaskDialog dialog(widget->getTask(), this);
            if (dialog.exec() == QDialog::Accepted) {
                qDebug() << "MainWindow: Dialog accepted, updating task...";
                try {
                    Task updatedTask = dialog.getTask();
                    qDebug() << "MainWindow: Task updated, refreshing list...";
                    widget->updateTask(updatedTask);
                    taskManager_.updateTask(updatedTask);
                    database_.save(taskManager_);
                    qDebug() << "MainWindow: Task updated successfully";
                } catch (const std::exception& e) {
                    qDebug() << "MainWindow: Error updating task:" << e.what();
                    QMessageBox::critical(this, tr("Error"), tr("Failed to update task: %1").arg(e.what()));
                }
            }
            return;
        }
        qDebug() << "MainWindow: Could not get task from sender";
        return;
    }

    qDebug() << "MainWindow: Selected task found:" << QString::fromStdString(selectedTask->getTitle());
    TaskDialog dialog(*selectedTask, this);
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "MainWindow: Dialog accepted, updating task...";
        try {
            Task updatedTask = dialog.getTask();
            qDebug() << "MainWindow: Task updated, refreshing list...";
            taskManager_.updateTask(updatedTask);
            refreshTaskList();
            database_.save(taskManager_);
            qDebug() << "MainWindow: Task updated successfully";
        } catch (const std::exception& e) {
            qDebug() << "MainWindow: Error updating task:" << e.what();
            QMessageBox::critical(this, tr("Error"), tr("Failed to update task: %1").arg(e.what()));
        }
    }
}

void MainWindow::onDeleteTask() {
    if (auto task = getSelectedTask()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Удалить задачу", 
                                    "Вы уверены?",
                                    QMessageBox::Yes|QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            taskManager_.removeTask(task->getDescription());
            refreshTaskList();
            database_.save(taskManager_);
        }
    }
}

void MainWindow::onTaskStatusChanged(const std::string& desc, bool completed) {
    qDebug() << "MainWindow::onTaskStatusChanged() called for task:" << QString::fromStdString(desc) 
             << "completed:" << completed;
    
    try {
        if (completed) {
            taskManager_.markTaskCompleted(desc);
        } else {
            taskManager_.markTaskPending(desc);
        }
        database_.save(taskManager_);
        
        // Вместо полного обновления списка, применяем текущий фильтр
        qDebug() << "Applying current filter after status change";
        onFilterTasks(filterCombo_->currentIndex());
        
        qDebug() << "Task status updated successfully";
    } catch (const std::exception& e) {
        qDebug() << "Error updating task status:" << e.what();
        QMessageBox::critical(this, tr("Error"), tr("Failed to update task status: %1").arg(e.what()));
    }
}

void MainWindow::onFilterTasks(int filterType) {
    qDebug() << "MainWindow::onFilterTasks() called with filter type:" << filterType;
    std::vector<Task> filtered;
    
    switch(filterType) {
        case 0: // Все задачи
            qDebug() << "Filtering: All tasks";
            filtered = taskManager_.getTasks(); 
            break;
        case 1: // Приоритетные
            qDebug() << "Filtering: High priority tasks";
            filtered = taskManager_.getTasksByPriority(Priority::High); 
            break;
        case 2: // Выполненные
            qDebug() << "Filtering: Completed tasks";
            filtered = taskManager_.getCompletedTasks(); 
            break;
        case 3: // В процессе
            qDebug() << "Filtering: Pending tasks";
            filtered = taskManager_.getPendingTasks(); 
            break;
    }
    
    qDebug() << "Number of filtered tasks:" << filtered.size();
    
    // Очищаем список
    taskList_->clear();
    
    // Добавляем отфильтрованные задачи
    for (const auto& task : filtered) {
        qDebug() << "Adding filtered task:" << QString::fromStdString(task.getTitle());
        try {
            QListWidgetItem *item = new QListWidgetItem();
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
            
            TaskWidget *widget = new TaskWidget(task);
            connect(widget, &TaskWidget::editRequested, this, &MainWindow::onEditTask);
            connect(widget, &TaskWidget::statusChanged, this, &MainWindow::onTaskStatusChanged);
            
            taskList_->addItem(item);
            taskList_->setItemWidget(item, widget);
            item->setSizeHint(widget->sizeHint());
            item->setData(Qt::DisplayRole, QVariant());
        } catch (const std::exception& e) {
            qDebug() << "Error creating task widget for filtered task:" << e.what();
        }
    }
    qDebug() << "Filtering completed";
}

const Task* MainWindow::getSelectedTask() const {
    if (auto item = taskList_->currentItem()) {
        return &static_cast<TaskWidget*>(taskList_->itemWidget(item))->getTask();
    }
    return nullptr; 
}

void MainWindow::loadSettings() {
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::saveSettings() {
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveSettings();
    database_.save(taskManager_);
    event->accept();
}

void MainWindow::loadStyleSheet() {
    QFile styleFile("");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet); // Применяем ко всему приложению
        styleFile.close();
    } else {
        qWarning() << "Не удалось загрузить файл стилей:" << styleFile.errorString();
        // Можно установить стиль по умолчанию
        qApp->setStyleSheet("QWidget { font-size: 12pt; }");
    }
}