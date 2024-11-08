#ifndef DIALOGGRAPHIC_H
#define DIALOGGRAPHIC_H

#include <QDialog>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include <QLine>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include "gamed.h"
#include "gamem.h"
#include "gamek.h"

namespace Ui { class DialogGraphic; }

class DrawingArea : public QWidget {
    Q_OBJECT

public:
    enum Tool {
            Draw,
            Erase,
            Circle,
            Triangle,
            Line
        };

    QPoint startPoint;

    QColor backgroundColor() const {
            return m_backgroundColor;
        }

    void clearLines() {
            lines.clear(); // Clear all lines
            update(); // Update the drawing area
        }

    DrawingArea(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_StaticContents);
        m_pen.setColor(Qt::black);
        m_pen.setWidth(2);
        m_pen.setStyle(Qt::SolidLine);
    }

    void setPen(const QPen &pen) {
        m_pen = pen;
        update();
    }

    QPen pen() const {
        return m_pen;
    }

    void setTool(Tool tool) {
        m_currentTool = tool;
    }

    void setEraserSize(int size) {
        m_eraserSize = size;
    }

    void setBackgroundColor(const QColor &color) {
        if (m_backgroundColor != color) { // Проверяем, изменился ли цвет
            m_backgroundColor = color;
            update(); // Обновляем виджет
        }
    }


    void addShape(const QRect &shape, const QPen &pen, const QColor &fillColor, Tool tool) {
            Shape newShape = {shape, pen, fillColor, tool};
            shapes.append(newShape);
            update();
        }

    void clearShapes() {
            shapes.clear();
            update();
        }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.fillRect(rect(), m_backgroundColor); // Заливаем цветом фон

        // Перерисовываем области рисования
        for (const Shape &shape : shapes) {
                    painter.setPen(shape.pen);
                    painter.setBrush(shape.fillColor);
                    switch (shape.tool) {
                        case Draw: // Прямоугольник
                            painter.drawRect(shape.rect);
                            break;
                        case Circle: // Круг
                            painter.drawEllipse(shape.rect);
                            break;
                        case Triangle: // Треугольник
                            QPainterPath path;
                            path.moveTo(shape.rect.topLeft());
                            path.lineTo(shape.rect.topRight());
                            path.lineTo(shape.rect.bottomLeft());
                            path.closeSubpath();
                            painter.drawPath(path);
                            break;
                    }
        }
        // Здесь можно добавить код для рисования линий, если они есть
        painter.setPen(m_pen);
        for (const QLine& line : lines) {
            painter.drawLine(line); // Для рисования линий
        }
        if (m_currentTool == Line) {
            painter.drawLine(startPoint, lastPoint); // Рисуем линию от начальной до текущей точки
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
                lastPoint = event->pos();
                drawing = true;

                if (m_currentTool == Line) {
                    startPoint = event->pos(); // Начало линии
                }
        }
        if (event->button() == Qt::RightButton) { // Используем правую кнопку мыши
               // Проверяем, возможно ли захватить фигуру для перемещения
               for (Shape &shape : shapes) {
                   if (shape.rect.contains(event->pos())) {
                       movingShape = &shape; // Сохраняем ссылку на фигуру для перемещения
                       lastMousePosition = event->pos();
                       break;
                   }
               }
           }

    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (drawing && (event->buttons() & Qt::LeftButton)) {
            if (m_currentTool == Draw) {
                QLine line(lastPoint, event->pos());
                lines.append(line);
                lastPoint = event->pos();
                update();
            } else if (m_currentTool == Erase) {
                QRect eraseRect(event->pos() - QPoint(m_eraserSize / 2, m_eraserSize / 2), QSize(m_eraserSize, m_eraserSize));
                QList<QLine> newLines;
                for (const QLine &line : lines) {
                    if (!eraseRect.intersects(QRect(line.p1(), line.p2()))) {
                        newLines.append(line); // Добавляем линию, если она не пересекается с областью стирания
                    }
                }
                lines = newLines; // Обновляем список линий
                update();
            }
        }
        if (movingShape) {
                // Обновляем позицию фигуры во время перемещения
                int dx = event->pos().x() - lastMousePosition.x();
                int dy = event->pos().y() - lastMousePosition.y();

                movingShape->rect.moveTopLeft(movingShape->rect.topLeft() + QPoint(dx, dy));
                lastMousePosition = event->pos();

                update(); // Перерисовываем виджет
            }
        if (m_currentTool == Line && drawing) {
            update(); // Обновляем для перерисовки линии
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            drawing = false;
        }
        if (event->button() == Qt::RightButton) { // Проверяем, была ли отпущена правая кнопка
                movingShape = nullptr; // Завершаем перемещение
            }
        if (event->button() == Qt::LeftButton && m_currentTool == Line) {
            lines.append(QLine(startPoint, event->pos())); // Сохраняем линию
            drawing = false;
        }
    }

private:
    QPen m_pen;
    QPen m_currentPen;
    QList<QLine> lines;
    QPoint lastPoint;
    bool drawing = false;
    Tool m_currentTool = Draw;
    int m_eraserSize = 10; // Размер ластика по умолчанию
    struct Shape {
            QRect rect;
            QPen pen;
            QColor fillColor;
            Tool tool; // добавлено поле для инструмента/типа фигуры
        };
    QList<Shape> shapes;
    QColor m_backgroundColor = Qt::white;
    Shape *movingShape = nullptr; // Текущая фигура для перемещения
    QPoint lastMousePosition; // Последняя позиция мыши
};

class DialogGraphic : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGraphic(QWidget *parent = nullptr);
    ~DialogGraphic();

private slots:
    void on_btnColor_clicked();

    void on_spinBoxSize_valueChanged(int value);

    void on_comboBoxStyle_currentIndexChanged(int index);

    void on_btnDraw_clicked();

    void on_btnErase_clicked();

    void on_eraseBoxSize_valueChanged(int value);

    void on_btnAddRectangle_clicked();

    void on_btnSetBackgroundColor_clicked();

    void on_btnDeleteShapes_clicked();

    void on_btnLine_clicked();

    void on_btnGame1_clicked();

    void on_btnGame2_clicked();

    void on_btnGame3_clicked();

    void on_btnClear_clicked();

private:
    Ui::DialogGraphic *ui;
    DrawingArea *drawingArea;
    QVBoxLayout *verticalLayout;
};

#endif // DIALOGGRAPHIC_H
