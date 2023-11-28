#pragma once
#include <QWidget>
#include <QPainter>

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    BoardWidget(QWidget* parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent* event) override;
private:
    const int numRows = 80;
    const int numCols = 80;
    std::vector<std::vector<int>> drawingMatrix;
};

