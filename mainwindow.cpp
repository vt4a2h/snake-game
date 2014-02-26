#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "grid.h"
#include "snakepart.h"
#include "snake.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Scene(new QGraphicsScene())
    , m_TextMessage(new QGraphicsTextItem())
    , m_Item(nullptr)
    , m_Grid(new graphics_item::Grid(CELL_COUNT_H, CELL_COUNT_V, {CELL_WIDTH, CELL_HEIGHT}))
    , m_Snake(new snake::Snake())
    , m_Apple(nullptr)
    , m_SnakeTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->gv_Main->setScene(m_Scene.get());
    ui->gv_Main->installEventFilter(this);

    m_Scene->addItem(m_Grid);
    m_Scene->addItem(m_TextMessage);

    connectElements();
    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Snake;
}

bool MainWindow::eventFilter(QObject *o, QEvent *ev)
{
    if (o == ui->gv_Main) {
        if (ev->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(ev);

            if (m_GameStatus == InGame) {
                switch (keyEvent->key()) {
                case Qt::Key_Left:
                    if (m_Snake->direction() != snake::SnakePart::Right)
                        m_Snake->setDirection(snake::SnakePart::Left);
                    break;
                case Qt::Key_Right:
                    if (m_Snake->direction() != snake::SnakePart::Left)
                        m_Snake->setDirection(snake::SnakePart::Right);
                    break;
                case Qt::Key_Up:
                    if (m_Snake->direction() != snake::SnakePart::Down)
                        m_Snake->setDirection(snake::SnakePart::Up);
                    break;
                case Qt::Key_Down:
                    if (m_Snake->direction() != snake::SnakePart::Up)
                        m_Snake->setDirection(snake::SnakePart::Down);
                    break;
                }
            } else if (m_GameStatus == Lose && keyEvent->key() == Qt::Key_R){
                newGame();
            }

            return true;
        }
    }

    return QMainWindow::eventFilter(o, ev);
}

void MainWindow::newGame()
{
    clearSnake();
    setupElements();

    m_GameStatus = InGame;
    m_TextMessage->hide();
    itemToStart();
    m_SnakeTimer->start(200);
    emit needApple();
    qsrand(QTime::currentTime().msec());
}

void MainWindow::makeApple()
{
    if (m_Apple == nullptr){
        QPointF itemPos = m_Grid->boundingRect().topLeft();
        float margin = m_Grid->margin();
        do {
            itemPos.rx() += margin + CELL_WIDTH * (qrand() % CELL_COUNT_H);
            itemPos.ry() += margin + CELL_HEIGHT * (qrand() % CELL_COUNT_V);
        } while (m_Scene->itemAt(itemPos, ui->gv_Main->transform()) != m_Grid);

        m_Apple =  m_Scene->addPixmap(QPixmap(":/img/img/apple.png")
                                      .scaled(QSize(CELL_WIDTH - margin, CELL_HEIGHT - margin),
                                              Qt::IgnoreAspectRatio,
                                              Qt::SmoothTransformation)
                                      );
        m_Apple->setPos(itemPos);
    }
}

void MainWindow::moveItem()
{
    auto r = m_Grid->boundingRect();
    switch (m_Snake->direction()) {
    case snake::SnakePart::Right:
        if (m_Snake->head()->x() > r.right()){
            emit youLose();
            return;
        }
    case snake::SnakePart::Left:
        if (m_Snake->head()->x() < r.left()){
            emit youLose();
            return;
        }
    case snake::SnakePart::Up:
        if (m_Snake->head()->y() < r.top()){
            emit youLose();
            return;
        }
    case snake::SnakePart::Down:
        if (m_Snake->head()->y() > r.bottom()){
            emit youLose();
            return;
        }
    }
    m_Snake->moveDirection();
    checkCollides();
}

void MainWindow::playerLose()
{
    m_SnakeTimer->stop();
    m_Item->setDirection(snake::SnakePart::Right);
    m_TextMessage->show();
    m_GameStatus = Lose;
}

void MainWindow::setupElements()
{
    QPointF messagePos(m_Grid->width() / 2 + 10, - m_Grid->height() / 2);
    m_TextMessage->setPlainText(tr("Вы проиграли!\n\nНажмите \"r\" для начала новой игры."));
    m_TextMessage->setPos(messagePos);

    m_Item = new snake::SnakePart({CELL_WIDTH, CELL_HEIGHT});
    m_Scene->addItem(m_Item);

    m_Snake->setHead(m_Item);
}

void MainWindow::connectElements()
{
    connect(this, &MainWindow::youLose, this, &MainWindow::playerLose);
    connect(m_SnakeTimer, &QTimer::timeout, this, &MainWindow::moveItem);
    connect(this, &MainWindow::needApple, this, &MainWindow::makeApple);
}

void MainWindow::itemToStart()
{
    QPointF itemPos(-m_Grid->width() / 2 + m_Item->width() / 2, m_Grid->height() / 2 - m_Item->height() / 2);
    m_Item->setPos(itemPos);
}

void MainWindow::checkCollides()
{
    if (m_Snake->head()->collidesWithItem(m_Apple)) {
        snake::SnakePart *part = new snake::SnakePart(QSizeF(CELL_WIDTH, CELL_HEIGHT));
        part->setPos(m_Snake->head()->pos());
        m_Scene->addItem(part);

        m_Snake->addPart(part);
        part->moveDirection();

        m_Scene->removeItem(m_Apple);
        delete m_Apple;
        m_Apple = nullptr;
        emit needApple();
    } else if (m_Scene->items(m_Snake->head()->pos()).count() > 2) emit youLose();
}

void MainWindow::clearSnake()
{
    for(snake::SnakePart* x : m_Snake->parts()) {
        m_Scene->removeItem(x);
        delete x;
    }
    m_Snake->parts().clear();
    if (m_Apple != nullptr) {
        m_Scene->removeItem(m_Apple);
        m_Apple = nullptr;
    }
}
