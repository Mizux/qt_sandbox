//! @file

#include "graphics_view.hpp"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "text_item.hpp"

GraphicsView::GraphicsView(QWidget* parent)
  : QGraphicsView(parent)
  , _size(9, 9)
  , _tileSize(32, 32)
  , _cells()
  , _items() {
	/*
	setStyleSheet(
	        "QGraphicsView {"
	        "background-color: transparent;"
	        "}");
	*/

	_setupWidget();
}

QSize
GraphicsView::sizeHint() const {
	return QSize(_size.width() * _tileSize.width(),
	             _size.height() * _tileSize.height());
}

int
GraphicsView::heightForWidth(int w) const {
	return w * _size.height() / _size.width();
}

void
GraphicsView::resizeEvent(QResizeEvent* event) {
	fitInView(sceneRect(), Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(event);
}

PkMItem*
GraphicsView::onSpawn() {
	PkMItem* pkm1 = new PkMItem();
	pkm1->setPos(qrand() % _size.width(), qrand() % _size.height());
	scene()->addItem(pkm1);
	_items.insert(pkm1);

	return pkm1;
}

void
GraphicsView::onMove() {
	QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
	for (auto it : _items) {
		QPointF currentPos = it->pos();

		QPropertyAnimation* animation = new QPropertyAnimation(this);
		animation->setTargetObject(it);
		animation->setPropertyName("pos");
		animation->setDuration(250); // ms
		animation->setStartValue(currentPos);
		// move between [-1, 0, 1]
		qreal dx = (qrand() % 3) - 1;
		qreal dy = (qrand() % 3) - 1;

		if (currentPos.x() + dx < 0 || currentPos.x() + dx > _size.width() - 1) {
			dx = 0;
		}

		if (currentPos.y() + dy < 0 || currentPos.y() + dy > _size.height() - 1) {
			dy = 0;
		}
		animation->setEndValue(currentPos + QPointF(dx, dy));

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

	PkMItem* item = *_items.begin();
	_items.remove(item);

	QPropertyAnimation* animation = new QPropertyAnimation(this);
	animation->setTargetObject(item);
	animation->setDuration(250);
	animation->setPropertyName("rotation");
	animation->setStartValue(0);
	animation->setEndValue(360);

	// item automatically unregister from the scene on destroy.
	connect(
	  animation, &QPropertyAnimation::finished, item, &PixmapItem::deleteLater);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void
GraphicsView::_createBoard() {
	_items.clear();
	_cells.clear();
	scene()->clear();

	qsrand(8); // init rand seed
	for (int j = 0; j < _size.width(); ++j) {
		for (int i = 0; i < _size.height(); ++i) {
			CellItem* cell = new CellItem();
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
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	_createBoard();

	onSpawn();
	onSpawn();
	onSpawn();

	//	{
	//		TextItem* text = new TextItem("1234xgf");
	//		text->setPos(2, 2);
	//		text->setZValue(2);
	//		text->setFlag(QGraphicsItem::ItemIsMovable);
	//		scene()->addItem(text);
	//	}
}
