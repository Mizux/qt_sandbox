//! @file
#pragma once

#include "Item.hpp"
#include "Tile.hpp"
#include <QGraphicsView>
#include <QSet>

class GraphicsView : public QGraphicsView {
	Q_OBJECT

	public:
	GraphicsView(QWidget* parent = 0);
	virtual ~GraphicsView()      = default;

	QSize sizeHint() const override;
	int heightForWidth(int w) const override;

	void setDropPos(const QPointF& pos);

	signals:
	void moveFinished();

	public slots:
	Item* onSpawn();
	void onMove();
	void onDelete();

	protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	//! @brief Update when clic on item.
	void mousePressEvent(QMouseEvent* event) override;
	//! @brief Update when clic is released on tile.
	void mouseReleaseEvent(QMouseEvent* event) override;

	void _createBoard();
	void _setupWidget();

	QSize _size;
	QSize _minTileSize;
	QSet<Item*> _items;
	QSet<Tile*> _cells;

	QPointF _dropPos;
};
