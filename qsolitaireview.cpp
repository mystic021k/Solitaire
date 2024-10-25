#include "qsolitaireview.h"
#include <QMouseEvent>
#include <QDebug>

QSolitaireView::QSolitaireView(QWidget* parent)
	: QGraphicsView(parent)
{
}

QSolitaireView::QSolitaireView(QGraphicsScene* scene, QWidget* parent)
	: QGraphicsView(scene, parent)
{
}

void QSolitaireView::mousePressEvent(QMouseEvent* event)
{
	emit select_piece(event->pos());
}

void QSolitaireView::mouseMoveEvent(QMouseEvent* event)
{
	emit hover_blank(event->pos());
}

void QSolitaireView::mouseReleaseEvent(QMouseEvent* event)
{
	emit down_piece(event->pos());
}
