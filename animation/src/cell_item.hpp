//! @file
#pragma once

#include "pixmap_item.hpp"

class CellItem : public PixmapItem {
	public:
	CellItem(QGraphicsItem* parent = 0);
	virtual ~CellItem() = default;

	void paint(QPainter* painter,
	           const QStyleOptionGraphicsItem* option,
	           QWidget* widget = 0) override;

	protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
	void dropEvent(QGraphicsSceneDragDropEvent* event) override;

	bool _dragOver;
};
