#include <QPainter>
#include <QApplication>
#include <QEventLoop>
#include "TreeWidgetDouble3.hpp"

TreeWidgetDouble3::TreeWidgetDouble3(std::shared_ptr<Node<double,3>> rootNode, QWidget* parent)
    : QWidget(parent), root(rootNode) {
	connect(this, &TreeWidgetDouble3::renderTree, this, &TreeWidgetDouble3::handleRenderTree);
    }

void TreeWidgetDouble3::setRoot(std::shared_ptr<Node<double,3>> rootNode) {
    root = rootNode;
}

void TreeWidgetDouble3::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawTree(painter, root, width() / 2, 30, width() / 4, 50);
}

void TreeWidgetDouble3::drawTree(QPainter& painter, std::shared_ptr<Node<double,3>> node, int x, int y, int hSpacing, int vSpacing) {
    if (!node) return;
    
    painter.drawEllipse(x - 15, y - 15, 30, 30);
    painter.drawText(x - 10, y + 5, QString::number(node->get_value()));

    int numChildren = node->get_children().size();
    int newX, newY;
    for (int i = 0; i < numChildren; ++i) {
        newX = x - (numChildren - 1) * hSpacing / 2 + i * hSpacing;
        newY = y + vSpacing;
        painter.drawLine(x, y + 15, newX, newY - 15);
        drawTree(painter, node->get_children()[i], newX, newY, hSpacing / 2, vSpacing);
    }
}

void TreeWidgetDouble3::handleRenderTree() {
    show();
    repaint();
}

