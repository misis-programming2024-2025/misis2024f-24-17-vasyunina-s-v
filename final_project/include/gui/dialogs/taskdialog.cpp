#include "taskdialog.hpp"
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

TaskDialog::TaskDialog(QWidget* parent) 
    : QDialog(parent),
      titleEdit(new QLineEdit(this)),
      descriptionEdit(new QTextEdit(this)),
      priorityCombo(new QComboBox(this)),
      categoryCombo(new QComboBox(this)),
      dueDateEdit(new QDateEdit(QDate::currentDate(), this)),
      buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)),
      m_isValid(false)
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
    setWindowTitle(tr("Task Editor"));
    resize(400, 300);
    
    dueDateEdit->setCalendarPopup(true);
    dueDateEdit->setDisplayFormat("yyyy-MM-dd");
    
    priorityCombo->addItems({tr("Low"), tr("Medium"), tr("High")});
    categoryCombo->addItems({tr("Work"), tr("Personal"), tr("Study"), tr("Other")});
    
    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout();
    
    formLayout->addRow(new QLabel(tr("&Title:")), titleEdit);
    formLayout->addRow(new QLabel(tr("&Description:")), descriptionEdit);
    formLayout->addRow(new QLabel(tr("&Priority:")), priorityCombo);
    formLayout->addRow(new QLabel(tr("&Category:")), categoryCombo);
    formLayout->addRow(new QLabel(tr("&Due Date:")), dueDateEdit);
    
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
    Task task(
        titleEdit->text().toStdString(),  
        dueDateEdit->date().toString("yyyy-MM-dd").toStdString(),
        static_cast<Priority>(priorityCombo->currentIndex()),
        static_cast<Category>(categoryCombo->currentIndex()),
        false 
    );
    if (!descriptionEdit->toPlainText().isEmpty()) {
        task.updateDescription(descriptionEdit->toPlainText().toStdString());
    }
    
    return task;
}

void TaskDialog::setTask(const Task& task)
{
    titleEdit->setText(QString::fromStdString(task.getDescription()));
    descriptionEdit->setPlainText(QString::fromStdString(task.getDescription()));
    priorityCombo->setCurrentIndex(static_cast<int>(task.getPriority()));
    categoryCombo->setCurrentIndex(static_cast<int>(task.getCategory()));
    
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
    if (m_isValid) {
        QDialog::accept();
    } else {
        QMessageBox::warning(this, tr("Invalid Input"), tr("Please enter a task title"));
    }
}