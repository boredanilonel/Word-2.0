#ifndef GAMEK_H
#define GAMEK_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QSet>

namespace Ui {
class gamek;
}

class gamek : public QDialog
{
    Q_OBJECT

public:
    gamek(QWidget *parent = nullptr);
    ~gamek();

protected:

private slots:
    void updateScene();
    void createTextAndShapes();
    void createMouse();

private:
    Ui::gamek *ui;
    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    QGraphicsItemGroup *mouse;
    QTimer *timer;
    int speed; // Переменная для хранения скорости движения
    double dx; // Переменная для скорости по оси X
    double dy; // Переменная для скорости по оси Y
     QMediaPlayer *collisionSound; // Звук столкновения
};

#endif // GAMEK_H
