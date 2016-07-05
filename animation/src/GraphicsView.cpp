//! @file

#include "GraphicsView.hpp"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

GraphicsView::GraphicsView(QWidget* parent)
  : QGraphicsView(parent)
  , _size(9, 9)
  , _minTileSize(32, 32)
  , _cells()
  , _items() {
	_setupWidget();
}

QSize
GraphicsView::sizeHint() const {
	return QSize(_size.width() * _minTileSize.width(),
	             _size.height() * _minTileSize.height());
}

int
GraphicsView::heightForWidth(int w) const {
	return w * _size.height() / _size.width();
}

Item*
GraphicsView::onSpawn() {
	Item* item = new Item();
	item->setPos(qrand() % _size.width(), qrand() % _size.height());
	scene()->addItem(item);
	_items.insert(item);
	return item;
}

void
GraphicsView::onMove() {
	QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
	for (auto it : _items) {
		QPointF currentPos = it->pos();
		QPointF endPos = currentPos + QPointF((qrand() % 5) - 2, (qrand() % 5) - 2);
		// Clamp to stay in grid if needed.
		endPos.setX(qMax(qMin(endPos.x(), qreal(_size.width() - 1)), 0.));
		endPos.setY(qMax(qMin(endPos.y(), qreal(_size.height() - 1)), 0.));

		QPropertyAnimation* animation = new QPropertyAnimation(this);
		animation->setTargetObject(it);
		animation->setPropertyName("pos");
		animation->setDuration(250); // ms
		animation->setStartValue(currentPos);
		animation->setEndValue(endPos);

		group->addAnimation(animation);
	}

	connect(group,
	        &QParallelAnimationGroup::finished,
	        this,
	        &GraphicsView::moveFinished);
	group->start(QAbstractAnimation::DeleteWhenStopped);
}

void
GraphicsView::onDelete() {
	if (_items.empty()) return;

	Item* item = *_items.begin();
	_items.remove(item);

	QPropertyAnimation* animation = new QPropertyAnimation(this);
	animation->setTargetObject(item);
	animation->setDuration(250);
	animation->setPropertyName("rotation");
	animation->setStartValue(0);
	animation->setEndValue(360);

	// item automatically unregister from the scene on destroy.
	connect(animation, &QPropertyAnimation::finished, item, &Item::deleteLater);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void
GraphicsView::resizeEvent(QResizeEvent* event) {
	fitInView(sceneRect(), Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(event);
}

void
GraphicsView::_createBoard() {
	_items.clear();
	_cells.clear();
	scene()->clear();

	qsrand(8); // init rand seed
	for (int j = 0; j < _size.width(); ++j) {
		for (int i = 0; i < _size.height(); ++i) {
			Tile* cell = new Tile();
			cell->setPos(i, j);
			if (qrand() % 8 == 0) { // 1/8 of cells should not accept drop
				cell->setAcceptDrops(false);
			}
			scene()->addItem(cell);
			_cells.insert(cell);
		}
	}
	scene()->setSceneRect(0, 0, _size.width(), _size.height());
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void
GraphicsView::_setupWidget() {
	setObjectName("View");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QSizePolicy policy;
	policy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);

	setScene(new QGraphicsScene(this));
	scene()->setBackgroundBrush(Qt::green);
	setCacheMode(QGraphicsView::CacheBackground);
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	_createBoard();

	onSpawn();
	onSpawn();
	onSpawn();
}
