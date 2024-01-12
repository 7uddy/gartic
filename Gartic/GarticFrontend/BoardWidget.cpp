#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), drawingMatrix{}
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

std::string BoardWidget::GetDrawingMatrix()
{
	std::string result;
	for (int index = 0; index < numRows; index++)
		for (int jndex = 0; jndex < numCols; jndex++)
		     result += std::to_string(drawingMatrix[index * numCols + jndex]);
	return result;
}

void BoardWidget::SetBoard(const std::string& boardText)
{
	for (int index = 0; index < numRows; index++)
		for (int jndex = 0; jndex < numCols; jndex++)
		{
			drawingMatrix[index * numCols + jndex] = boardText[index * numCols + jndex] - '0';
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
	for (int index = 0; index < numRows; index++)
		for (int jndex = 0; jndex < numCols; jndex++)
		{
			QRect rectangle(startX + jndex * pixelSize, startY + index * pixelSize, pixelSize, pixelSize);
			if (drawingMatrix[index * numCols + jndex] == 1)
			{
				paint.setPen(QPen(Qt::black, 0));
				paint.setBrush(Qt::black);
				paint.drawRect(rectangle);
			}
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
