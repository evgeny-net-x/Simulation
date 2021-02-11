#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "cell.h"

#define TIME_SLICE 100 // ms

class Farm: public QWidget
{
	Q_OBJECT

private:
	int m_time;
	int m_total;
	int m_timerID;

	Cell *m_cells[16];

	QPushButton *m_speed1x_button;
	QPushButton *m_speed2x_button;
	QPushButton *m_speed4x_button;
	QLabel *m_timeLabel;
	QLabel *m_totalLabel;
public:
	Farm(QWidget *parent = nullptr);

	void updateTotalLabel(void);

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
