#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "cell.h"

class Farm: public QWidget
{
	Q_OBJECT

private:
	int m_time;
	int m_total;
	int m_timerID;

	Cell *m_cells[16];

	QLabel *m_timeLabel;
	QLabel *m_totalLabel;
	QPushButton *m_speed1x_button;
	QPushButton *m_speed2x_button;
	QPushButton *m_speed4x_button;
public:
	Farm(QWidget *parent = nullptr);

	void setTotal(int);

	void plant(Cell &);
	void harvest(Cell &);
	int getCellProfit(Cell &);

public slots:
	void handleCell(Cell &);
	void handle_speed1x_button(void);
	void handle_speed2x_button(void);
	void handle_speed4x_button(void);

protected slots:
	void timerEvent(QTimerEvent *);
};

#endif
