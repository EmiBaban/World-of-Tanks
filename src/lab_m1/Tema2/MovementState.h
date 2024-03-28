#pragma once

#include <iostream>
#include <random>
#include <map>
#include <string>

enum class MovementState
{
    GoingForward,
    GoingBackward,
    InPlaceRotationLeft,
    InPlaceRotationRight
};

int GetRandomNumberInRange(const int minInclusive, const int maxInclusive);

MovementState GetNextMovementState(const MovementState currentState);

std::string GetMovementStateName(const MovementState state);