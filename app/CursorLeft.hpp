#ifndef CURSORLEFT_HPP
#define CURSORLEFT_HPP

#include "Command.hpp"



class CursorMoveLeft : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		model.moveCursorLeft();
	}


	virtual void undo(EditorModel& model)
	{
		model.moveCursorRight();
	}

};




#endif // CURSORLEFT_HPP