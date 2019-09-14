#ifndef TYPING_HPP
#define TYPING_HPP

#include "Command.hpp"



class Typing : public Command
{
public:

	Typing(char c)
	    : c{c}
	{
	}

	virtual void execute(EditorModel& model)
	{
		_prevStrVector = model.getStringVector();
		_prevColVector = model.getIntVector();
		_prevCol = model.cursorColumn();

		model.typeIntoModel(c);
	}


	virtual void undo(EditorModel& model)
	{
		model.undoTyping(_prevStrVector, _prevColVector, _prevCol);
	}


private:
	char c;

	std::vector<std::string> _prevStrVector;
	std::vector<unsigned int> _prevColVector;
	unsigned int _prevCol;
};




#endif // TYPING_HPP