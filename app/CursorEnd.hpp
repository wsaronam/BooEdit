#ifndef CURSOREND_HPP
#define CURSOREND_HPP

#include "Command.hpp"



class CursorMoveEnd : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		_prevCursorColumn = model.cursorColumn();
		model.moveCursorEnd();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoMoveCursorHomeEnd(_prevCursorColumn);
	}

private:
	int _prevCursorColumn;

};




#endif // CURSOREND_HPP