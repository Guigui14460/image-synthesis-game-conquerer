#include "StartStage.hpp"
#include "PlayingStage.hpp"
#include "EndStage.hpp"

std::unique_ptr<GameStage> StartStage::nextStage() const {
    return std::unique_ptr<GameStage>(new PlayingStage());
}

std::unique_ptr<GameStage> PlayingStage::nextStage() const {
    return std::unique_ptr<GameStage>(new EndStage());
}

std::unique_ptr<GameStage> EndStage::nextStage() const {
    return std::unique_ptr<GameStage>(new StartStage());
}
