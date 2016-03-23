//! @file

#include "pkm_item.hpp"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

#include <QDrag>
#include <QWidget>
#include <QMimeData>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

PkMItem::PkMItem(QGraphicsItem* parent)
  : PixmapItem(":/img/item.png", parent) {
	setZValue(1);
	setFlag(QGraphicsItem::ItemIsMovable);

	setCursor(Qt::OpenHandCursor);
	setAcceptedMouseButtons(Qt::LeftButton);
}

void
PkMItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	setCursor(Qt::ClosedHandCursor);
	setOpacity(0.5);
	setScale(1.5);
	QGraphicsItem::mousePressEvent(event);
}

void
PkMItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  //QGraphicsItem::mouseMoveEvent(event);

  if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
      .length() >= QApplication::startDragDistance()) {
    QDrag* drag     = new QDrag(event->widget());
    QMimeData* data = new QMimeData;
    data->setData("application/x-items", QByteArray());
    drag->setMimeData(data);

    // Since One cell is 1 unit (cf fitInView)
    QTransform tf = scene()->views().first()->transform();
    drag->setPixmap(_pix.scaledToWidth(tf.m11()));
    drag->setHotSpot(QPoint(tf.m11()/2, tf.m22()/2));
    drag->exec();

    // Once drag performed, item returns to its previous "style"
    setCursor(Qt::OpenHandCursor);
    setOpacity(1.0);
    setScale(1.0);
    setPos(std::round(pos().x()), std::round(pos().y()));
    scene()->update();
  }

}

void
PkMItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
	setCursor(Qt::OpenHandCursor);
	setOpacity(1.0);
	setScale(1.0);
	setPos(std::round(pos().x()), std::round(pos().y()));
	QGraphicsItem::mouseReleaseEvent(event);
}
