#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
{
        ui->setupUi(this);
        connect(ui->textEdit, &QTextEdit::textChanged, this, [this]() {
        });
        new QShortcut(QKeySequence("Ctrl+S"), this, SLOT(on_saveFile_clicked()));      // Ctrl+S для сохранения
        new QShortcut(QKeySequence("Ctrl+O"), this, SLOT(on_openFile_clicked()));      // Ctrl+O для открытия
        new QShortcut(QKeySequence("Ctrl+F"), this, SLOT(on_search_clicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

//Комбобоксы с размером шрифта и цветом текста

void MainWindow::on_sizeChange_currentIndexChanged(const QString& size)
{
    // Обработка изменения размера текста
        qreal newSize = size.toDouble();  // Преобразуем текст в число

        // Получаем текущий текстовый курсор
        QTextCursor cursor = ui->textEdit->textCursor();

        // Меняем размер шрифта выделенного текста
        QTextCharFormat format;
        format.setFontPointSize(newSize);
        cursor.mergeCharFormat(format);  // Применяем формат к выделенному тексту

        // Устанавливаем курсор обратно
        ui->textEdit->setTextCursor(cursor);
        // Изменение шрифта только в выделенной ячейке таблицы
            QTableWidget *currentTable = qobject_cast<QTableWidget*>(ui->tabWidget->currentWidget());
            if (currentTable) {
                int currentRow = currentTable->currentRow();
                int currentColumn = currentTable->currentColumn();

                if (currentRow >= 0 && currentColumn >= 0) {
                    QTableWidgetItem *item = currentTable->item(currentRow, currentColumn);
                    if (item) {
                        QFont font = item->font();
                        font.setPointSize(newSize);
                        item->setFont(font);
                    }
                }
            }
}

void MainWindow::on_colorChange_currentIndexChanged(const QString& color)
{
    // Создаем объект QColor на основе выбранного цвета
        QColor selectedColor;
        if (color == "Black") selectedColor = Qt::black;
        else if (color == "Red") selectedColor = Qt::red;
        else if (color == "Green") selectedColor = Qt::green;
        else if (color == "Blue") selectedColor = Qt::blue;
        else if (color == "Pink") selectedColor = Qt::magenta;  // Используем magenta для pink
        else if (color == "Orange") selectedColor = QColor(255, 165, 0); // Параметры RGB для оранжевого
        else if (color == "Yellow") selectedColor = Qt::yellow;

        // Получаем текущий текстовый курсор
        QTextCursor cursor = ui->textEdit->textCursor();

        // Меняем цвет шрифта выделенного текста
        QTextCharFormat format;
        format.setForeground(selectedColor);
        cursor.mergeCharFormat(format);  // Применяем формат к выделенному тексту

        // Устанавливаем курсор обратно
        ui->textEdit->setTextCursor(cursor);
        QTableWidget *currentTable = qobject_cast<QTableWidget*>(ui->tabWidget->currentWidget());
            if (currentTable) {
                for (int row = 0; row < currentTable->rowCount(); ++row) {
                    for (int col = 0; col < currentTable->columnCount(); ++col) {
                        QTableWidgetItem *item = currentTable->item(row, col);
                        if (item) {
                            item->setForeground(selectedColor);
                        }
                    }
                }
            }
}

