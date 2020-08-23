#pragma once

typedef unsigned long ComponentListSignature;
typedef unsigned int ComponentID;

constexpr ComponentID TransformComponentID = 0;
constexpr ComponentID ControllerComponentID = 1;
constexpr ComponentID RenderComponentID = 2;
constexpr ComponentID CollisionBoxComponentID = 3;
constexpr ComponentID DamgeComponentID = 4;
constexpr ComponentID HealthComponentID = 5;
constexpr ComponentID LightComponentID = 6;
constexpr ComponentID PathfindingComponentID = 7;
constexpr ComponentID AIComponentID = 8;
constexpr ComponentID MoveComponentID = 9;
constexpr ComponentID TeamComponentID = 10;
constexpr ComponentID LifeComponentID = 11;

// TODO This should be type TeamID, not int.
constexpr int TeamBug = 0;
constexpr int TeamGoblin = 1;
constexpr int TeamDwarf = 2;
constexpr int TeamPlant = 3;