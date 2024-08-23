#ifndef DESKTOP
#define DESKTOP

#include <jGL/jGL.h>
#include <jGL/OpenGL/openGLInstance.h>
#include <jGL/orthoCam.h>
#include <jGL/Display/desktopDisplay.h>

#include <Object/entityComponentSystem.h>
#include <System/Physics/sPhysics.h>
#include <System/Rendering/sRender.h>
#include <System/Physics/sCollision.h>
#include <World/world.h>
#include <World/tileWorld.h>
#include <Console/console.h>

#include <jLog/jLog.h>

#include <chrono>
using namespace std::chrono;

std::string fixedLengthNumber(double x, unsigned length);

using Hop::Object::Component::cTransform;
using Hop::Object::Component::cPhysics;
using Hop::Object::Component::cRenderable;
using Hop::Object::Component::cSprite;
using Hop::Object::EntityComponentSystem;
using Hop::Object::Id;
using Hop::System::Rendering::sRender;
using Hop::System::Physics::CollisionDetector;
using Hop::System::Physics::CollisionResolver;
using Hop::System::Physics::sPhysics;
using Hop::System::Physics::sCollision;
using Hop::World::MapSource;
using Hop::World::Boundary;
using Hop::World::AbstractWorld;
using Hop::World::TileWorld;
using jLog::INFO;
using jLog::WARN;

const int resX = 800;
const int resY = 1000;

uint8_t frameId = 0;
double deltas[60];

const double deltaPhysics = 1.0/900.0;

std::shared_ptr<jGL::jGLInstance> jGLInstance;

#endif /* DESKTOP */
