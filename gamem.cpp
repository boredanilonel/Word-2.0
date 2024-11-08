#include "gamem.h"
#include "ui_gamem.h"

gamem::gamem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamem)
  , dog(nullptr)
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
    createDog();
    // Инициализация таймера
    connect(timer, &QTimer::timeout, this, &gamem::updateScene);
    timer->start(16);
}

gamem::~gamem()
{
    delete ui;
}

void gamem::createTextAndShapes() {
    QPen thickPen(Qt::magenta); // Устанавливаем цвет линий в розовый (magenta)
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
    group2->addToGroup(scene->addLine(70, 50, 60, 100, thickPen));
    group2->addToGroup(scene->addLine(70, 50, 80, 100, thickPen));
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

    // Группа для буквы "а"
    QGraphicsItemGroup* group7 = new QGraphicsItemGroup();
    group7->addToGroup(scene->addLine(255, 100, 265, 50, thickPen));
    group7->addToGroup(scene->addLine(265, 50, 275, 100, thickPen));
    group7->addToGroup(scene->addLine(260, 75, 270, 75, thickPen)); // перекладина
    group7->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(group7);

    // Добавление текста "Марина"
    QGraphicsTextItem* surnameText = new QGraphicsTextItem("Марина");
    surnameText->setPos(50, 220);

    // Увеличиваем шрифт текста
    QFont font = surnameText->font();
    font.setPointSize(24); // Устанавливаем размер шрифта в 24 пункта
    surnameText->setFont(font);
        surnameText->setDefaultTextColor(Qt::magenta); // Устанавливаем цвет текста в розовый (magenta)

    // Делаем текст перемещаемым
    surnameText->setFlag(QGraphicsItem::ItemIsMovable);

    scene->addItem(surnameText);
}

void gamem::createDog() {
    // Создание 'Собаки'
    dog = new QGraphicsItemGroup(); // Создаем группу для собаки

    // Голова
    QGraphicsEllipseItem* head = new QGraphicsEllipseItem(-20, -13, 40, 40);
    head->setBrush(QColor(139, 69, 19)); // Задаем цвет головы
    dog->addToGroup(head); // Добавляем голову в группу

    // Тело
    QGraphicsRectItem* body = new QGraphicsRectItem(-10, 25, 80, 40);
    body->setBrush(QColor(139, 69, 19)); // Задаем цвет тела
    dog->addToGroup(body); // Добавляем тело в группу

    // Ноги
    QGraphicsRectItem* leftLeg = new QGraphicsRectItem(-10, 60, 10, 30);
    leftLeg->setBrush(QColor(139, 69, 19)); // Цвет левой ноги
    dog->addToGroup(leftLeg); // Добавляем левую ногу в группу

    QGraphicsRectItem* rightLeg = new QGraphicsRectItem(60, 60, 10, 30);
    rightLeg->setBrush(QColor(139, 69, 19)); // Цвет правой ноги
    dog->addToGroup(rightLeg); // Добавляем правую ногу в группу

    // Хвост
    QGraphicsLineItem* tail = new QGraphicsLineItem(60, 30, 90, 60);
    tail->setPen(QPen(QColor(139, 69, 19), 5)); // Задаем цвет и ширину хвоста
    dog->addToGroup(tail); // Добавляем хвост в группу

    // Уши
    QGraphicsPolygonItem* leftEar = new QGraphicsPolygonItem();
    QPolygonF leftEarShape;
    leftEarShape << QPointF(0, 0) << QPointF(-10, -10) << QPointF(0, -10);
    leftEar->setPolygon(leftEarShape);
    leftEar->setBrush(QColor(139, 69, 19));
    leftEar->setPos(-20, 0);
    dog->addToGroup(leftEar);

    QGraphicsPolygonItem* rightEar = new QGraphicsPolygonItem();
    QPolygonF rightEarShape;
    rightEarShape << QPointF(0, 0) << QPointF(10, -10) << QPointF(0, -10);
    rightEar->setPolygon(rightEarShape);
    rightEar->setBrush(QColor(139, 69, 19));
    rightEar->setPos(18, 0);
    dog->addToGroup(rightEar);

    // Создаем хитбокс для "Собаки"
    QGraphicsRectItem* hitbox = new QGraphicsRectItem(-40, 0, 80, 100); // Задаем размеры хитбокса
    hitbox->setBrush(QBrush(Qt::NoBrush)); // Без заливки
    hitbox->setPen(QPen(Qt::NoPen)); // Убираем границы хитбокса
    dog->addToGroup(hitbox); // Добавляем хитбокс в группу

    dog->setFlag(QGraphicsItem::ItemIsMovable, false); // Убираем возможность перетаскивания

    // Установка позиции для размещения в центре
    qreal centerX = (800 - 40) / 2; // 800 - ширина сцены, 40 - ширина головы
    qreal centerY = (600 - 100) / 2; // 600 - высота сцены, 100 - общее высота собаки
    dog->setPos(centerX, centerY); // Устанавливаем позицию группы "Собаки"

    // Добавляем группу собаки на сцену
    scene->addItem(dog);
    qDebug() << "Dog created and added to scene"; // Отладочное сообщение
}


void gamem::updateScene() {
    // Получаем текущую позицию хитбокса "человечка"
    QRectF dogHitbox = dog->boundingRect().translated(dog->pos());

    // Проверяем столкновения с границами сцены
    if (dogHitbox.left() <= 0 || dogHitbox.right() >= scene->width()) {
        dx = -dx; // Отражаем по оси X
    }
    if (dogHitbox.top() <= 0 || dogHitbox.bottom() >= scene->height()) {
        dy = -dy; // Отражаем по оси Y
    }

    // Проверяем столкновения с другими хитбоксами на сцене
    QList<QGraphicsItem*> items = scene->items(dogHitbox, Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item : items) {
        if (item != dog) { // Избегаем столкновения с самим собой
            QRectF itemHitbox = item->boundingRect().translated(item->pos());
            if (dogHitbox.intersects(itemHitbox)) {
                // Определяем, в какую сторону отталкиваться
                qreal dxOverlap = (dogHitbox.center().x() - itemHitbox.center().x());
                qreal dyOverlap = (dogHitbox.center().y() - itemHitbox.center().y());

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
    dog->moveBy(dx, dy);
}
