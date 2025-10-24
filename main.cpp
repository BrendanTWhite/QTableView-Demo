#include <QApplication>
#include "contactmanager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ContactManager window;
    window.show();
    return app.exec();
}
