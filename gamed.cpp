#include "gamed.h"
#include "ui_gamed.h"

gamed::gamed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamed)
    , human(nullptr)
    , timer(new QTimer(this))
    , speed(5) // Устанавливаем скорость движения на 5 пикселей
    , dx(speed) // Начальная скорость по X
    , dy(speed) // Начальная скорость по Y, отрицательное значение для движения вверх
{
    ui->setupUi(this);
    // Инициализация QMediaPlayer
        collisionSound = new QMediaPlayer(this);
        collisionSound->setMedia(QUrl::fromLocalFile("C:/Qt/Game/sound1.mp3")); // Укажите путь к звуковому файлу

    // Создаём сцену
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0, 0, 800, 600);

    // Добавление стен (в виде прямоугольников)
    scene->addRect(0, 0, 800, 10, QPen(), QBrush(Qt::black)); // верхняя
    scene->addRect(0, 590, 800, 10, QPen(), QBrush(Qt::black)); // нижняя
    scene->addRect(0, 0, 10, 600, QPen(), QBrush(Qt::black)); // левая
    scene->addRect(790, 0, 10, 600, QPen(), QBrush(Qt::black)); // правая

    createTextAndShapes(); // Здесь добавляем вызов вашего нового метода
    createHuman();
    // Инициализация таймера
    connect(timer, &QTimer::timeout, this, &gamed::updateScene);
    timer->start(16);
}

gamed::~gamed()
{
    delete ui;
}

void gamed::createTextAndShapes() {
    QPen thickPen(Qt::black);
    thickPen.setWidth(8); // Устанавливаем толщину в 8 пикселей

    // Группа для буквы "в"
    QGraphicsItemGroup* group1 = new QGraphicsItemGroup();
    group1->addToGroup(scene->addLine(20, 50, 20, 100, thickPen));
    group1->addToGroup(scene->addLine(20, 50, 40, 50, thickPen));
    group1->addToGroup(scene->addLine(40, 50, 50, 75, thickPen));
    group1->addToGroup(scene->addLine(50, 75, 20, 75, thickPen));
    group1->addToGroup(scene->addLine(50, 75, 50, 100, thickPen));
    group1->addToGroup(scene->addLine(50, 100, 20, 100, thickPen));
    group1->setFlag(QGraphicsItem::ItemIsMovable); // Делаем группу перетаскиваемой
    scene->addItem(group1);

    // Хитбокс для буквы "в"
    QGraphicsRectItem* hitbox1 = new QGraphicsRectItem(15, 40, 40, 70);
    hitbox1->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox1->setPen(Qt::NoPen); // Убираем границы
    group1->addToGroup(hitbox1); // Добавляем хитбокс в группу

    // Группа для буквы "л"
    QGraphicsItemGroup* group2 = new QGraphicsItemGroup();
    group2->addToGroup(scene->addLine(60, 50, 60, 100, thickPen));
    group2->addToGroup(scene->addLine(60, 50, 80, 50, thickPen));
    group2->addToGroup(scene->addLine(80, 50, 80, 100, thickPen));
    group2->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group2);

    // Хитбокс для буквы "л"
    QGraphicsRectItem* hitbox2 = new QGraphicsRectItem(55, 40, 30, 70);
    hitbox2->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox2->setPen(Qt::NoPen); // Убираем границы
    group2->addToGroup(hitbox2); // Добавляем хитбокс в группу

    // Группа для буквы "а"
    QGraphicsItemGroup* group3 = new QGraphicsItemGroup();
    group3->addToGroup(scene->addLine(90, 100, 100, 50, thickPen));
    group3->addToGroup(scene->addLine(100, 50, 110, 100, thickPen));
    group3->addToGroup(scene->addLine(95, 75, 105, 75, thickPen)); // перекладина
    group3->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group3);

    // Хитбокс для буквы "а"
    QGraphicsRectItem* hitbox3 = new QGraphicsRectItem(85, 45, 30, 65);
    hitbox3->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox3->setPen(Qt::NoPen); // Убираем границы
    group3->addToGroup(hitbox3); // Добавляем хитбокс в группу

    // Группа для буквы "с"
    QGraphicsItemGroup* group4 = new QGraphicsItemGroup();
    group4->addToGroup(scene->addLine(120, 50, 120, 100, thickPen));
    group4->addToGroup(scene->addLine(120, 50, 150, 50, thickPen));
    group4->addToGroup(scene->addLine(120, 100, 150, 100, thickPen));
    group4->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group4);

    // Хитбокс для буквы "с"
    QGraphicsRectItem* hitbox4 = new QGraphicsRectItem(115, 45, 40, 60);
    hitbox4->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox4->setPen(Qt::NoPen); // Убираем границы
    group4->addToGroup(hitbox4); // Добавляем хитбокс в группу

    // Группа для буквы "о"
    QGraphicsItemGroup* group5 = new QGraphicsItemGroup();
    QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(150, 50, 50, 50);
    circle->setPen(thickPen);
    circle->setBrush(QBrush(Qt::NoBrush)); // Окружность без заливки
    group5->addToGroup(circle);
    group5->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group5);

    // Хитбокс для буквы "о"
    QGraphicsRectItem* hitbox5 = new QGraphicsRectItem(145, 50, 50, 50);
    hitbox5->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox5->setPen(Qt::NoPen); // Убираем границы
    group5->addToGroup(hitbox5); // Добавляем хитбокс в группу

    // Группа для буквы "в"
    QGraphicsItemGroup* group6 = new QGraphicsItemGroup();
    group6->addToGroup(scene->addLine(210, 50, 210, 100, thickPen));
    group6->addToGroup(scene->addLine(210, 50, 230, 50, thickPen));
    group6->addToGroup(scene->addLine(230, 50, 240, 75, thickPen));
    group6->addToGroup(scene->addLine(240, 75, 210, 75, thickPen));
    group6->addToGroup(scene->addLine(240, 75, 240, 100, thickPen));
    group6->addToGroup(scene->addLine(240, 100, 210, 100, thickPen));
    group6->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group6);

    // Хитбокс для буквы "в"
    QGraphicsRectItem* hitbox6 = new QGraphicsRectItem(205, 40, 40, 70);
    hitbox6->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox6->setPen(Qt::NoPen); // Убираем границы
    group6->addToGroup(hitbox6); // Добавляем хитбокс в группу

    // Добавление текста "Данил"
    QGraphicsTextItem* surnameText = new QGraphicsTextItem("Данил");
    surnameText->setPos(50, 220);

    // Увеличиваем шрифт текста
    QFont font = surnameText->font();
    font.setPointSize(24); // Устанавливаем размер шрифта в 24 пункта
    surnameText->setFont(font);

    // Делаем текст перемещаемым
    surnameText->setFlag(QGraphicsItem::ItemIsMovable);

    scene->addItem(surnameText);
}

void gamed::createHuman() {
    // Создание 'Человека'
    human = new QGraphicsItemGroup(); // Создаем группу для человека

    // Голова
    QGraphicsEllipseItem* head = new QGraphicsEllipseItem(0, 0, 20, 20);
    head->setBrush(Qt::blue);
    human->addToGroup(head); // Добавляем голову в группу

    // Тело
    QGraphicsLineItem* body = new QGraphicsLineItem(10, 20, 10, 70);
    body->setPen(QPen(Qt::blue, 5)); // Устанавливаем цвет и ширину линии
    human->addToGroup(body); // Добавляем тело в группу

    // Руки
    QGraphicsLineItem* leftArm = new QGraphicsLineItem(10, 30, -20, 30);
    leftArm->setPen(QPen(Qt::blue, 5));
    human->addToGroup(leftArm); // Добавляем левую руку в группу

    QGraphicsLineItem* rightArm = new QGraphicsLineItem(10, 30, 40, 30);
    rightArm->setPen(QPen(Qt::blue, 5));
    human->addToGroup(rightArm); // Добавляем правую руку в группу

    // Ноги
    QGraphicsLineItem* leftLeg = new QGraphicsLineItem(10, 70, -10, 110);
    leftLeg->setPen(QPen(Qt::blue, 5));
    human->addToGroup(leftLeg); // Добавляем левую ногу в группу

    QGraphicsLineItem* rightLeg = new QGraphicsLineItem(10, 70, 30, 110);
    rightLeg->setPen(QPen(Qt::blue, 5));
    human->addToGroup(rightLeg); // Добавляем правую ногу в группу

    // Создаем хитбокс для "Человека"
    QGraphicsRectItem* hitbox = new QGraphicsRectItem(-20, 0, 60, 110); // Задаем размеры хитбокса
    hitbox->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox->setPen(QPen(Qt::NoPen)); // Устанавливаем цвет границы хитбокса
    human->addToGroup(hitbox); // Добавляем хитбокс в группу

    human->setFlag(QGraphicsItem::ItemIsMovable, false); // Убираем возможность перетаскивания

    // Установка позиции для размещения в центре
    qreal centerX = (800 - 20) / 2; // 800 - ширина сцены, 20 - ширина головы
    qreal centerY = (600 - 110) / 2; // 600 - высота сцены, 110 - общее высота человека
    human->setPos(centerX, centerY); // Устанавливаем позицию группы "Человека"

    // Добавляем группу человека на сцену
    scene->addItem(human);
    qDebug() << "Human created and added to scene"; // Отладочное сообщение
}

void gamed::updateScene() {
    // Получаем текущую позицию хитбокса "человечка"
    QRectF humanHitbox = human->boundingRect().translated(human->pos());

    // Проверяем столкновения с границами сцены
    if (humanHitbox.left() <= 0 || humanHitbox.right() >= scene->width()) {
        dx = -dx; // Отражаем по оси X
    }
    if (humanHitbox.top() <= 0 || humanHitbox.bottom() >= scene->height()) {
        dy = -dy; // Отражаем по оси Y
    }

    // Проверяем столкновения с другими хитбоксами на сцене
    QList<QGraphicsItem*> items = scene->items(humanHitbox, Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item : items) {
        if (item != human) { // Избегаем столкновения с самим собой
            QRectF itemHitbox = item->boundingRect().translated(item->pos());
            if (humanHitbox.intersects(itemHitbox)) {
                // Определяем, в какую сторону отталкиваться
                qreal dxOverlap = (humanHitbox.center().x() - itemHitbox.center().x());
                qreal dyOverlap = (humanHitbox.center().y() - itemHitbox.center().y());

                if (qAbs(dxOverlap) > qAbs(dyOverlap)) {
                    dx = -dx; // Отражаем по оси X
                } else {
                    dy = -dy; // Отражаем по оси Y
                }
                collisionSound->play();
            }
        }
    }

    // Обновляем позицию "человечка"
    human->moveBy(dx, dy);
}
