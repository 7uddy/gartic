#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), drawingMatrix(numRows, std::vector<int>(numCols, 0))
{
	setFixedSize(numCols * 10, numRows * 10);
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter paint(this);
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
			if (drawingMatrix[index][jndex] == 0)
			{
				paint.setPen(QPen(Qt::white, 0));
				paint.setBrush(Qt::white);
				paint.drawRect(rectangle);
			}
			else if (drawingMatrix[index][jndex] == 1)
			{
				paint.setPen(QPen(Qt::black, 0));
				paint.setBrush(Qt::black);
				paint.drawRect(rectangle);
			}
		}
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	emit mouseDraw(event);
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	emit mouseDraw(event);
}
