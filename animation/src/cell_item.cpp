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
  if (_dragOver) {
    painter->setBrush(Qt::yellow);
    painter->drawRoundedRect(0, 0, _pix.width(), _pix.height(), 25, 25, Qt::RelativeSize);
  }
}

void
CellItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
  // qDebug() << "drag enter...";
  if (event->mimeData()->hasFormat("application/x-items")) {
    event->accept();
    _dragOver = true;
    update();
  } else {
    event->ignore();
  }
}

void
CellItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event) {
  //qDebug() << "drag leave...";
  _dragOver = false;
  update();
  event->accept();
}

void
CellItem::dropEvent(QGraphicsSceneDragDropEvent* event) {
  //qDebug() << "drag drop...";
  _dragOver = false;
  update();
  event->accept();
}
