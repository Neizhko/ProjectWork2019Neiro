#include "Output/Mouse.hpp"
#include <cmath>
#include <QEventLoop>
#include <QTimer>
#include <qdebug.h>

using namespace Output_module;

Mouse::Mouse() :
	isCursorChanged(false)
{
	QObject::connect(this, SIGNAL(newCoords(QPoint)), this, SLOT(setCurrentCoords(QPoint)));
}


Mouse::~Mouse()
{
	QObject::disconnect(this, SIGNAL(newCoords(QPoint)), this, SLOT(setCurrentCoords(QPoint)));
}

void Mouse::getCoords()
{
	emit newCoords(QCursor::pos());
}

void Mouse::setCoords(double x, double y)
{
	cursor.setPos(x, y);
}

void Mouse::setCoords(QPoint point)
{
	cursor.setPos(point);
}

void Mouse::setCoords(QPoint point, int time)
{
	setCoords(point.x(), point.y(), time);
}

void Mouse::setCoords(double x, double y, int time)
{
	if (time <= 0)
	{
		setCoords(x, y);
		return;
	}
	getCoords();
	double dx = abs(x - currentCoords.x());
	double dy = abs(y - currentCoords.y());
	double curX = currentCoords.x();
	double curY = currentCoords.y();
	short int xMult = 1;
	short int yMult = 1;
	if (curX > x)
	{
		xMult = -1;
	}
	if (curY > y)
	{
		yMult = -1;
	}
	QEventLoop loop;
	double sleepTime = time / 100;
	for (int i = 0; i < 100; i++)
	{
		curX += dx / 100 * xMult;
		curY += dy / 100 * yMult;
		cursor.setPos(curX, curY);
		QTimer::singleShot(sleepTime, &loop, SLOT(quit()));
		loop.exec();
	}
	setCoords(x, y);
}

void Mouse::shiftCoords(double x, double y)
{
	getCoords();
	cursor.setPos(currentCoords.x() + x, currentCoords.y() + y);
}

void Mouse::shiftCoords(double x, double y, int time)
{
	getCoords();
	double xNew = currentCoords.x() + x;
	double yNew = currentCoords.y() + y;
	setCoords(xNew, yNew, time);
}

void Mouse::pressLeftClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	emit leftClicked();
}

void Mouse::releaseLeftClick()
{
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	emit leftReleased();
}

void Mouse::pressRightClick()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	emit rightClicked();
}

void Mouse::releaseRightClick()
{
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	emit rightReleased();
}

void Mouse::changeCursor()
{
	if (isCursorChanged)
	{
		return;
	}
	isCursorChanged = true;
	hHand = LoadCursorFromFile(TEXT("GUI/Images/Cross.cur"));
	hArrow = LoadNoShareCursor(OCR_NORMAL);
	SetSystemCursor((HCURSOR)hHand, OCR_NORMAL);
}

void Mouse::restoreCursor()
{
	isCursorChanged = false;
	SetSystemCursor((HCURSOR)hArrow, OCR_NORMAL);
}

void Mouse::setCurrentCoords(QPoint coords)
{
	this->currentCoords = coords;
}

HANDLE Mouse::LoadNoShareCursor(UINT ocr_id)
{
	HANDLE tmp = LoadImage(0, MAKEINTRESOURCE(ocr_id), IMAGE_CURSOR, 0, 0, LR_SHARED);
	if (!tmp)
	{
		return 0;
	}
	return CopyImage(tmp, IMAGE_CURSOR, 0, 0, 0);
}
