#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

#include <memory>
#include <vector>
#include <functional>

#include "Asteroid.hpp"
#include "RandomizeParams.hpp"
#include "Dimensions.hpp"
#include "ParticleSystem.hpp"

namespace test {

  using Asteroids = ParticleSystem<Asteroid>;

}

#endif// ASTEROIDS_HPP
