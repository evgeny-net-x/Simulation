#include "cell.h"

Cell::Cell(QWidget *parent) : QPushButton(parent)
{
	progress = 0;
	state = CELLSTATE_EMPTY;

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->setAutoFillBackground(true);
	this->update();

	connect(this, &QPushButton::released, this, &Cell::handleButton);
}

void Cell::plant(void)
{
	state = CELLSTATE_PLANTED;
	progress = 1;

	this->update();
}

void Cell::harvest(void)
{
	state = CELLSTATE_EMPTY;
	progress = 0;

	this->update();
}

void Cell::nextStep(void)
{
	if (state == CELLSTATE_EMPTY || state == CELLSTATE_OVERGROW)
		return;

	progress++;
	switch (progress) {
		case PROGRESS_PLANTED:  state = CELLSTATE_PLANTED;  break;
		case PROGRESS_GREEN:    state = CELLSTATE_GREEN;    break;
		case PROGRESS_IMMATURE: state = CELLSTATE_IMMATURE; break;
		case PROGRESS_MATURE:   state = CELLSTATE_MATURE;   break;
		case PROGRESS_OVERGROW: state = CELLSTATE_OVERGROW; break;
	}

	this->update();
}

void Cell::update(void)
{
	QString style = "border: 1px;";

	switch(state) {
	case CELLSTATE_EMPTY:    style += "background-color: white;"; break;
	case CELLSTATE_PLANTED:  style += "background-color: black;";  break;
	case CELLSTATE_GREEN:    style += "background-color: green;";  break;
	case CELLSTATE_IMMATURE: style += "background-color: yellow;"; break;
	case CELLSTATE_MATURE:   style += "background-color: red;";    break;
	case CELLSTATE_OVERGROW: style += "background-color: brown;";  break;
	}

	setStyleSheet(style);
}

void Cell::handleButton(void)
{
	emit signalFromCell(*this);
}
