#include "gamek.h"
#include "ui_gamek.h"

gamek::gamek(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamek)
  , mouse(nullptr)
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
    createMouse();
    // Инициализация таймера
    connect(timer, &QTimer::timeout, this, &gamek::updateScene);
    timer->start(16);
}

gamek::~gamek()
{
    delete ui;
}


void gamek::createTextAndShapes() {
    QPen thickPen(Qt::red);
    thickPen.setWidth(8);

    // Группа для буквы "П"
    QGraphicsItemGroup* group1 = new QGraphicsItemGroup();
    group1->addToGroup(scene->addLine(20, 50, 20, 100, thickPen));
    group1->addToGroup(scene->addLine(20, 50, 40, 50, thickPen));
    group1->addToGroup(scene->addLine(40, 50, 40, 100, thickPen));
    group1->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group1);

    QGraphicsRectItem* hitbox1 = new QGraphicsRectItem(15, 40, 30, 70);
    hitbox1->setBrush(QBrush(Qt::NoBrush));
    hitbox1->setPen(Qt::NoPen);
    group1->addToGroup(hitbox1);

    // Группа для буквы "е"
    QGraphicsItemGroup* group2 = new QGraphicsItemGroup();
    group2->addToGroup(scene->addLine(60, 50, 60, 100, thickPen));
    group2->addToGroup(scene->addLine(60, 50, 90, 50, thickPen));
    group2->addToGroup(scene->addLine(60, 75, 85, 75, thickPen));
    group2->addToGroup(scene->addLine(60, 100, 90, 100, thickPen));
    group2->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group2);

    QGraphicsRectItem* hitbox2 = new QGraphicsRectItem(65, 40, 40, 70);
    hitbox2->setBrush(QBrush(Qt::NoBrush));
    hitbox2->setPen(Qt::NoPen);
    group2->addToGroup(hitbox2);

    // Группа для буквы "р"
    QGraphicsItemGroup* group3 = new QGraphicsItemGroup();
    group3->addToGroup(scene->addLine(110, 50, 110, 100, thickPen));
    group3->addToGroup(scene->addLine(110, 50, 130, 50, thickPen));
    group3->addToGroup(scene->addLine(130, 50, 130, 75, thickPen));
    group3->addToGroup(scene->addLine(130, 75, 110, 75, thickPen));
    group3->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group3);

    QGraphicsRectItem* hitbox3 = new QGraphicsRectItem(105, 40, 30, 70);
    hitbox3->setBrush(QBrush(Qt::NoBrush));
    hitbox3->setPen(Qt::NoPen);
    group3->addToGroup(hitbox3);

    // Группа для буквы "м"
    QGraphicsItemGroup* group4 = new QGraphicsItemGroup();
    group4->addToGroup(scene->addLine(150, 100, 150, 50, thickPen));
    group4->addToGroup(scene->addLine(150, 50, 160, 75, thickPen));
    group4->addToGroup(scene->addLine(160, 75, 170, 50, thickPen));
    group4->addToGroup(scene->addLine(170, 50, 170, 100, thickPen));
    group4->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group4);

    QGraphicsRectItem* hitbox4 = new QGraphicsRectItem(145, 40, 30, 70);
    hitbox4->setBrush(QBrush(Qt::NoBrush));
    hitbox4->setPen(Qt::NoPen);
    group4->addToGroup(hitbox4);

    // Группа для буквы "и"
    QGraphicsItemGroup* group5 = new QGraphicsItemGroup();
    group5->addToGroup(scene->addLine(190, 50, 190, 100, thickPen));
    group5->addToGroup(scene->addLine(190, 100, 210, 50, thickPen));
    group5->addToGroup(scene->addLine(210, 50, 210, 100, thickPen));
    group5->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group5);

    QGraphicsRectItem* hitbox5 = new QGraphicsRectItem(185, 40, 30, 70);
    hitbox5->setBrush(QBrush(Qt::NoBrush));
    hitbox5->setPen(Qt::NoPen);
    group5->addToGroup(hitbox5);

    // Группа для буквы "н"
    QGraphicsItemGroup* group6 = new QGraphicsItemGroup();
    group6->addToGroup(scene->addLine(230, 50, 230, 100, thickPen));
    group6->addToGroup(scene->addLine(230, 75, 250, 75, thickPen));
    group6->addToGroup(scene->addLine(250, 50, 250, 100, thickPen));
    group6->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group6);

    QGraphicsRectItem* hitbox6 = new QGraphicsRectItem(225, 40, 30, 70);
    hitbox6->setBrush(QBrush(Qt::NoBrush));
    hitbox6->setPen(Qt::NoPen);
    group6->addToGroup(hitbox6);

    // Группа для буквы "о"
    QGraphicsItemGroup* group7 = new QGraphicsItemGroup();
    QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(265, 50, 50, 50);
    circle->setPen(thickPen);
    circle->setBrush(QBrush(Qt::NoBrush));
    group7->addToGroup(circle);
    group7->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group7);

    QGraphicsRectItem* hitbox7 = new QGraphicsRectItem(265, 50, 50, 50);
    hitbox7->setBrush(QBrush(Qt::NoBrush));
    hitbox7->setPen(Qt::NoPen);
    group7->addToGroup(hitbox7);

    // Группа для буквы "в"
    QGraphicsItemGroup* group8 = new QGraphicsItemGroup();
    group8->addToGroup(scene->addLine(330, 50, 330, 100, thickPen));
    group8->addToGroup(scene->addLine(330, 50, 350, 50, thickPen));
    group8->addToGroup(scene->addLine(350, 50, 360, 75, thickPen));
    group8->addToGroup(scene->addLine(360, 75, 330, 75, thickPen));
    group8->addToGroup(scene->addLine(360, 75, 360, 100, thickPen));
    group8->addToGroup(scene->addLine(360, 100, 330, 100, thickPen));
    group8->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group8);

    QGraphicsRectItem* hitbox8 = new QGraphicsRectItem(325, 40, 40, 70);
    hitbox8->setBrush(QBrush(Qt::NoBrush));
    hitbox8->setPen(Qt::NoPen);
    group8->addToGroup(hitbox8);

    // Группа для буквы "а"
    QGraphicsItemGroup* group9 = new QGraphicsItemGroup();
    group9->addToGroup(scene->addLine(380, 100, 390, 50, thickPen));
    group9->addToGroup(scene->addLine(390, 50, 400, 100, thickPen));
    group9->addToGroup(scene->addLine(385, 75, 395, 75, thickPen)); // перекладина
    group9->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group9);

    QGraphicsRectItem* hitbox9 = new QGraphicsRectItem(385, 45, 30, 65);
    hitbox9->setBrush(QBrush(Qt::NoBrush));
    hitbox9->setPen(Qt::NoPen);
    group9->addToGroup(hitbox9);

    // Добавление текста "Катя"
    QGraphicsTextItem* surnameText = new QGraphicsTextItem("Катя");
    surnameText->setPos(50, 220);

    // Увеличиваем шрифт текста
    QFont font = surnameText->font();
    font.setPointSize(24); // Устанавливаем размер шрифта в 24 пункта
    surnameText->setFont(font);
    surnameText->setDefaultTextColor(Qt::black); // Устанавливаем цвет текста в розовый (magenta)

    // Делаем текст перемещаемым
    surnameText->setFlag(QGraphicsItem::ItemIsMovable);

    scene->addItem(surnameText);
}

void gamek::createMouse() {
    // Создание 'Мыши'
    mouse = new QGraphicsItemGroup(); // Создаем группу для мыши

    // Голова (овал)
    QGraphicsEllipseItem* head = new QGraphicsEllipseItem(-15, -20, 30, 30);
    head->setBrush(Qt::gray); // Задаем цвет головы
    mouse->addToGroup(head); // Добавляем голову в группу

    // Тело (овал)
    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(-20, 10, 40, 20);
    body->setBrush(Qt::gray); // Задаем цвет тела
    mouse->addToGroup(body); // Добавляем тело в группу

    // Уши (треугольники)
    QGraphicsPolygonItem* leftEar = new QGraphicsPolygonItem();
    QPolygonF leftEarShape;
    leftEarShape << QPointF(0, 0) << QPointF(-10, -10) << QPointF(0, -10);
    leftEar->setPolygon(leftEarShape);
    leftEar->setBrush(Qt::lightGray); // Задаем цвет уха
    leftEar->setPos(-15, -10); // Устанавливаем позицию уха
    mouse->addToGroup(leftEar);

    QGraphicsPolygonItem* rightEar = new QGraphicsPolygonItem();
    QPolygonF rightEarShape;
    rightEarShape << QPointF(0, 0) << QPointF(10, -10) << QPointF(0, -10);
    rightEar->setPolygon(rightEarShape);
    rightEar->setBrush(Qt::lightGray); // Задаем цвет уха
    rightEar->setPos(15, -10); // Устанавливаем позицию уха
    mouse->addToGroup(rightEar);

    // Хвост (линия)
    QGraphicsLineItem* tail = new QGraphicsLineItem(15, 20, 30, 30);
    tail->setPen(QPen(Qt::gray, 5)); // Задаем цвет и ширину хвоста
    mouse->addToGroup(tail); // Добавляем хвост в группу

    // Создаем хитбокс для "Мыши"
    QGraphicsRectItem* hitbox = new QGraphicsRectItem(-30, -30, 60, 50); // Задаем размеры хитбокса
    hitbox->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox->setPen(QPen(Qt::NoPen)); // Убираем границы хитбокса
    mouse->addToGroup(hitbox); // Добавляем хитбокс в группу

    mouse->setFlag(QGraphicsItem::ItemIsMovable, false); // Убираем возможность перетаскивания

    // Установка позиции для размещения в центре
    qreal centerX = (800 - 40) / 2; // 800 - ширина сцены, 40 - ширина головы
    qreal centerY = (600 - 100) / 2; // 600 - высота сцены, 100 - общее высота мыши
    mouse->setPos(centerX, centerY); // Устанавливаем позицию группы "Мыши"

    // Добавляем группу мыши на сцену
    scene->addItem(mouse);
    qDebug() << "Mouse created and added to scene"; // Отладочное сообщение
}


void gamek::updateScene() {
    // Получаем текущую позицию хитбокса "человечка"
    QRectF mouseHitbox = mouse->boundingRect().translated(mouse->pos());

    // Проверяем столкновения с границами сцены
    if (mouseHitbox.left() <= 0 || mouseHitbox.right() >= scene->width()) {
        dx = -dx; // Отражаем по оси X
    }
    if (mouseHitbox.top() <= 0 || mouseHitbox.bottom() >= scene->height()) {
        dy = -dy; // Отражаем по оси Y
    }

    // Проверяем столкновения с другими хитбоксами на сцене
    QList<QGraphicsItem*> items = scene->items(mouseHitbox, Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item : items) {
        if (item != mouse) { // Избегаем столкновения с самим собой
            QRectF itemHitbox = item->boundingRect().translated(item->pos());
            if (mouseHitbox.intersects(itemHitbox)) {
                // Определяем, в какую сторону отталкиваться
                qreal dxOverlap = (mouseHitbox.center().x() - itemHitbox.center().x());
                qreal dyOverlap = (mouseHitbox.center().y() - itemHitbox.center().y());

                if (qAbs(dxOverlap) > qAbs(dyOverlap)) {
                    dx = -dx; // Отражаем по оси X
                } else {
                    dy = -dy; // Отражаем по оси Y
                }
                collisionSound->play();
            }
        }
    }

    // Обновляем позицию "собаки"
    mouse->moveBy(dx, dy);
}
