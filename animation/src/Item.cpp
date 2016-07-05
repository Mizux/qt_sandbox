//! @file

#include "Item.hpp"

#include <QCursor>
#include <QPainter>
#include <QPixmapCache>

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

#include <QDebug>

Item::Item(QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , _dragStart(false) {
	setTransformOriginPoint(0.5, 0.5);
	setZValue(1);

  setAcceptedMouseButtons(Qt::LeftButton);
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
Item::setDropPos(const QPointF& pos) {
	_dropPos = pos;
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

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QPointF currentPos = pos();
  qDebug() << "currentPos:" << currentPos;

	// Then create DragDrop event
	{
		QDrag* drag     = new QDrag(this);
		QMimeData* data = new QMimeData;
		data->setData("application/x-items", QByteArray());
		drag->setMimeData(data);

		// A tile size = 1x1 * fitInView Factor
		// HotSpot = middle of the tile
		QTransform tf = transform();
		qDebug() << "Transform:" << tf;
		//drag->setHotSpot(QPoint((tf.m11() + 0.5) / 2, (tf.m22() + 0.5) / 2));
		//drag->setPixmap(pixmap().scaledToWidth(tf.m11()));
		drag->setHotSpot(QPoint(32, 32));
		drag->setPixmap(pixmap().scaledToWidth(64));
		_dropPos = currentPos;
		dragStart();
		if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
			qDebug() << "dropPos:" << _dropPos;
			// Verify if item is also present on drop site
      if (currentPos == _dropPos) {
				setPos(pos());
			}
			setPos(_dropPos);
		}
		dragStop();
	}
}

void Item::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	//dragStop();
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	//dragStop();
}
