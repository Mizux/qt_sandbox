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

	signals:
	void moveFinished();

	public slots:
	Item* onSpawn();
	void onMove();
	void onDelete();

	protected:
	virtual void resizeEvent(QResizeEvent* event) override;

	void _createBoard();
	void _setupWidget();

	QSize _size;
	QSize _minTileSize;
	QSet<Item*> _items;
	QSet<Tile*> _cells;
};
