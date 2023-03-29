#include <stateHandler.h>
#include <menuState.h>
#include <playState.h>
#include <overState.h>

stateHandler::stateHandler(/* args */)
{
}

stateHandler::~stateHandler()
{
}

void stateHandler::checkState(std::unique_ptr<gameState>& rState)
{
    if(rState->stateInfo.close){
        /*

        */
        switch (rState->stateInfo.nextState)
        {
        case 0:
            rState = std::make_unique<menuState>();
            break;

        case 1:
            rState = std::make_unique<playState>();
            break;
        
        case 2:
            rState = std::make_unique<overState>();

        default:
            break;
        }
    }
}