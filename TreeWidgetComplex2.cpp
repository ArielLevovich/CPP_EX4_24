#include <QPainter>
#include <QApplication>
#include <QEventLoop>
#include "TreeWidgetComplex2.hpp"

TreeWidgetComplex2::TreeWidgetComplex2(std::shared_ptr<Node<Complex,2>> rootNode, QWidget* parent)
    : QWidget(parent), root(rootNode) {
	    renderConnection = connect(this, &TreeWidgetComplex2::renderTree, this, &TreeWidgetComplex2::handleRenderTree);
    }

TreeWidgetComplex2::~TreeWidgetComplex2() {
    disconnect(renderConnection); // Explicitly disconnect the signal
}
void TreeWidgetComplex2::setRoot(std::shared_ptr<Node<Complex,2>> rootNode) {
    root = rootNode;
}

void TreeWidgetComplex2::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawTree(painter, root, width() / 2, 30, width() / 4, 50);
}

void TreeWidgetComplex2::drawTree(QPainter& painter, std::shared_ptr<Node<Complex,2>> node, int x, int y, int hSpacing, int vSpacing) {
    if (!node) return;
    
    painter.drawEllipse(x - 20, y - 20, 40, 40);
    Complex c = node->get_value();       
    
    painter.drawText(x - 10, y + 5, QString(c.toString().c_str()));

    int numChildren = node->get_children().size();
    int newX, newY;
    for (int i = 0; i < numChildren; ++i) {
        newX = x - (numChildren - 1) * hSpacing / 2 + i * hSpacing;
        newY = y + vSpacing;
        painter.drawLine(x, y + 20, newX, newY - 20);
        drawTree(painter, node->get_children()[i], newX, newY, hSpacing / 2, vSpacing);
    }
}

void TreeWidgetComplex2::handleRenderTree() {
    show();
    repaint();
}

