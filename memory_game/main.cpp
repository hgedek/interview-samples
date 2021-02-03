#include "cellmodel.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

constexpr auto IMAGE_COUNT = 50;
constexpr auto MAX_IMAGE_COUNT = 50;

int main(int argc, char *argv[]) {

    static_assert(IMAGE_COUNT <= MAX_IMAGE_COUNT,
                  "project doesn't have enough images");

    static_assert(IMAGE_COUNT % 2 == 0, "IMAGE_COUNT should pow of 2");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    CellModel cellModel;
    cellModel.initialize(IMAGE_COUNT);
    cellModel.shuffle();

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("cellModel", &cellModel);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    
    return app.exec();
}
