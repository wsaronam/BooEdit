// EditorModel.cpp
//
// ICS 45C Fall 2016
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"


EditorModel::EditorModel()
{
	currentCursorLine = 1;
	currentCursorColumn = 1;
	LineAmount = 1;

	vectorOfColumns.push_back(1);
	vectorOfStrings.push_back("");
}


int EditorModel::cursorLine() const
{
    return currentCursorLine;
}


int EditorModel::cursorColumn() const
{
    return currentCursorColumn;
}


int EditorModel::lineCount() const
{
    return LineAmount;
}


const std::string& EditorModel::line(int lineNumber) const
{
	return vectorOfStrings[lineNumber - 1];
}


const std::string& EditorModel::currentErrorMessage() const
{
    return CurrentErrorMessage;
}


void EditorModel::setErrorMessage(const std::string& errorMessage)
{
	CurrentErrorMessage = errorMessage;
}


void EditorModel::clearErrorMessage()
{
	CurrentErrorMessage = "";
}




// ============================== COMMAND FUNCTIONS ==============================  

void EditorModel::moveCursorRight()
{
	if (currentCursorColumn == vectorOfColumns[currentCursorLine - 1] && currentCursorLine == LineAmount)  // if cursor is at the last line and last letter
	{
		EditorException Exception = EditorException("Already at end");
		throw Exception;
	}

	else if (currentCursorColumn == vectorOfColumns[currentCursorLine - 1]  && currentCursorLine != LineAmount)  // if cursor is at the last letter but not last line
	{
		currentCursorColumn = 1;
		currentCursorLine++;
	}

	else if (currentCursorColumn != vectorOfColumns[currentCursorLine - 1])  // if the cursor is not at the end of the line
	{
		currentCursorColumn++;
	}

}


void EditorModel::moveCursorLeft()
{
	if (currentCursorColumn == 1 && currentCursorLine == 1)  // if the cursor is at the first line and first letter
	{
		EditorException Exception = EditorException("Already at beginning");
		throw Exception;
	}

	else if (currentCursorColumn == 1 && currentCursorLine != 1)  // if the cursor is at the first letter but not first line
	{
		currentCursorLine--;
		currentCursorColumn = vectorOfColumns[currentCursorLine - 1];
	}

	else if (currentCursorColumn != 1)  // if the cursor is not at the beginning of a line
	{
		currentCursorColumn--;
	}
}


void EditorModel::moveCursorUp()
{
	if (currentCursorLine == 1)
	{
		EditorException Exception = EditorException("Already at top");
		throw Exception;
	}

	else if (currentCursorColumn <= vectorOfColumns[currentCursorLine - 2])
	{
		currentCursorLine--;
	}

	else
	{
		currentCursorColumn = vectorOfColumns[currentCursorLine - 2];
		currentCursorLine--;
	}
}


void EditorModel::moveCursorDown()
{
	if (currentCursorLine == LineAmount)
	{
		EditorException Exception = EditorException("Already at bottom");
		throw Exception;
	}

	else if (currentCursorColumn <= vectorOfColumns[currentCursorLine])
	{
		currentCursorLine++;
	}

	else
	{
		currentCursorColumn = vectorOfColumns[currentCursorLine];
		currentCursorLine++;
	}
}


void EditorModel::undoCursorUpDown(unsigned int prevCursorColumn, unsigned int prevCursorLine)
{
	currentCursorColumn = prevCursorColumn;
	currentCursorLine = prevCursorLine;
}


void EditorModel::moveCursorHome()
{
	if (vectorOfColumns[currentCursorLine - 1] != 1)
	{
		currentCursorColumn = 1;
	}

}


void EditorModel::moveCursorEnd()
{
	if (vectorOfColumns[currentCursorLine - 1] != currentCursorColumn)
	{
		currentCursorColumn = vectorOfColumns[currentCursorLine - 1];
	}

}


void EditorModel::undoMoveCursorHomeEnd(int prevColumn)
{
	currentCursorColumn = prevColumn;
}


void EditorModel::createNewLine()
{
	if (currentCursorLine == LineAmount && currentCursorColumn == vectorOfColumns[currentCursorLine - 1])  // at the last line and at the last letter
	{
		LineAmount++;
		currentCursorLine++;
		currentCursorColumn = 1;

		vectorOfColumns.push_back(1);
		vectorOfStrings.push_back("");
	}

	else if (currentCursorLine == LineAmount)  // at the last line but not last letter
	{
		std::string cutString = vectorOfStrings[currentCursorLine - 1].substr(currentCursorColumn - 1);
		vectorOfStrings[currentCursorLine - 1].erase(currentCursorColumn - 1);

		LineAmount++;
		currentCursorLine++;
		currentCursorColumn = 1;

		vectorOfColumns.push_back(cutString.size() + 1);
		vectorOfStrings.push_back(cutString);
	}

	else
	{
		vectorOfStrings.push_back("");
		vectorOfColumns.push_back(1);

		for (int counter = vectorOfStrings.size() - 2; counter != currentCursorLine - 1; counter--)
		{
			vectorOfStrings[counter + 1] = vectorOfStrings[counter];
			vectorOfColumns[counter + 1] = vectorOfColumns[counter];
		}

		std::string cutString = vectorOfStrings[currentCursorLine - 1].substr(currentCursorColumn - 1);
		vectorOfStrings[currentCursorLine - 1].erase(currentCursorColumn - 1);
		vectorOfColumns[currentCursorLine - 1] = vectorOfColumns[currentCursorLine - 1] - cutString.size();

		vectorOfStrings[currentCursorLine] = cutString;
		vectorOfColumns[currentCursorLine] = cutString.size() + 1;

		LineAmount++;
		currentCursorLine++;
		currentCursorColumn = 1;
	}
	
}


void EditorModel::undoNewLine(unsigned int& prevCursorCol, 
	std::vector<std::string>& prevStrVec, std::vector<unsigned int>& prevIntVec)
{
	LineAmount--;
	currentCursorLine--;
	currentCursorColumn = prevCursorCol;

	vectorOfStrings = prevStrVec;
	vectorOfColumns = prevIntVec;
}


void EditorModel::deleteLine()
{
	if (LineAmount == 1)  // if there's only one line
	{
		vectorOfStrings[0] = "";
		vectorOfColumns[0] = 1;

		currentCursorColumn = 1;
	}

	else if (currentCursorLine != LineAmount)  // if the cursor isn't on the last line
	{
		if (currentCursorColumn <= vectorOfColumns[currentCursorLine])  // if the cursor can fit in the next line
		{
			for (int counter = currentCursorLine - 1; counter < LineAmount - 1; counter++)
			{
				vectorOfStrings[counter] = vectorOfStrings[counter + 1];
				vectorOfColumns[counter] = vectorOfColumns[counter + 1];
			}

			vectorOfStrings.pop_back();
			vectorOfColumns.pop_back();

			LineAmount--;
		}

		else  // if it can't fit in the next line
		{
			for (int counter = currentCursorLine - 1; counter < LineAmount - 1; counter++)
			{
				vectorOfStrings[counter] = vectorOfStrings[counter + 1];
				vectorOfColumns[counter] = vectorOfColumns[counter + 1];
			}

			vectorOfStrings.pop_back();
			vectorOfColumns.pop_back();

			LineAmount--;
			currentCursorColumn = vectorOfColumns[currentCursorLine];
		}
	}

	else if (currentCursorLine == LineAmount)
	{
		if (currentCursorColumn <= vectorOfColumns[currentCursorLine - 2])
		{
			LineAmount--;
			currentCursorLine--;

			vectorOfColumns.pop_back();
			vectorOfStrings.pop_back();
		}

		else
		{
			currentCursorColumn = vectorOfColumns[currentCursorLine - 2];
			currentCursorLine--;
			LineAmount--;

			vectorOfColumns.pop_back();
			vectorOfStrings.pop_back();
		}
	}

}


void EditorModel::undoDeleteLine(unsigned int& prevCursorCol, 
	std::vector<std::string>& prevStrVec, std::vector<unsigned int>& prevIntVec, 
	unsigned int prevLineAmount, unsigned int prevCursorLine)
{
	LineAmount = prevLineAmount;
	currentCursorLine = prevCursorLine;
	currentCursorColumn = prevCursorCol;

	vectorOfStrings = prevStrVec;
	vectorOfColumns = prevIntVec;
}


void EditorModel::typeIntoModel(char c)
{
	vectorOfStrings[currentCursorLine - 1].insert(currentCursorColumn - 1, 1, c);
	vectorOfColumns[currentCursorLine - 1]++;

	currentCursorColumn++;
}


void EditorModel::undoTyping(std::vector<std::string>& prevStrVec, 
	std::vector<unsigned int>& prevColVec, unsigned int& prevCursorColumn)
{
	vectorOfStrings = prevStrVec;
	vectorOfColumns = prevColVec;
	currentCursorColumn = prevCursorColumn;
}


void EditorModel::deleteCharacter()
{
	if (currentCursorLine == 1 && currentCursorColumn == 1)
	{
		EditorException Exception = EditorException("Already at beginning");
		throw Exception;
	}

	else if (currentCursorColumn == 1)
	{
		currentCursorColumn = vectorOfColumns[currentCursorLine - 2];

		vectorOfStrings[currentCursorLine - 2] += vectorOfStrings[currentCursorLine - 1];
		vectorOfColumns[currentCursorLine - 2] += vectorOfColumns[currentCursorLine - 1] - 1;

		vectorOfStrings.erase(vectorOfStrings.begin() + currentCursorLine - 1);
		vectorOfColumns.erase(vectorOfColumns.begin() + currentCursorLine - 1);

		LineAmount--;
		currentCursorLine--;
	}

	else
	{
		vectorOfStrings[currentCursorLine - 1].erase(currentCursorColumn - 2, 1);
		vectorOfColumns[currentCursorLine - 1]--;
		currentCursorColumn--;
	}
}


void EditorModel::undoDeleteCharacter(unsigned int prevCursorColumn, unsigned int prevCursorLine, unsigned int prevLineAmount,
	std::vector<std::string> prevStrVector, std::vector<unsigned int> prevIntVector)
	{
		currentCursorColumn = prevCursorColumn;
		currentCursorLine = prevCursorLine;
		LineAmount = prevLineAmount;

		vectorOfStrings = prevStrVector;
		vectorOfColumns = prevIntVector;
	}




// ============================== HELPER FUNCTIONS ==============================  

std::vector<std::string> EditorModel::getStringVector()
{
	return vectorOfStrings;
}


std::vector<unsigned int> EditorModel::getIntVector()
{
	return vectorOfColumns;
}