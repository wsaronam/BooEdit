#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"



class CreateNewLine : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		_prevCursorColumn = model.cursorColumn();

		_prevStringVec = model.getStringVector();
		_prevIntVec = model.getIntVector();

		model.createNewLine();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoNewLine(_prevCursorColumn, _prevStringVec, _prevIntVec);
	}

private:
	unsigned int _prevCursorColumn;

	std::vector<std::string> _prevStringVec;
	std::vector<unsigned int> _prevIntVec;

};




#endif // NEWLINE_HPP