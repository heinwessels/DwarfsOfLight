#include "MovementSystem.hpp"
#include "Game.hpp"

#include "RNG.hpp"

#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "MoveComponent.hpp"

MovementSystem::MovementSystem(Game &game)
    :   System(game, std::string("Moving System"))
{
    m_signature |= Component::get_component_signature<TransformComponent>();
    m_signature |= Component::get_component_signature<MoveComponent>();
}

void MovementSystem::update(double dT){
    for(auto const entity : m_pgame.get_entities()){
        if(has_valid_signature(*entity)){

            TransformComponent &transform = entity->get_component<TransformComponent>();
            MoveComponent &move = entity->get_component<MoveComponent>();

            if (move.type == MoveComponent::TypeStraight){
                handle_straight_movement(transform, move, dT);
            }
            else if (move.type == MoveComponent::TypeSporadic){

                //////////
                // move.target_direction = Vec2(1, 0);
                //////////

                handle_sporadic_movement(transform, move, dT);
            }
        }
    }
}

void MovementSystem::handle_straight_movement(TransformComponent &transform, MoveComponent &move, double dT){
    transform.position += move.target_direction * move.speed * dT;
}

void MovementSystem::handle_sporadic_movement(TransformComponent &transform, MoveComponent &move, double dT){

    auto &sporadic = move.sporadic; // Just for ease of use

    // First move in the current direction. Note this is <current>, not <target>.
    transform.position += sporadic.current_direction * move.speed * dT;

    // Update the current direction
    Vec2 new_direction = sporadic.current_direction;   // Copy to make rotation safe
    double angle = sporadic.rotation_speed*dT * random_float_in_range(0.5, 1.5);
    new_direction.x = sporadic.current_direction.x * cos(angle) - sporadic.current_direction.y * sin(angle);
    new_direction.y = sporadic.current_direction.x * sin(angle) + sporadic.current_direction.y * cos(angle);
    sporadic.current_direction = new_direction;

    // Now adjust the rotation speed for the next iteration
    double current_direction = atan2(sporadic.current_direction.y, sporadic.current_direction.x);
    double target_direction = atan2(move.target_direction.y, move.target_direction.x);
    double delta_angle = target_direction - current_direction;
    sporadic.rotation_speed += sporadic.tightness_factor * delta_angle * dT * random_float_in_range(0.5, 1.5);
}