#pragma once
#include <QWidget>
#include <QPainter>
#include <nlohmann/json.hpp>
#include <unordered_set>

struct HashFunction
{
    size_t operator()(const std::pair<int,
        int>& x) const
    {
        return x.first ^ x.second;
    }
};

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(QWidget* parent = nullptr);
    const int GetNumRows();
    const int GetNumCols();
    nlohmann::json GetBoard();
    void SetBoard(std::unordered_set<std::pair<int, int>, HashFunction>);
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
    std::unordered_set<std::pair<int,int>, HashFunction> pointsCoordinates;
};


