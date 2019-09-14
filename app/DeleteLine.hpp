#ifndef DELETELINE_HPP
#define DELETELINE_HPP

#include "Command.hpp"



class DeleteLine : public Command
{
public:

	virtual void execute(EditorModel& model)
	{
		_prevCursorColumn = model.cursorColumn();
		_prevCursorLine = model.cursorLine();
		_prevLineAmount = model.lineCount();

		_prevStringVec = model.getStringVector();
		_prevIntVec = model.getIntVector();

		model.deleteLine();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoDeleteLine(_prevCursorColumn, _prevStringVec, _prevIntVec, _prevLineAmount, _prevCursorLine);
	}

private:
	unsigned int _prevCursorColumn;
	unsigned int _prevCursorLine;
	unsigned int _prevLineAmount;

	std::vector<std::string> _prevStringVec;
	std::vector<unsigned int> _prevIntVec;

};




#endif // DELETELINE_HPP