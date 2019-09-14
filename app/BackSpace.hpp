#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"



class BackSpace : public Command
{
public:

	virtual void execute(EditorModel& model)
	{	
		_prevCursorCol = model.cursorColumn();
		_prevCursorLine = model.cursorLine();
		_prevLineAmount = model.lineCount();

		_prevStrVector = model.getStringVector();
		_prevIntVector = model.getIntVector();

		model.deleteCharacter();
	}


	virtual void undo(EditorModel& model)
	{
		model.undoDeleteCharacter(_prevCursorCol, _prevCursorLine, _prevLineAmount, _prevStrVector, _prevIntVector);
	}

private:
	unsigned int _prevCursorCol;
	unsigned int _prevCursorLine;
	unsigned int _prevLineAmount;

	std::vector<std::string> _prevStrVector;
	std::vector<unsigned int> _prevIntVector;
};




#endif // BACKSPACE_HPP