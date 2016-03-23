//! @file

#include "main_window.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
  : QWidget(parent) {
	setStyleSheet(
	  "MainWindow {"
	  "background-color: transparent;"
	  "}");
	_setupWidget();
}

MainWindow::~MainWindow() {}

void
MainWindow::_setupWidget() {
	setObjectName("Main");
	setLayout(new QVBoxLayout(this));

	_view = new GraphicsView(this);
	layout()->addWidget(_view);

	{
		QHBoxLayout* box = new QHBoxLayout();

		QPushButton* _spawnButton = new QPushButton("Spawn", this);
		_spawnButton->setFixedSize(_spawnButton->sizeHint());
		box->addWidget(_spawnButton);
		box->setAlignment(_spawnButton, Qt::AlignCenter);
		connect(_spawnButton, &QPushButton::clicked, _view, &GraphicsView::onSpawn);

		QPushButton* _moveButton = new QPushButton("Move", this);
		_moveButton->setFixedSize(_moveButton->sizeHint());
		box->addWidget(_moveButton);
		box->setAlignment(_moveButton, Qt::AlignCenter);
		connect(_moveButton, &QPushButton::clicked, _view, &GraphicsView::onMove);
		// wait for previous animation to finish (async)
		connect(_moveButton,
		        &QPushButton::clicked,
		        [=]() { _moveButton->setDisabled(true); });
		connect(_view,
		        &GraphicsView::moveFinished,
		        [=]() { _moveButton->setDisabled(false); });

		QPushButton* _deleteButton = new QPushButton("Delete", this);
		_deleteButton->setFixedSize(_deleteButton->sizeHint());
		box->addWidget(_deleteButton);
		box->setAlignment(_deleteButton, Qt::AlignCenter);
		connect(
		  _deleteButton, &QPushButton::clicked, _view, &GraphicsView::onDelete);

		layout()->addItem(box);
	}
}
