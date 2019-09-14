#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP

#include "Command.hpp"



class CursorMoveHome : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		_prevCursorColumn = model.cursorColumn();
		model.moveCursorHome();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoMoveCursorHomeEnd(_prevCursorColumn);
	}

private:
	int _prevCursorColumn;

};




#endif // CURSORHOME_HPP