1. 初始化 QGIS 应用程序和 Qt 环境
    初始化 QApplication：
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 初始化 QGIS 应用程序
    QgsApplication::setPrefixPath("/path/to/qgis/installation", true);
    QgsApplication::initQgis();
    
    // 其他初始化操作...
    
    // 执行事件循环
    return a.exec();
}

