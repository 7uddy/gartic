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

std::string BoardWidget::GetBoard()
{
	std::vector<nlohmann::json> coordinatesToBeSent;
	for (const auto& coordinate : pointsCoordinates)
	{
		nlohmann::json point;
		point["x"] = coordinate.first;
		point["y"] = coordinate.second;
		coordinatesToBeSent.emplace_back(point);
	}
	std::string combinedJson;
	for (const auto& json : coordinatesToBeSent)
	{
		combinedJson += json.dump();
	}
	return combinedJson;
}

void BoardWidget::SetBoard(const std::string& boardText)
{
	for (int index = 0; index < numRows; index++)
	{
		/*drawingMatrix[index * numCols + jndex] = boardText[index * numCols + jndex] - '0';*/
	}
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
