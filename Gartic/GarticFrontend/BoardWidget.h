#pragma once
#include <QWidget>
#include <QPainter>

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    BoardWidget(QWidget* parent = nullptr);
    const int GetNumRows();
    const int GetNumCols();
    ~BoardWidget();
signals:
    void MouseDraw(QMouseEvent* event);
protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
private:
    const int numRows = 50;
    const int numCols = 80;
public:
    std::vector<std::vector<int>> drawingMatrix;
};


