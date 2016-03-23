//! @file
#pragma once

#include <QGraphicsObject>

class PixmapItem : public QGraphicsObject {
	public:
	PixmapItem(const QString& filename, QGraphicsItem* parent = 0);
	virtual ~PixmapItem() = default;

	QPixmap pixmap() const;
	void setPixmap(const QPixmap& pixmap);

	QSizeF size() const;
	QRectF boundingRect() const override;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

	protected:
	QPixmap _pix;
};
