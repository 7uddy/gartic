#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent)
{
	setFixedSize(numCols * 10, numRows * 10);
}

const int BoardWidget::GetNumRows()
{
	return numRows;
}

const int BoardWidget::GetNumCols()
{
	return numCols;
}

nlohmann::json BoardWidget::GetBoard()
{
	nlohmann::json coordinatesToBeSent;
	for (const auto& coordinate : pointsCoordinates)
	{
		coordinatesToBeSent.push_back({ {"x", coordinate.first}, {"y", coordinate.second} });
	}
	return coordinatesToBeSent;
}

void BoardWidget::SetBoard(std::vector<std::pair<int, int>> newCoordinates)
{
	pointsCoordinates = newCoordinates;
	update();
}

BoardWidget::~BoardWidget()
{
	/*empty*/
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter paint(this);
	paint.fillRect(rect(), Qt::white);
	paint.setRenderHint(QPainter::Antialiasing, true);
	const int pixelSize = 10;
	const int matrixWidth = numCols * 10;
	const int matrixHeight = numRows * 10;
	int startX = (width() - matrixWidth) / 2;
	int startY = (height() - matrixHeight) / 2;
	paint.setPen(QPen(Qt::black, 0));
	paint.setBrush(Qt::black);
	for (int index = 0; index < pointsCoordinates.size(); index++)
	{
		QRect rectangle(startX + pointsCoordinates[index].second * pixelSize, startY + pointsCoordinates[index].first * pixelSize, pixelSize, pixelSize);
		paint.drawRect(rectangle);
	}
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	emit MouseDraw(event);
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	emit MouseDraw(event);
}
