//! @file
#pragma once

#include <QWidget>
#include <QPushButton>
#include "graphics_view.hpp"

class MainWindow : public QWidget {
	Q_OBJECT

	public:
	MainWindow(QWidget* parent = 0);
	virtual ~MainWindow();
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;

	private:
	GraphicsView* _view;

	void _setupWidget();
};
