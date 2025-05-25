#ifndef TASKDIALOG_HPP
#define TASKDIALOG_HPP

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include "task/task.hpp"

class TaskDialog : public QDialog
{
    Q_OBJECT 

public:
    explicit TaskDialog(QWidget* parent = nullptr);
    TaskDialog(const Task& task, QWidget* parent = nullptr);
    Task getTask() const;
    void setTask(const Task& task);

private slots:
    void accept() override;
    void validateInput();

private:
    void initUI();
    void setupConnections();
    
    QLineEdit* titleEdit;
    QTextEdit* descriptionEdit;
    QComboBox* priorityCombo;
    QComboBox* categoryCombo;
    QDateEdit* dueDateEdit;
    QDialogButtonBox* buttonBox;
    bool m_isValid;
    bool m_isCompleted;
};

#endif