#ifndef PARTICLES_HPP_INCLUDED
#define PARTICLES_HPP_INCLUDED

#include <array>

#include <GL/glew.h>
#include "glm.hpp"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>

#include "Camera.hpp"
#include "ObstacleMap.hpp"

/* Class for handling, updating and drawing particles */
class Particles
{
    public:
        /* nb: square root of the amount of particles */
        Particles(unsigned int width, unsigned int height, unsigned int nb=128);
        ~Particles();

        unsigned int getNbParticles() const;

        /* Places particles to random initial position
         * and gives them random velocity */
        void initialize();

        /* Allowes to change the force applied to all particles */
        void setForce (sf::Vector2f const& force);

        void computeNewPositions(sf::Time const& dt, ObstacleMap const& obstacleMap);

        void draw(sf::RenderWindow &window, Camera const& camera) const;

    private:
        sf::Vector2f _worldSize;
        sf::Vector2f _bufferSize;
        sf::Vector2f _force;

        /* Particles' positions are stored in these texture buffers */
        int _currentBufferIndex; //0 or 1 alternatively
        std::array<sf::RenderTexture, 2> _positions;
        std::array<sf::RenderTexture, 3> _velocities;

        sf::Shader _initialPositionsShader;
        sf::Shader _initialVelocitiesShader;
        sf::Shader _updateVelocityShader;
        sf::Shader _updatePositionShader;
        mutable sf::Shader _displayVerticesShader;

        /* Particles' coordinates on the buffer texture */
        GLuint _texCoordBufferID;
};

#endif // PARTICLES_HPP_INCLUDED
