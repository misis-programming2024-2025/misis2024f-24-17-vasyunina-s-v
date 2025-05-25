#include "taskdialog.hpp"
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

TaskDialog::TaskDialog(QWidget* parent) 
    : QDialog(parent),
      titleEdit(new QLineEdit(this)),
      descriptionEdit(new QTextEdit(this)),
      priorityCombo(new QComboBox(this)),
      categoryCombo(new QComboBox(this)),
      dueDateEdit(new QDateEdit(QDate::currentDate(), this)),
      buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)),
      m_isValid(false),
      m_isCompleted(false)
{
    initUI();
    setupConnections();
    validateInput();
}

TaskDialog::TaskDialog(const Task& task, QWidget* parent)
    : TaskDialog(parent)
{
    setTask(task);
}

void TaskDialog::initUI()
{
    setWindowTitle(tr("Редактирование задачи"));
    resize(400, 300);
    
    dueDateEdit->setCalendarPopup(true);
    dueDateEdit->setDisplayFormat("yyyy-MM-dd");
    
    priorityCombo->addItems({tr("Можно отложить"), tr("Опционально"), tr("Важно")});
    categoryCombo->addItems({tr("Работа"), tr("Личное"), tr("Учеба"), tr("Другое")});
    
    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout();
    
    formLayout->addRow(new QLabel(tr("Задача")), titleEdit);
    formLayout->addRow(new QLabel(tr("Описание")), descriptionEdit);
    formLayout->addRow(new QLabel(tr("Приоритет")), priorityCombo);
    formLayout->addRow(new QLabel(tr("Категория")), categoryCombo);
    formLayout->addRow(new QLabel(tr("Дата дедлайна")), dueDateEdit);
    
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);
    
    setLayout(mainLayout);
}

void TaskDialog::setupConnections()
{
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TaskDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TaskDialog::reject);
    connect(titleEdit, &QLineEdit::textChanged, this, &TaskDialog::validateInput);
}

Task TaskDialog::getTask() const
{
    qDebug() << "TaskDialog::getTask() called";
    try {
        Task task(
            titleEdit->text().toStdString(),  // title
            descriptionEdit->toPlainText().toStdString(),  // description
            dueDateEdit->date().toString("yyyy-MM-dd").toStdString(),
            static_cast<Priority>(priorityCombo->currentIndex()),
            static_cast<Category>(categoryCombo->currentIndex()),
            m_isCompleted  // Используем сохраненный статус
        );
        qDebug() << "TaskDialog: Task created successfully with completed status:" << m_isCompleted;
        return task;
    } catch (const std::exception& e) {
        qDebug() << "TaskDialog: Error creating task:" << e.what();
        throw;
    }
}

void TaskDialog::setTask(const Task& task)
{
    titleEdit->setText(QString::fromStdString(task.getTitle()));
    descriptionEdit->setPlainText(QString::fromStdString(task.getDescription()));
    priorityCombo->setCurrentIndex(static_cast<int>(task.getPriority()));
    categoryCombo->setCurrentIndex(static_cast<int>(task.getCategory()));
    m_isCompleted = task.isCompleted();  // Сохраняем статус
    
    QDate date = QDate::fromString(QString::fromStdString(task.getDueDate()), "yyyy-MM-dd");
    if (date.isValid()) {
        dueDateEdit->setDate(date);
    }
}

void TaskDialog::validateInput()
{
    m_isValid = !titleEdit->text().isEmpty();
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_isValid);
}

void TaskDialog::accept()
{
    qDebug() << "TaskDialog::accept() called, m_isValid =" << m_isValid;
    if (m_isValid) {
        qDebug() << "TaskDialog: Validating task data before accepting...";
        qDebug() << "Title:" << titleEdit->text();
        qDebug() << "Description:" << descriptionEdit->toPlainText();
        qDebug() << "Priority:" << priorityCombo->currentIndex();
        qDebug() << "Category:" << categoryCombo->currentIndex();
        qDebug() << "Due date:" << dueDateEdit->date().toString("yyyy-MM-dd");
        QDialog::accept();
    } else {
        qDebug() << "TaskDialog: Invalid input, showing warning";
        QMessageBox::warning(this, tr("Invalid Input"), tr("Please enter a task title"));
    }
}