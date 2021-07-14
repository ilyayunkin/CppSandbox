#include <QApplication>
#include <QQmlEngine>
#include <QQuickItem>
#include <QDebug>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QLineEdit le;
    le.show();

    QQmlEngine engine;
    QQmlComponent component(&engine,
            QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *ui = component.create();

    QObject::connect(ui, SIGNAL(sendMessage(QString)),
                     &le, SLOT(setText(QString)));

    return app.exec();
}
