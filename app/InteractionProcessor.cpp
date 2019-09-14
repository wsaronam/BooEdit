// InteractionProcessor.cpp
//
// ICS 45C Fall 2016
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include <iostream>


// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    view.refresh();

    std::vector<Command*> VectorOfUndoCommands;
    std::vector<Command*> VectorOfRedoCommands;

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if (VectorOfUndoCommands.size() != 0)
            {
                Command* undoCommand = VectorOfUndoCommands.back();
                undoCommand->undo(model);

                VectorOfRedoCommands.push_back(undoCommand);
                VectorOfUndoCommands.pop_back();

                view.refresh();
            }
            
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if (VectorOfRedoCommands.size() != 0)
            {
                Command* redoCommand = VectorOfRedoCommands.back();
                redoCommand->execute(model);

                VectorOfUndoCommands.push_back(redoCommand);
                VectorOfRedoCommands.pop_back();

                view.refresh();
            }
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                VectorOfUndoCommands.push_back(command);
                command->execute(model);
                model.clearErrorMessage();
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
        }
    }

    for (int counter = 0; counter < VectorOfUndoCommands.size(); counter++)
    {  delete VectorOfUndoCommands[counter];  }

    for (int counter2 = 0; counter2 < VectorOfRedoCommands.size(); counter2++)
    {  delete VectorOfRedoCommands[counter2];  }

}

