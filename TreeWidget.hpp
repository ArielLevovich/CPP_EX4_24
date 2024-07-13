#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include "Node.hpp"

class TreeWidget : public QWidget {
    Q_OBJECT

public:
    explicit TreeWidget(std::shared_ptr<Node<double,2>> rootNode, QWidget* parent = nullptr);    

    ~TreeWidget(); // Destructor

    void setRoot(std::shared_ptr<Node<double,2>> rootNode);
    
signals:
    void renderTree(); // Signal to trigger rendering

public slots:
    void handleRenderTree(); // Slot to handle rendering

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Node<double,2>> root;
    QMetaObject::Connection renderConnection; // Store the connection
    static void drawTree(QPainter& painter, std::shared_ptr<Node<double,2>> node, int x, int y, int hSpacing, int vSpacing);
};

#endif // TREEWIDGET_H
