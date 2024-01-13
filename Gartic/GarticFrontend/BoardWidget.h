#pragma once
#include <QWidget>
#include <QPainter>
#include <nlohmann/json.hpp>

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(QWidget* parent = nullptr);
    const int GetNumRows();
    const int GetNumCols();
    nlohmann::json GetBoard();
    void SetBoard(std::vector<std::pair<int, int>>);
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
public:
    std::vector<std::pair<int,int>> pointsCoordinates;
};


