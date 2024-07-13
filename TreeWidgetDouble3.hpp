#ifndef TREEWIDGET_DOUBLE3_H
#define TREEWIDGET_DOUBLE3_H

#include <QWidget>
#include "Node.hpp"

class TreeWidgetDouble3 : public QWidget {
    Q_OBJECT

public:
    explicit TreeWidgetDouble3(std::shared_ptr<Node<double,3>> rootNode, QWidget* parent = nullptr);    
    ~TreeWidgetDouble3(); // Destructor
    void setRoot(std::shared_ptr<Node<double,3>> rootNode);
    
signals:
    void renderTree(); // Signal to trigger rendering

public slots:
    void handleRenderTree(); // Slot to handle rendering

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Node<double,3>> root;
    QMetaObject::Connection renderConnection; // Store the connection
    static void drawTree(QPainter& painter, std::shared_ptr<Node<double,3>> node, int x, int y, int hSpacing, int vSpacing);
};

#endif // TREEWIDGET_DOUBLE3_H
