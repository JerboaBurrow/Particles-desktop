#include <desktop.h>

std::string fixedLengthNumber(double x, unsigned length)
{
    std::string d = std::to_string(x);
    std::string dtrunc(length,' ');
    for (unsigned c = 0; c < dtrunc.length(); c++)
    {
        if (c >= d.length())
        {
            dtrunc[c] = '0';
        }
        else
        {
            dtrunc[c] = d[c];
        }
    }
    return dtrunc;
}

int main(int argv, char ** argc)
{

    jGL::DesktopDisplay::Config conf;

    conf.VULKAN = false;
    #ifdef MACOS
    conf.COCOA_RETINA = true;
    #endif

    jGL::DesktopDisplay display(glm::ivec2(resX, resY), "Particles", conf);
    display.setFrameLimit(60);

    glewInit();

    jGLInstance = std::move(std::make_shared<jGL::GL::OpenGLInstance>(display.getRes()));

    jGL::OrthoCam camera(resX, resY, glm::vec2(0.0,0.0));

    jGLInstance->setTextProjection(glm::ortho(0.0,double(resX),0.0,double(resY)));
    #ifndef MACOS
    jGLInstance->setMSAA(8);
    #else
    jGLInstance->setMSAA(1);
    #endif

    camera.setPosition(0.0f, 0.0f);

    EntityComponentSystem manager;

    jLog::Log log;

    Hop::Console console(log);

    std::unique_ptr<AbstractWorld> world;

    Hop::World::FiniteBoundary<double> mapBounds(0,0,16,16);
    Hop::World::FixedSource mapSource;

    world = std::make_unique<TileWorld>
    (
        2,
        &camera,
        16,
        1,
        &mapSource,
        &mapBounds
    );

    sRender & rendering = manager.getSystem<sRender>();
    auto assets = std::make_shared<Hop::Util::Assets::TextureAssetStore>(
        std::filesystem::path("assets"), jGLInstance
    );
    auto spriteRenderer = jGLInstance->createSpriteRenderer(8);
    rendering.setSpriteRenderer(spriteRenderer);
    rendering.setTextureAssetStore(assets);

    // setup physics system
    sPhysics & physics = manager.getSystem<sPhysics>();
    physics.setTimeStep(deltaPhysics);
    physics.setGravity(0.0, 0.0, -1.0);

    sCollision & collisions = manager.getSystem<sCollision>();

    auto det = std::make_unique<Hop::System::Physics::CellList>(1);
    auto res = std::make_unique<Hop::System::Physics::SpringDashpot>
    (
        deltaPhysics*10.0,
        0.66,
        0.0
    );
    collisions.setDetector(std::move(det));
    collisions.setResolver(std::move(res));

    Hop::LuaExtraSpace luaStore;

    luaStore.ecs = &manager;
    luaStore.world = world.get();
    luaStore.physics = &physics;
    luaStore.resolver = &collisions;

    console.luaStore(&luaStore);
    std::string status = console.luaStatus();
    if (status != "LUA_OK") { WARN(status) >> log; }

    high_resolution_clock::time_point tic, tock;
    double delta = 0.0;

    while (display.isOpen())
    {
        tic = high_resolution_clock::now();

        jGLInstance->beginFrame();

            jGLInstance->clear();

            delta = 0.0;
            for (int n = 0; n < 60; n++)
            {
                delta += deltas[n];
            }
            delta /= 60.0;

            std::stringstream debugText;

            double mouseX, mouseY;
            display.mousePosition(mouseX,mouseY);

            debugText << "Delta: " << fixedLengthNumber(delta,6)
                    << " ( FPS: " << fixedLengthNumber(1.0/delta,4)
                    << ")\n"
                    << "Mouse (" << fixedLengthNumber(mouseX,4)
                    << ","
                    << fixedLengthNumber(mouseY,4)
                    << ")\n";

            jGLInstance->text(
                debugText.str(),
                glm::vec2(resX*0.5f, resY-64.0f),
                0.5f,
                glm::vec4(0.0f,0.0f,0.0f,1.0f),
                glm::bvec2(true,true)
            );

            if (frameId == 30)
            {
                if (log.size() > 0)
                {
                    std::cout << log << "\n";
                }
            }

        jGLInstance->endFrame();

        display.loop();

        tock = high_resolution_clock::now();

        deltas[frameId] = duration_cast<duration<double>>(tock-tic).count();
        frameId = (frameId+1) % 60;

    }

    jGLInstance->finish();

    return 0;
}