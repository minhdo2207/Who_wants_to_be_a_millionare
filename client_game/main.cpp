#include "mymainwindow.h"
#include "client.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();

    Client* client = new Client();
    if(client->Connect()){
        w.client = client;
    } else {
        //QMessageBox::information(this, "Not   ification", "Socket Connection Error!");
        return 0;
    }

    return a.exec();
}
