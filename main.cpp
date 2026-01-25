#include <QApplication>
#include "contactwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ContactWindow window;
    window.show();
    return app.exec();
}
