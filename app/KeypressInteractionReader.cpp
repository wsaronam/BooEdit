// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2016
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"

#include "CursorRight.hpp"
#include "CursorLeft.hpp"

#include "CursorUp.hpp"
#include "CursorDown.hpp"

#include "CursorHome.hpp"
#include "CursorEnd.hpp"

#include "NewLine.hpp"

#include "typing.hpp"
#include "BackSpace.hpp"

#include "DeleteLine.hpp"


// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
                case 'X':
                    {  return Interaction::quit();  }

                case 'Z':
                    {  return Interaction::undo();  }

                case 'A':
                    {  return Interaction::redo();  }

                case 'O':
                {
                    Command* CursorMoveRightCommand = new CursorMoveRight;
                    return Interaction::command(CursorMoveRightCommand);
                }
                    
                case 'U':
                {
                    Command* CursorMoveLeftCommand = new CursorMoveLeft;
                    return Interaction::command(CursorMoveLeftCommand);
                }

                case 'I':
                {
                    Command* CursorMoveUpCommand = new CursorMoveUp;
                    return Interaction::command(CursorMoveUpCommand);
                }

                case 'K':
                {
                    Command* CursorMoveDownCommand = new CursorMoveDown;
                    return Interaction::command(CursorMoveDownCommand);
                }

                case 'Y':
                {
                    Command* CursorMoveHomeCommand = new CursorMoveHome;
                    return Interaction::command(CursorMoveHomeCommand);
                }

                case 'P':
                {
                    Command* CursorMoveEndCommand = new CursorMoveEnd;
                    return Interaction::command(CursorMoveEndCommand);
                }

                case 'J':
                {
                    Command* createNewLine = new CreateNewLine;
                    return Interaction::command(createNewLine);
                }

                case 'M':
                {
                    Command* createNewLine2 = new CreateNewLine;
                    return Interaction::command(createNewLine2);
                }

                case 'D':
                {
                    Command* deleteLine = new DeleteLine;
                    return Interaction::command(deleteLine);
                }

                case 'H':
                {
                    Command* backSpace = new BackSpace;
                    return Interaction::command(backSpace);
                }
            }
        }

        else
        {
            Command* TypingCommand = new Typing(keypress.code());
            return Interaction::command(TypingCommand);
        }
    }
}

