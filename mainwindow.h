#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QTime>

#include <memory>

namespace Ui {
    class MainWindow;
}

namespace snake {
    class SnakePart;
    class Snake;
}

namespace graphics_item {
    class Grid;
}

using Scene = std::unique_ptr<QGraphicsScene>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject *o, QEvent *ev) override;

    void newGame();

public slots:
    void makeApple();
    void moveItem();

signals:
    void youLose();
    void needApple();

private:
    enum GameStatus{InGame, Win, Lose};

    void playerLose();
    void setupElements();
    void connectElements();
    void itemToStart();
    void checkCollides();
    void clearSnake();

    static constexpr size_t CELL_COUNT_H = 30;
    static constexpr size_t CELL_COUNT_V = 30;
    static constexpr float  CELL_HEIGHT  = 20;
    static constexpr float  CELL_WIDTH   = 20;

    Ui::MainWindow *ui;

    Scene m_Scene;
    QGraphicsTextItem *m_TextMessage;
    snake::SnakePart *m_Item;
    graphics_item::Grid *m_Grid;

    snake::Snake *m_Snake;

    GameStatus m_GameStatus;
    QGraphicsPixmapItem *m_Apple;

    QTimer *m_SnakeTimer;
};

#endif // MAINWINDOW_H
