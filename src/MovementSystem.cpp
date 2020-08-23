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

    // Update the current direction using the rotation speed
    Vec2 new_direction = sporadic.current_direction;   // Copy to make rotation safe
    double angle = sporadic.current_rotation_speed*dT; // * random_float_in_range(0.5, 1.5);
    new_direction.x = sporadic.current_direction.x * cos(angle) - sporadic.current_direction.y * sin(angle);
    new_direction.y = sporadic.current_direction.x * sin(angle) + sporadic.current_direction.y * cos(angle);
    sporadic.current_direction = new_direction;

    // Should we change the rotation speed?
    sporadic.time_to_change -= dT;
    if (sporadic.time_to_change <= 0){
        // Yes! Enough time has passed

        // Adjust the rotation speed for the next iteration
        double delta_angle = atan2(
            Vec2::cross(sporadic.current_direction, move.target_direction),
            Vec2::dot(sporadic.current_direction, move.target_direction)
        );
        sporadic.current_rotation_speed = (delta_angle > 0 ? 1.0 : -1.0) * sporadic.rotation_speed * random_float_in_range(0.5, 1.5);

        // Set new timer
        sporadic.time_to_change = sporadic.period * random_float_in_range(0.5, 1.5);
    }
}