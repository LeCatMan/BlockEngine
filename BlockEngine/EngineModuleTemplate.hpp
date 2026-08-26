#pragma once

// ============================================================================
// Module: Engine Subsystem Template
// Description: Standardized layout for consistency across the engine
// ============================================================================

namespace Engine {

    // Status codes for clean error handling
    enum class Result : int {
        Success = 0,
        Failure = -1,
        NotInitialized = -2
    };

    class Subsystem {
    public:
        // Initialization
        static Result Init();

        // Shutdown (Clean teardown returning a status code)
        static int ShutDown();

        // Core update loop
        static void Update(float deltaTime);

    private:
        // Internal state variables kept private for consistency
        static bool s_IsInitialized;
    };

}