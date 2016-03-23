//! @file
#pragma once

#include "pixmap_item.hpp"

class PkMItem : public PixmapItem {
	public:
	PkMItem(QGraphicsItem* parent = 0);
	virtual ~PkMItem() = default;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
