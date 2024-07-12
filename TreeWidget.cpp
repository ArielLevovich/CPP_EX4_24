#include <QPainter>
#include <QApplication>
#include <QEventLoop>
#include "TreeWidget.hpp"

TreeWidget::TreeWidget(std::shared_ptr<Node<double,2>> rootNode, QWidget* parent)
    : QWidget(parent), root(rootNode) {
	connect(this, &TreeWidget::renderTree, this, &TreeWidget::handleRenderTree);
    }

void TreeWidget::setRoot(std::shared_ptr<Node<double,2>> rootNode) {
    root = rootNode;
}

void TreeWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawTree(painter, root, width() / 2, 30, width() / 4, 50);
}

void TreeWidget::drawTree(QPainter& painter, std::shared_ptr<Node<double,2>> node, int x, int y, int hSpacing, int vSpacing) {
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

void TreeWidget::handleRenderTree() {
    show();
    repaint();
}

