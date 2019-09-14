#ifndef CURSORDOWN_HPP
#define CURSORDOWN_HPP

#include "Command.hpp"



class CursorMoveDown : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		_prevCursorColumn = model.cursorColumn();
		_prevCursorLine = model.cursorLine();

		model.moveCursorDown();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoCursorUpDown(_prevCursorColumn, _prevCursorLine);
	}

private:
	unsigned int _prevCursorColumn;
	unsigned int _prevCursorLine;

};




#endif // CURSORDOWN_HPP