#include "GameObject.h"

GameObject::GameObject()
{
    input = nullptr;
    window = nullptr;
    alive = true;
    Colliding = false;

    collisionBoxDebug.setFillColor(sf::Color::Transparent);
    collisionBoxDebug.setOutlineColor(sf::Color::Red);
    collisionBoxDebug.setOutlineThickness(1.f);


}

GameObject::~GameObject()
{

}

// Override this function to provide input handling for the derived class
void GameObject::handleInput(float dt)
{
}

// override this function to provide functionality
void GameObject::update(float dt)
{
}

void GameObject::updateCollisionBox(float dt)
{
    collisionBox = sf::FloatRect(getPosition().x, getPosition().y, getSize().x, getSize().y);
    setDebugCollisionBox(getPosition().x, getPosition().y, getSize().x, getSize().y);
}

// Sets the velocity of the sprite
void GameObject::setVelocity(sf::Vector2f vel)
{
    if (!isStatic)
    {
        velocity = vel;
    }
}
void GameObject::setVelocity(float vx, float vy)
{
    if (!isStatic)
    {
        velocity.x = vx;
        velocity.y = vy;
    }
}

void GameObject::applyImpulse(sf::Vector2f impulse)
{
    if (!isStatic)
    {
        velocity += impulse / mass;
    }
}

// get sprite velocity
sf::Vector2f GameObject::getVelocity()
{
    return velocity;
}

// Returns collision box + position, giving the collision box in the correct position
sf::FloatRect GameObject::getCollisionBox() {

    return collisionBox;

}

void GameObject::setDebugCollisionBox(float x, float y, float w, float h)
{
    collisionBoxDebug.setPosition(sf::Vector2f(x, y));
    collisionBoxDebug.setSize(sf::Vector2f(w, h));
}

bool GameObject::checkCollision(GameObject* otherBox)
{
    // Skip collision detection if both objects are tiles
    if (isTile && otherBox->getTile()) {
        return false; // No collision detection between two tiles
    }

    if (otherBox->getTag() == "Collectable" && tag =="Enemy" || otherBox->getTag() == "Enemy" && tag == "Collectable")
    {
		return false;
	}

    //Check if both objects are tagged as Enemy if they are , skip collision detection
    // This is to prevent the enemy from colliding with each other
    if (otherBox->getTag() == "Enemy" && tag == "Enemy")
    {
		return false;
	}
    // Get the collision box for both objects
    sf::FloatRect otherCollisionBox = otherBox->getCollisionBox();

    // Use intersects to check if the objects are colliding
    if (collisionBox.intersects(otherCollisionBox))
    {
        // Check if either object is a trigger and the other is not static
        //Doing this so that triggers can collide with non-static objects
        if ((isTrigger && !otherBox->getStatic()) || otherBox->getTrigger() && !isStatic)
        {
            return true;
        }
        // Check if either object is a trigger and the other is static
        if ((isTrigger && otherBox->getStatic()) || (otherBox->getTrigger() && isStatic))
        {
            // If the conditions are met, proceed with collision resolution
            // Get the half sizes of the two objects
            sf::Vector2f otherHalfSize = sf::Vector2f(otherCollisionBox.width / 2.0f, otherCollisionBox.height / 2.0f);
            sf::Vector2f thisHalfSize = sf::Vector2f(collisionBox.width / 2.0f, collisionBox.height / 2.0f);

            // Calculate the difference in position between the two objects
            sf::Vector2f otherPos = otherBox->getPosition() + otherHalfSize;
            sf::Vector2f thisPos = getPosition() + thisHalfSize;

            // Calculate the intersection depth in X and Y
            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;
            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            // Calculate the total inverse mass
            float totalInverseMass = getInverseMass() + otherBox->getInverseMass();

            // The push factor is the ratio of the other object's inverse mass to the total inverse mass
            float push = (totalInverseMass != 0) ? otherBox->getInverseMass() / totalInverseMass : 0.0f;
            push = std::min(std::max(push, 0.0f), 1.0f); // Clamp push value between 0 and 1

            // Adjust positions to resolve collision
            if (intersectX > intersectY) {
                //Collision on the right

                Direction.x = 1.f;
                Direction.y = 0.f;
                if (deltaX > 0.0f) {
                    move(intersectX * (1.0f - push), 0.f);
                    otherBox->move(-intersectX * push, 0.0f);
                }
                else {

                    //Collision on the left

                    Direction.x = -1.f;
                    Direction.y = 0.f;
                    move(-intersectX * (1.0f - push), 0.0f);
                    otherBox->move(intersectX * push, 0.0f);

           
                    
                }
            }
            else {
                if (deltaY > 0.0f) {

                    //Collision on the bottom
          
                    Direction.x = 0.f;
                    Direction.y = 1.f;
                    canJump = true;

                    move(0.0f, intersectY * (1.f - push));
                    otherBox->move(0.0f, -intersectY * push);


                }
                else {
                    //Collision on the top
                    Direction.x = 0.f;
                    Direction.y = -1.f;

                    move(0.0f, -intersectY * (1.0f - push));
                    otherBox->move(0.0f, intersectY * push);

                    
                }
            }

            return true;
        }
        else if (!isTrigger && !otherBox->getTrigger())
        {
            // If neither object is a trigger, proceed with collision resolution
            // Get the half sizes of the two objects
            sf::Vector2f otherHalfSize = sf::Vector2f(otherCollisionBox.width / 2.0f, otherCollisionBox.height / 2.0f);
            sf::Vector2f thisHalfSize = sf::Vector2f(collisionBox.width / 2.0f, collisionBox.height / 2.0f);

            // Calculate the difference in position between the two objects
            sf::Vector2f otherPos = otherBox->getPosition() + otherHalfSize;
            sf::Vector2f thisPos = getPosition() + thisHalfSize;

            // Calculate the intersection depth in X and Y
            float deltaX = otherPos.x - thisPos.x;
            float deltaY = otherPos.y - thisPos.y;
            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            // Calculate the total inverse mass
            float totalInverseMass = getInverseMass() + otherBox->getInverseMass();

            // The push factor is the ratio of the other object's inverse mass to the total inverse mass
            float push = (totalInverseMass != 0) ? otherBox->getInverseMass() / totalInverseMass : 0.0f;
            push = std::min(std::max(push, 0.0f), 1.0f); // Clamp push value between 0 and 1

            // Adjust positions to resolve collision
            if (intersectX > intersectY) {
                if (deltaX > 0.0f) {
                    //Collision on the right
                
                        Direction.x = 1.f;
                        Direction.y = 0.f;
                    
                    move(intersectX * (1.0f - push), 0.f);
                    otherBox->move(-intersectX * push, 0.0f);
                }
                else {
                    //Collision on the left
                   
                        Direction.x = -1.f;
                        Direction.y = 0.f;
                    

                    move(-intersectX * (1.0f - push), 0.0f);
                    otherBox->move(intersectX * push, 0.0f);
                }
            }
            else {
                if (deltaY > 0.0f) {

                    //Collision on the bottom
                  
                        Direction.x = 0.f;
                        Direction.y = 1.f;
                    
                    canJump = true;
                    move(0.0f, intersectY * (1.f - push));
                    otherBox->move(0.0f, -intersectY * push);


                }
                else {
                    //Collision on the top
                    Direction.x = 0.f;
                    Direction.y = -1.f;

                    move(0.0f, -intersectY * (1.0f - push));
                    otherBox->move(0.0f, intersectY * push);
                }
            }
            return true;
        }
        // If none of the conditions are met, it means either both are triggers
        // or the collision shouldn't be resolved (e.g., two non-static objects)
        return false;
    }
    return false;
}




// Reponse function, what the sprite does based on collision
// Colliding object is passed in for information
// e.g. compare sprite positions to determine new velocity direction.
// e.g. checking sprite type (world, enemy, bullet etc) so response is based on that.
//void GameObject::collisionResponse(GameObject* collider)
//{
//    // Check if the collider is not static and not a tile
//    if (!collider->getStatic() && !collider->getTile())
//    {
//        // If the collider is neither static nor a tile, update the colliding tag
//        collidingTag = collider->getTag();
//    }
//    else if (collider->getTile() && collider->getTag() == "Wall")
//    {
//        collidingTag = collider->getTag();
//    }
//    else if (collider->getTile() && collider->getTag() == "Collectable")
//    {
//        collidingTag = collider->getTag();
//    }
//}
void GameObject::collisionResponse(GameObject* collider)
{
    // Check if collider is a tile and has a specific tag ("Wall" or "Collectable"), or if it is neither static nor a tile.
    if ((collider->getTile() && (collider->getTag() == "Wall" || collider->getTag() == "Collectable")) ||
        (!collider->getStatic() && !collider->getTile()))
    {
        // Update the colliding tag
        collidingTag = collider->getTag();
    }
}
void GameObject::Jump(float jumpHeight)
{
    velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
    canJump = false;
}

std::string GameObject::getCollisionDirection()
{
    //If the direction is not 0,0
    if (Direction.x != 0 || Direction.y != 0)
    {
        //If the direction is 1,0
        if (Direction.x == 1)
        {
            return "Right";
        }
        //If the direction is -1,0
        if (Direction.x == -1)
        {
            return "Left";
        }
        //If the direction is 0,1
        if (Direction.y == 1)
        {
            return "Down";
        }
        //If the direction is 0,-1
        if (Direction.y == -1)
        {
            return "Up";
        }
    }
    return "None";
}



void GameObject::UpdatePhysics(sf::Vector2f* gravity, float deltaTime)
{

    if (!isStatic)
    {
        if (!isMassless)
        {
            velocity.y += gravity->y * deltaTime;

            // Clamp the gravity so that the object does not fall through the floor also known as tunneling
            velocity.y = std::min(velocity.y, gravity->y);
        }
        angularVelocity += torque * deltaTime;
        setRotation(getRotation() + angularVelocity * deltaTime);
        move(velocity * deltaTime);
        updateCollisionBox(deltaTime);
        //std::string tags= getTag();
       // if(tags != "Collectable") std::cout << getTag() << " Direction: " << Direction.x << "x" << Direction.y << std::endl;
    }
}
