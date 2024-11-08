#ifndef GAMEM_H
#define GAMEM_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QSet>

namespace Ui {
class gamem;
}

class gamem : public QDialog
{
    Q_OBJECT

public:
    gamem(QWidget *parent = nullptr);
    ~gamem();

protected:

private slots:
    void updateScene();
    void createTextAndShapes();
    void createDog();

private:
    Ui::gamem *ui;
    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    QGraphicsItemGroup *dog;
    QTimer *timer;
    int speed; // Переменная для хранения скорости движения
    double dx; // Переменная для скорости по оси X
    double dy; // Переменная для скорости по оси Y
     QMediaPlayer *collisionSound; // Звук столкновения
};

#endif // GAMEM_H
