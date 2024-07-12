#ifndef TREEWIDGET_COMPLEX2_H
#define TREEWIDGET_COMPLEX2_H

#include <QWidget>
#include "Node.hpp"
#include "Complex.hpp"

class TreeWidgetComplex2 : public QWidget {
    Q_OBJECT

public:
    explicit TreeWidgetComplex2(std::shared_ptr<Node<Complex,2>> rootNode, QWidget* parent = nullptr);    

    void setRoot(std::shared_ptr<Node<Complex,2>> rootNode);
    
signals:
    void renderTree(); // Signal to trigger rendering

public slots:
    void handleRenderTree(); // Slot to handle rendering

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::shared_ptr<Node<Complex,2>> root;

    void drawTree(QPainter& painter, std::shared_ptr<Node<Complex,2>> node, int x, int y, int hSpacing, int vSpacing);
};

#endif // TREEWIDGET_COMPLEX2_H
