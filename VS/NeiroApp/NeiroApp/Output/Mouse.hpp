#pragma once
#define OEMRESOURCE
#include <Windows.h>
#include <QCursor>
#include <QObject>

namespace Output_module
{
	class Mouse : QObject
	{
		Q_OBJECT;
	public:
		Mouse();
		~Mouse();

	public slots:
		void getCoords(); //Return QPoint structure with current coords of cursor. This coords depends on resolution of screen
		void setCoords(double x, double y); //Move cursor to x y coordinate
		void setCoords(QPoint point); //Move cursor to QPoint coordinate
		void setCoords(QPoint point, int time); //Move cursor to QPoint coordinate in time (ms)
		void setCoords(double x, double y, int time); //Move cursor to x y coordinate in time (ms)
		void shiftCoords(double x, double y); //Shift cursor by x y
		void shiftCoords(double x, double y, int time); // Shift cursor by x y in time (ms)
		void pressLeftClick(); //Press left button of the mouse
		void releaseLeftClick(); //Release left button of the mouse
		void pressRightClick(); //Press right button of the mouse
		void releaseRightClick(); //Release right button of the mouse
		void changeCursor(); //Change system cursor
		void restoreCursor(); //Restore system cursor

	private slots:
		void setCurrentCoords(QPoint);

	signals:
		void newCoords(QPoint currentCoords);
		void leftClicked();
		void leftReleased();
		void rightClicked();
		void rightReleased();

	private:
		QPoint currentCoords;
		QCursor cursor;
		HANDLE LoadNoShareCursor(UINT ocr_id);
		HANDLE hHand;
		HANDLE hArrow;
		bool isCursorChanged;
	};
}
