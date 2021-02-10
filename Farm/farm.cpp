#include "farm.h"

Farm::Farm(QWidget *parent): QWidget(parent)
{
	setWindowTitle("Farm");
	resize(720, 620);

	m_time = 0;
	m_total = 100;
	m_timerID = startTimer(100); // ms

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QGridLayout *cellLayout = new QGridLayout(this);
	QHBoxLayout *textLayout = new QHBoxLayout(this);

	mainLayout->addLayout(cellLayout);
	mainLayout->addLayout(textLayout);

	// cellLayout
	for (int i = 0; i < 16; i++) {
		m_cells[i] = new Cell(this);

		cellLayout->addWidget(m_cells[i], i/4, i%4);
		connect(m_cells[i], &Cell::signalFromCell, this, &Farm::handleCell);
	}

	// textLayout
	QFont font;
	font.setPointSize(20);

	m_timeLabel = new QLabel(this);
	m_totalLabel = new QLabel(this);
	this->setTotal(m_total);

	m_speed1x_button = new QPushButton("=>1x", this);
	m_speed2x_button = new QPushButton("=>2x", this);
	m_speed4x_button = new QPushButton("=>4x", this);

	m_timeLabel->setFont(font);
	m_totalLabel->setFont(font);
	m_speed1x_button->setFont(font);
	m_speed2x_button->setFont(font);
	m_speed4x_button->setFont(font);

	textLayout->addWidget(m_timeLabel);
	textLayout->addWidget(m_totalLabel);
	textLayout->addWidget(m_speed1x_button);
	textLayout->addWidget(m_speed2x_button);
	textLayout->addWidget(m_speed4x_button);

	//
	connect(m_speed1x_button, &QPushButton::released, this, &Farm::handle_speed1x_button);
	connect(m_speed2x_button, &QPushButton::released, this, &Farm::handle_speed2x_button);
	connect(m_speed4x_button, &QPushButton::released, this, &Farm::handle_speed4x_button);
}

void Farm::setTotal(int total)
{
	m_total = total;
	m_totalLabel->setText("Total: " + QString::number(total));
}

void Farm::plant(Cell &cell)
{
	const int plantCost = 2;
	if (m_total-plantCost < 0)
		return;

	this->setTotal(m_total - plantCost);
	cell.plant();
}

void Farm::harvest(Cell &cell)
{
	int profit = this->getCellProfit(cell);
	if (m_total + profit < 0)
		return;

	this->setTotal(m_total + profit);
	cell.harvest();
}

int Farm::getCellProfit(Cell &cell)
{
	switch (cell.state) {
		case CELLSTATE_PLANTED:  return 0;
		case CELLSTATE_GREEN:    return 1;
		case CELLSTATE_IMMATURE: return 3;
		case CELLSTATE_MATURE:   return 5;
		case CELLSTATE_OVERGROW: return -1;
		default:                 return 0;
	}
}


//------------------------SLOTS-----------------
void Farm::handleCell(Cell &cell)
{
	if (cell.state == CELLSTATE_EMPTY)
		this->plant(cell);
	else
		this->harvest(cell);
}

void Farm::handle_speed1x_button(void)
{
	killTimer(m_timerID);
	m_timerID = startTimer(100);
}

void Farm::handle_speed2x_button(void)
{
	killTimer(m_timerID);
	m_timerID = startTimer(100/2);
}

void Farm::handle_speed4x_button(void)
{
	killTimer(m_timerID);
	m_timerID = startTimer(100/4);
}

void Farm::timerEvent(QTimerEvent *e)
{
	Q_UNUSED(e);
	m_timeLabel->setText("Time: " + QString::number(m_time));
	m_time++;

	for (int i = 0; i < 16; i++)
		m_cells[i]->nextStep();
}
