#ifndef CURSORUP_HPP
#define CURSORUP_HPP

#include "Command.hpp"



class CursorUp : public Command
{
public:

	virtual void execute(EditorModel& model)
	{

		model.moveCursorUp();
	}


	virtual void undo(EditorModel& model)
	{
		
	}

};




#endif // CURSORUP_HPP