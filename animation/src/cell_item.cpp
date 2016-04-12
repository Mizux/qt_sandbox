//! @file

#include "cell_item.hpp"
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QMimeData>

#include <QDebug>

CellItem::CellItem(QGraphicsItem* parent)
  : PixmapItem(":/img/cell.png", parent)
  , _dragOver(false) {
	setZValue(0);
	setAcceptDrops(true);
}

void
CellItem::paint(QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget) {
	PixmapItem::paint(painter, option, widget);

	if (!acceptDrops()) {
		painter->setPen(QPen(Qt::red, _pix.width() / 32, Qt::DashDotLine));
	} else {
		painter->setPen(QPen(Qt::green, _pix.width() / 32, Qt::DashDotLine));
	}
	painter->drawLine(0, 0, _pix.width(), _pix.height());
	painter->drawLine(0, _pix.height(), _pix.width(), 0);

	if (_dragOver && acceptDrops()) {
		painter->setPen(QPen(QColor(224, 224, 32), _pix.width() / 64));
		painter->setBrush(QColor(224, 224, 32, 128));
		painter->drawRoundedRect(
		  0, 0, _pix.width(), _pix.height(), 25, 25, Qt::RelativeSize);
	}
}

void
CellItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
	// qDebug() << "drag enter...";
	if (event->mimeData()->hasFormat("application/x-items")) {
		_dragOver = true;
		update();
		event->accept();
	} else {
		event->ignore();
	}
}

void
CellItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
	// qDebug() << "drag leave...";
	if (event->mimeData()->hasFormat("application/x-items")) {
		_dragOver = false;
		update();
		event->accept();
	} else {
		event->ignore();
	}
}

void
CellItem::dropEvent(QGraphicsSceneDragDropEvent* event) {
	// qDebug() << "drag drop...";
	if (event->mimeData()->hasFormat("application/x-items")) {
		_dragOver = false;
		update();
		event->accept();
	}
}
