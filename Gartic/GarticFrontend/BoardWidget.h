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
    static const size_t numRows{ 50 };
    static const size_t numCols{ 90 };
    static const size_t kSize{ numRows*numCols};
public:
    std::array<uint16_t, kSize> drawingMatrix;
};


