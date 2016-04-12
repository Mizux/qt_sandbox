//! @file
#pragma once

#include <QGraphicsView>
#include <QSet>
#include "cell_item.hpp"
#include "pkm_item.hpp"

class GraphicsView : public QGraphicsView {
	Q_OBJECT

	public:
	GraphicsView(QWidget* parent = 0);
	virtual ~GraphicsView() = default;

	QSize sizeHint() const override;
	int heightForWidth(int w) const override;

	signals:
	void moveFinished();

	public slots:
	PkMItem* onSpawn();
	void onMove();
	void onDelete();

	protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	void _createBoard();
	void _setupWidget();

	QSize _size;
	QSize _tileSize;
	QSet<PkMItem*> _items;
	QSet<CellItem*> _cells;
};
