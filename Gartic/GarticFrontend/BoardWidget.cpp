#include "BoardWidget.h"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), drawingMatrix(numRows, std::vector<int>(numCols, 0))
{

}

void BoardWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter paint(this);
	paint.setRenderHint(QPainter::Antialiasing, true);
	const int matrixWidth = numCols * 10;
	const int matrixHeight = numRows * 10;
	int startX = (width() - matrixWidth) / 2;
	int startY = (height() - matrixHeight) / 2;
	for (int index = 0; index < numRows; index++)
		for (int jndex = 0; jndex < numCols; jndex++)
		{
			QRect rectangle(startX + jndex * 10, startY + index * 10, 10, 10);
			if (drawingMatrix[index][jndex] == 0)
			{
				paint.setPen(QPen(Qt::white, 0));
				paint.setBrush(Qt::white);
				paint.drawRect(rectangle);
			}
		}
}