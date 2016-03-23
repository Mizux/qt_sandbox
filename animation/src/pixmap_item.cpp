//! @file

#include "pixmap_item.hpp"

#include <QPainter>

PixmapItem::PixmapItem(const QString& filename, QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , _pix() {
	_pix = QPixmap(filename);
	setTransformOriginPoint(0.5, 0.5);
}

QPixmap
PixmapItem::pixmap() const {
	return _pix;
}

void
PixmapItem::setPixmap(const QPixmap& pixmap) {
	_pix = pixmap;
}

QSizeF
PixmapItem::size() const {
	return QSizeF(1.0, 1.0);
}

QRectF
PixmapItem::boundingRect() const {
	return QRectF(QPointF(0, 0), QPointF(1, 1));
}

void
PixmapItem::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem*,
                  QWidget*) {
	painter->setRenderHint(QPainter::Antialiasing);
	painter->scale(1.0 / _pix.width(), 1.0 / _pix.height());
	painter->drawPixmap(0, 0, _pix);
}
