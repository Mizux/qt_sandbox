//! @file

#include "Item.hpp"

#include <QCursor>
#include <QPainter>
#include <QPixmapCache>

Item::Item(QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , _dragStart(false) {
	setTransformOriginPoint(0.5, 0.5);
	setZValue(1);

	setCursor(Qt::OpenHandCursor);
}

QRectF
Item::boundingRect() const {
	return QRectF(QPointF(0, 0), QPointF(1, 1));
}

void
Item::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
	if (_dragStart) painter->setOpacity(0.5);
	painter->drawPixmap(QRect(0, 0, 1, 1), pixmap());
}

QPixmap
Item::pixmap() {
	QPixmap pm;
	if (!QPixmapCache::find("item", &pm)) {
		pm = QPixmap(256, 256);
		pm.fill(Qt::transparent);
		QPainter* painter = new QPainter(&pm);
		painter->setPen(QColor(0, 0, 192, 128));
		painter->setBrush(QColor(0, 0, 192));
		painter->drawEllipse(
		  QPoint(pm.width() / 2, pm.height() / 2), pm.width() / 3, pm.height() / 3);
		delete painter;
		QPixmapCache::insert("item", pm);
	}
	return pm;
}

void
Item::dragStart() {
	_dragStart = true;
	update();
}

void
Item::dragStop() {
	_dragStart = false;
	update();
}
