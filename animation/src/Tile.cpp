//! @file

#include "Tile.hpp"

#include "GraphicsView.hpp"
#include <QGraphicsSceneEvent>
#include <QMimeData>
#include <QPainter>
#include <QPixmapCache>

Tile::Tile(QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , _dragOver(false) {
	setTransformOriginPoint(0.5, 0.5);
	setZValue(0);
	setAcceptDrops(true);
}

QRectF
Tile::boundingRect() const {
	return QRectF(QPointF(0, 0), QPointF(1, 1));
}

void
Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
	painter->drawPixmap(QRect(0, 0, 1, 1), pixmap());

	// Draw "NoEntry" sign if Drop forbidden
	if (!acceptDrops()) {
		painter->setPen(QPen(Qt::NoPen));
		painter->setBrush(QColor(160, 0, 0));
		painter->drawEllipse(QPointF(0.5, 0.5), 0.375, 0.375);

		painter->setBrush(QColor(255, 255, 255));
		painter->drawRect(QRectF(0.25, 0.4375, 0.5, 0.125));
	}

	// Draw Drop Enabled feedback
	if (_dragOver && acceptDrops()) {
		painter->setPen(QPen(QColor(224, 224, 32), 0.05, Qt::SolidLine));
		painter->setBrush(QColor(224, 224, 32, 128));
		painter->drawRoundedRect(0, 0, 1, 1, 25, 25, Qt::RelativeSize);
	}
}

QPixmap
Tile::pixmap() {
	QPixmap pm;
	if (!QPixmapCache::find("tile", &pm)) {
		pm                = QPixmap(256, 256);
		QPainter* painter = new QPainter(&pm);
		painter->setPen(QColor(32, 32, 32));
		painter->setBrush(QColor(32, 32, 32));
		painter->drawRect(0, 0, pm.width(), pm.height());
		painter->setPen(QColor(64, 64, 64));
		painter->setBrush(QColor(64, 64, 64));
		painter->drawRoundedRect(QRect(pm.width() / 8,
		                               pm.height() / 8,
		                               pm.width() * 6 / 8,
		                               pm.height() * 6 / 8),
		                         25,
		                         25,
		                         Qt::RelativeSize);
		delete painter;
		QPixmapCache::insert("tile", pm);
	}
	return pm;
}

void
Tile::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
	if (event->mimeData()->hasFormat("application/x-items")) {
		_dragOver = true;
		event->accept();
		update();
	} else {
		event->ignore();
	}
}

void
Tile::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
	if (event->mimeData()->hasFormat("application/x-items")) {
		_dragOver = false;
		event->accept();
		update();
	} else {
		event->ignore();
	}
}

void
Tile::dropEvent(QGraphicsSceneDragDropEvent* event) {
	if (event->mimeData()->hasFormat("application/x-items")) {
		_dragOver = false;
		dynamic_cast<GraphicsView*>(event->source())->setDropPos(pos());
		event->acceptProposedAction();
		event->accept();
		update();
	}
}
