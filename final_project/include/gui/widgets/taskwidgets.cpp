#include "taskwidgets.hpp"
#include <QMouseEvent>
#include <QPalette>
#include <QDate>
#include <QDebug>

TaskWidget::TaskWidget(const Task& task, QWidget *parent) 
    : QWidget(parent), task_(task) 
{
    qDebug() << "TaskWidget: Creating widget for task:" << QString::fromStdString(task.getTitle());
    setupUI();
    updateStyle();
    qDebug() << "TaskWidget: Widget created successfully";
}

void TaskWidget::updateTask(const Task& task) {
    qDebug() << "TaskWidget: Updating task from" << QString::fromStdString(task_.getTitle()) 
             << "to" << QString::fromStdString(task.getTitle());
    task_ = task;
    titleLabel_->setText(QString::fromStdString(task.getTitle()));
    updateStyle();
    qDebug() << "TaskWidget: Task updated successfully";
}

const Task& TaskWidget::getTask() const {
    return task_;
}

void TaskWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    qDebug() << "TaskWidget: Double click detected for task:" << QString::fromStdString(task_.getTitle());
    Q_EMIT editRequested(task_.getTitle());
    QWidget::mouseDoubleClickEvent(event);
}

void TaskWidget::setupUI() {
    qDebug() << "TaskWidget: Setting up UI for task:" << QString::fromStdString(task_.getTitle());
    // Основной layout
    mainLayout_ = new QHBoxLayout(this);
    mainLayout_->setContentsMargins(5, 5, 5, 5);
    mainLayout_->setSpacing(10);

    // Виджеты для отображения данных
    titleLabel_ = new QLabel(QString::fromStdString(task_.getTitle()), this); 
    titleLabel_->setWordWrap(true);
    titleLabel_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    titleLabel_->setStyleSheet("font-weight: bold;");

    priorityLabel_ = new QLabel(this);
    priorityLabel_->setFixedWidth(20);
    priorityLabel_->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    datesLabel_ = new QLabel(formatDates(), this);
    datesLabel_->setAlignment(Qt::AlignRight);

    // Кнопки управления
    statusButton_ = new QPushButton(this);
    statusButton_->setFixedSize(24, 24);
    statusButton_->setCheckable(true);
    statusButton_->setChecked(task_.isCompleted());
    statusButton_->setAutoExclusive(false);
    
    editButton_ = new QPushButton("✏", this);
    editButton_->setFixedSize(24, 24);

    // Добавление виджетов в layout
    mainLayout_->addWidget(priorityLabel_);
    mainLayout_->addWidget(titleLabel_, 1);  
    mainLayout_->addWidget(datesLabel_);
    mainLayout_->addWidget(statusButton_);
    mainLayout_->addWidget(editButton_);

    // Соединение сигналов
    connect(statusButton_, &QPushButton::clicked, [this](bool checked) {
        qDebug() << "TaskWidget: Status button clicked for task:" << QString::fromStdString(task_.getTitle())
                 << "Current status:" << task_.isCompleted()
                 << "New status:" << checked
                 << "Button state:" << statusButton_->isChecked();
        
        // Обновляем локальное состояние задачи
        if (checked) {
            task_.markCompleted();
            qDebug() << "TaskWidget: Task marked as completed";
        } else {
            task_.markPending();
            qDebug() << "TaskWidget: Task marked as pending";
        }
        
        // Обновляем внешний вид
        updateStyle();
        
        // Отправляем сигнал с правильным описанием задачи
        Q_EMIT statusChanged(task_.getTitle(), checked);
        qDebug() << "TaskWidget: Status change signal emitted with title:" 
                 << QString::fromStdString(task_.getTitle()) 
                 << "and status:" << checked;
    });

    connect(editButton_, &QPushButton::clicked, [this]() {
        qDebug() << "TaskWidget: Edit button clicked for task:" << QString::fromStdString(task_.getTitle());
        Q_EMIT editRequested(task_.getTitle());  
    });
    qDebug() << "TaskWidget: UI setup completed";
}

void TaskWidget::updateStyle() {
    qDebug() << "TaskWidget: Updating style for task:" << QString::fromStdString(task_.getTitle())
             << "Completed:" << task_.isCompleted();
             
    // Обновление цвета приоритета
    priorityLabel_->setStyleSheet(
        QString("background-color: %1; border-radius: 10px;").arg(priorityToColor(task_.getPriority()))
    );

    // Обновление статуса
    statusButton_->setChecked(task_.isCompleted());
    statusButton_->setText(task_.isCompleted() ? "✓" : "○");
    statusButton_->setStyleSheet(
        QString("QPushButton { font-weight: bold; color: %1; }")
            .arg(task_.isCompleted() ? "green" : "gray")
    );

    // Обновление дат
    datesLabel_->setText(formatDates());

    // Стиль для просроченных задач
    if (QDate::fromString(QString::fromStdString(task_.getDueDate()), "yyyy-MM-dd") < QDate::currentDate()) {
        setStyleSheet("background-color: #FFF0F0;");
    } else {
        setStyleSheet("");
    }
    qDebug() << "TaskWidget: Style updated";
}

QString TaskWidget::priorityToColor(Priority priority) const {
    switch (priority) {
        case Priority::High: return "#FF6B6B";
        case Priority::Medium: return "#FFD166";
        case Priority::Low: return "#06D6A0";
        default: return "#CCCCCC";
    }
}

QString TaskWidget::formatDates() const {
    QDateTime creationTime = QDateTime::fromSecsSinceEpoch(task_.getCreationTime());
    QDateTime completionTime = QDateTime::fromSecsSinceEpoch(task_.getCompletionTime());
 
    QString creationStr = creationTime.toString("dd.MM.yyyy");
    
    QString completionStr = "—";
    if (task_.isCompleted()) {
        completionStr = completionTime.toString("dd.MM.yyyy");
    }

    return QString("Создана: %1\nЗавершена: %2")
        .arg(creationStr)
        .arg(completionStr);
}