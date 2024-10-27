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
	QPoint point = event->pos();
	emit select_piece(&point);
}

void QSolitaireView::mouseMoveEvent(QMouseEvent* event)
{
	QPoint point = event->pos();
	emit hover_blank(&point);
}

void QSolitaireView::mouseReleaseEvent(QMouseEvent* event)
{
	QPoint point = event->pos();
	emit down_piece(&point);
}
