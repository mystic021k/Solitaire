#pragma once
#include <QGraphicsView>

class QSolitaireView :
    public QGraphicsView
{
    Q_OBJECT
signals:
    void select_piece(QPoint pos);
    void hover_blank(QPoint pos);
    void down_piece(QPoint pos);
public:
    QSolitaireView(QWidget* parent);
    QSolitaireView(QGraphicsScene* scene, QWidget* parent);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};
