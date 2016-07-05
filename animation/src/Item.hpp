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
	void setDropPos(const QPointF& pos);

	protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

	void dragStart();
	void dragStop();

  private:
	bool _dragStart;
	QPointF _dropPos;
};
