#ifndef GAMED_H
#define GAMED_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QSet>

namespace Ui {
class gamed;
}

class gamed : public QDialog
{
    Q_OBJECT

public:
    gamed(QWidget *parent = nullptr);
    ~gamed();

protected:

private slots:
    void updateScene();
    void createTextAndShapes();
    void createHuman();

private:
    Ui::gamed *ui;
    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    QGraphicsItemGroup *human;
    QTimer *timer;
    int speed; // Переменная для хранения скорости движения
    double dx; // Переменная для скорости по оси X
    double dy; // Переменная для скорости по оси Y
     QMediaPlayer *collisionSound; // Звук столкновения
};

#endif // GAMED_H
