#include "dialoggraphic.h"
#include "ui_dialoggraphic.h"
#include <QColorDialog>
#include <QInputDialog>

DialogGraphic::DialogGraphic(QWidget *parent) : QDialog(parent), ui(new Ui::DialogGraphic) {
    ui->setupUi(this);
    drawingArea = new DrawingArea(this);
    ui->verticalLayout->addWidget(drawingArea);
}

DialogGraphic::~DialogGraphic() {
    delete ui;
}

void DialogGraphic::on_btnColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose Brush Color");
    if (color.isValid()) {
        QPen pen = drawingArea->pen();
        pen.setColor(color);
        drawingArea->setPen(pen);
    }
}

void DialogGraphic::on_spinBoxSize_valueChanged(int value) {
    QPen pen = drawingArea->pen();
    pen.setWidth(value);
    drawingArea->setPen(pen);
}

void DialogGraphic::on_comboBoxStyle_currentIndexChanged(int index) {
    QPen pen = drawingArea->pen();
    switch (index) {
        case 0: pen.setStyle(Qt::SolidLine); break;
        case 1: pen.setStyle(Qt::DashLine); break;
        case 2: pen.setStyle(Qt::DotLine); break;
        case 3: pen.setStyle(Qt::DashDotLine); break;
    }
    drawingArea->setPen(pen);
}

void DialogGraphic::on_btnDraw_clicked() {
    drawingArea->setTool(DrawingArea::Draw);
}

void DialogGraphic::on_btnErase_clicked() {
    drawingArea->setTool(DrawingArea::Erase);
}

void DialogGraphic::on_eraseBoxSize_valueChanged(int value) {
    drawingArea->setEraserSize(value);
}

void DialogGraphic::on_btnAddRectangle_clicked() {
    // Получаем размеры фигуры от пользователя
        bool ok;
        int width = QInputDialog::getInt(this, tr("Shape Width"), tr("Width:"), 100, 1, 1000, 1, &ok);
        if (!ok) return;

        int height = QInputDialog::getInt(this, tr("Shape Height"), tr("Height:"), 100, 1, 1000, 1, &ok);
        if (!ok) return;

        // Получаем толщину обводки от пользователя
        int penWidth = QInputDialog::getInt(this, tr("Pen Width"), tr("Width of the border:"), 2, 1, 10, 1, &ok);
        if (!ok) return;

        // Получаем цвет заливки от пользователя
        QColor fillColor = QColorDialog::getColor(Qt::yellow, this, tr("Choose Fill Color"));
        if (!fillColor.isValid()) return;

        // Получаем цвет обводки
        QColor penColor = QColorDialog::getColor(Qt::black, this, tr("Choose Border Color"));
        if (!penColor.isValid()) return;

        // Создаем обводку с выбранным цветом и толщиной
        QPen pen(penColor, penWidth, Qt::SolidLine);

        // Получаем тип фигуры от QComboBox
        QString selectedShape = ui->comboBoxShape->currentText();
        DrawingArea::Tool shapeType = DrawingArea::Draw; // Значение по умолчанию

        if (selectedShape == "Circle") {
            shapeType = DrawingArea::Circle;
        } else if (selectedShape == "Triangle") {
            shapeType = DrawingArea::Triangle;
        } else {
            shapeType = DrawingArea::Draw; // Прямоугольник
        }

        // Добавляем нужную фигуру
        drawingArea->addShape(QRect(QPoint(10, 10), QSize(width, height)), pen, fillColor, shapeType);
}

void DialogGraphic::on_btnSetBackgroundColor_clicked() {
    QColor color = QColorDialog::getColor(drawingArea->backgroundColor(), this, "Choose Background Color");
    if (color.isValid()) {
        drawingArea->setBackgroundColor(color);
    }
}

void DialogGraphic::on_btnDeleteShapes_clicked() {
    drawingArea->clearShapes();
}

void DialogGraphic::on_btnLine_clicked()
{
    drawingArea->setTool(DrawingArea::Line);
}

void DialogGraphic::on_btnGame1_clicked()
{
    gamed *newDialog = new gamed(this);
    newDialog->exec(); // Use exec() to open it as a modal dialog
}

void DialogGraphic::on_btnGame2_clicked()
{
    gamem *newDialog = new gamem(this);
    newDialog->exec(); // Use exec() to open it as a modal dialog
}

void DialogGraphic::on_btnGame3_clicked()
{
    gamek *newDialog = new gamek(this);
    newDialog->exec(); // Use exec() to open it as a modal dialog
}

void DialogGraphic::on_btnClear_clicked()
{
    drawingArea->clearShapes();
        // Optionally, you could also clear lines if needed
        drawingArea->clearLines(); // You would need to implement this method if it doesn't exist
}
