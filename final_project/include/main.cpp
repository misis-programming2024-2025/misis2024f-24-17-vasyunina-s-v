#include "gui/mainwindow/mainwindow.hpp"  
#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include <QDebug>

/**
 * @brief Точка входа в приложение
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения приложения
 * 
 * Инициализирует Qt-приложение, настраивает глобальные стили,
 * создает и отображает главное окно.
 */
int main(int argc, char *argv[])
{
    // 1. Инициализация Qt-приложения
    QApplication app(argc, argv);
    
    // 2. Настройка информации о приложении
    app.setApplicationName("Менеджер задач");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("MyCompany");
    app.setWindowIcon(QIcon(":/icons/app_icon.svg"));  // Иконка приложения

    // 3. Настройка глобальных стилей (опционально)
    QApplication::setStyle(QStyleFactory::create("Fusion"));  // Современный стиль
    
    // 4. Загрузка глобального стиля из QSS-файла
    QFile styleFile(":/styles/main.qss");
    if(styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        app.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
    else
    {
        qWarning() << "Не удалось загрузить файл стилей:" << styleFile.errorString();
    }

    // 5. Создание и отображение главного окна
    MainWindow mainWindow;
    mainWindow.show();

    // 6. Запуск основного цикла обработки событий
    return app.exec();
}