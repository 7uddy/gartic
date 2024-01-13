#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent)
{
	setFixedSize(Width * 10, Height * 10);
}

const int BoardWidget::GetHeight()
{
	return Height;
}

const int BoardWidget::GetWidth()
{
	return Width;
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

void BoardWidget::SetBoard(const std::unordered_set<std::pair<int, int>, HashFunction>& newCoordinates)
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
	const int matrixWidth = Width * 10;
	const int matrixHeight = Height * 10;
	int startX = (width() - matrixWidth) / 2;
	int startY = (height() - matrixHeight) / 2;
	paint.setPen(QPen(Qt::black, 0));
	paint.setBrush(Qt::black);
	for (const auto& point:pointsCoordinates)
	{
		QRect rectangle(startX + point.second * pixelSize, startY + point.first * pixelSize, pixelSize, pixelSize);
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
