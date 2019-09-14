#ifndef CURSORUP_HPP
#define CURSORUP_HPP

#include "Command.hpp"



class CursorMoveUp : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		_prevCursorColumn = model.cursorColumn();
		_prevCursorLine = model.cursorLine();

		model.moveCursorUp();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoCursorUpDown(_prevCursorColumn, _prevCursorLine);
	}

private:
	unsigned int _prevCursorColumn;
	unsigned int _prevCursorLine;

};




#endif // CURSORUP_HPP