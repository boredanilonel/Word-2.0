#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QTextEdit *editor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    textEdit(editor) // Сохраняем указатель на редактор
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getFindText() const {
    return ui->findLineEdit->text();
}

QString Dialog::getReplaceText() const {
    return ui->replaceLineEdit->text();
}

void Dialog::on_replaceButton_clicked()
{
    QString findText = getFindText();
        QString replaceText = getReplaceText();

        // Получаем текст из редактора
        QString content = textEdit->toPlainText();

        // Заменяем текст
        content.replace(findText, replaceText);

        // Устанавливаем новый текст в редактор
        textEdit->setPlainText(content);

        // Закрываем диалог после замены (по желанию)
        this->close();
}

void Dialog::on_closeButton_clicked()
{
    this->close();
}

void Dialog::on_findButton_clicked()
{
    QString findText = getFindText();

        if (findText.isEmpty()) {
            QMessageBox::warning(this, tr("Warning"), tr("Please enter text to find."));
            return;
        }

        // Получаем текст из редактора
        QString content = textEdit->toPlainText();

        // Ищем текст
        int index = content.indexOf(findText, 0, Qt::CaseInsensitive);
        if (index != -1) {
            // Если текст найден, выделяем его
            QTextCursor cursor = textEdit->textCursor();
            cursor.setPosition(index);
            cursor.setPosition(index + findText.length(), QTextCursor::KeepAnchor);
            textEdit->setTextCursor(cursor);
            textEdit->setFocus();
        } else {
            QMessageBox::information(this, tr("Information"), tr("Text not found."));
        }
}
