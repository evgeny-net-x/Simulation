#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QPalette>

enum CellState
{
	CELLSTATE_EMPTY,
	CELLSTATE_PLANTED,
	CELLSTATE_GREEN,
	CELLSTATE_IMMATURE,
	CELLSTATE_MATURE,
	CELLSTATE_OVERGROW
};

enum
{
	PROGRESS_PLANTED = 0,
	PROGRESS_GREEN = 20,
	PROGRESS_IMMATURE = 80,
	PROGRESS_MATURE = 100,
	PROGRESS_OVERGROW = 110
};

class Cell: public QPushButton
{
	Q_OBJECT

public:
	int progress;
	CellState state;

public:
	Cell(QWidget *parent = nullptr);
	void plant(void);
	void harvest(void);
	void nextStep(void);

private:
	void update(void);

signals:
	void signalFromCell(Cell &);

private slots:
	void handleButton(void);
};

#endif // CELL_H
