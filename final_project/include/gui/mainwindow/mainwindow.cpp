#include "mainwindow.hpp"
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      taskManager_(),
      database_("tasks.db"),
      taskList_(new QListWidget(this)),
      mainToolBar_(new QToolBar("Меню", this)),
      statusBar_(new QStatusBar(this)) 
{
    // Загрузка стилей перед инициализацией UI
    loadStyleSheet();
    
    // Инициализация UI
    setupUI();
    setupMenuBar();

    setupToolBar();
    setupConnections();
    
    // Загрузка данных
    database_.load(taskManager_);
    refreshTaskList();
    
    // Восстановление настроек
    loadSettings();
}

void MainWindow::setupUI() {
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
    addAction_->setIcon(QIcon("resources/icons/add.svg"));
    editAction_->setIcon(QIcon("resources//icons/edit.svg"));
    deleteAction_->setIcon(QIcon("resources//icons/delete.svg"));
    
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
            [this](){ onEditTask(); });
}

void MainWindow::refreshTaskList() {
    taskList_->clear();
    
    for (const auto& task : taskManager_.getTasks()) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable); 
        
        TaskWidget *widget = new TaskWidget(task);
        
        connect(widget, &TaskWidget::editRequested, this, &MainWindow::onEditTask);
        connect(widget, &TaskWidget::statusChanged, this, &MainWindow::onTaskStatusChanged);
        
        taskList_->addItem(item);
        taskList_->setItemWidget(item, widget);
        item->setSizeHint(widget->sizeHint());
        
        // Полностью скрываем текст
        item->setData(Qt::DisplayRole, QVariant());
    }
}

// Реализация слотов
void MainWindow::onAddTask() {
    TaskDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Task newTask = dialog.getTask();
        taskManager_.addTask(newTask);
        refreshTaskList();
        database_.save(taskManager_);
    }
}

void MainWindow::onEditTask() {
    if (auto task = const_cast<Task*>(getSelectedTask())) {
        TaskDialog dialog(*task, this);
        if (dialog.exec() == QDialog::Accepted) {
            *task = dialog.getTask(); 
            refreshTaskList() ;
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
    if (completed) {
        taskManager_.markTaskCompleted(desc);
    } else {
        taskManager_.markTaskPending(desc);
    }
    database_.save(taskManager_);
    refreshTaskList(); 
}

void MainWindow::onFilterTasks(int filterType) {
    std::vector<Task> filtered;
    
    switch(filterType) {
        case 0: filtered = taskManager_.getTasks(); break;
        case 1: filtered = taskManager_.getTasksByPriority(Priority::High); break;
        case 2: filtered = taskManager_.getCompletedTasks(); break;
        case 3: filtered = taskManager_.getPendingTasks(); break;
    }
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
    QFile styleFile("resources/styles/main.qss");
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