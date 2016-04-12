//! @file
#pragma once

#include <QGraphicsObject>

class Item : public QGraphicsObject {
	public:
	Item(QGraphicsItem* parent = 0);
	virtual ~Item()            = default;

	QRectF boundingRect() const override;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

	QPixmap pixmap();

	void dragStart();
	void dragStop();

	protected:
	bool _dragStart;
};
