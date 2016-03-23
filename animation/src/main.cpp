#include <QApplication>

#include "main_window.hpp"

int
main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	app.setOrganizationName("Mizux");
	app.setApplicationName("Animation");

	// MainWindow main;
	MainWindow main;
	main.show();
	return app.exec();
}
