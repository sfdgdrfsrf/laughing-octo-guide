#include <jni.h>
#include <cstddef>
#include <cstdint>
#include <optional>

extern "C" {
    struct lua_State;
}

// Emulated engine structure mapping Trunk2012's globalStates array layout
struct VMState {
    void* unknown_padding; 
    lua_State* state;
};

// Global pointer to hold the discovered location of the ScriptContext memory region
uintptr_t scriptContextBaseAddress = 0; 

struct LuaStateInfo {
    std::size_t vmIndex;
    lua_State* state;
    bool valid;
};

// JNI Bridge: Allows your compiled Android App UI to call this function over the memory space
extern "C" JNIEXPORT jlong JNICALL
Java_com_roblox_client_ActivityGlView_nativePassInput(JNIEnv* env, jobject thiz, jlong requested_index) {
    
    if (scriptContextBaseAddress == 0) {
        return 0; // ScriptContext signature not yet established
    }

    // Safely typecast the target offset inside the memory container
    VMState* globalStates = reinterpret_cast<VMState*>(scriptContextBaseAddress);
    
    if (globalStates == nullptr) {
        return 0;
    }

    // Extract the raw pointer value out of the emulated engine structure mapping
    lua_State* activeState = globalStates[requested_index].state;

    if (activeState == nullptr) {
        return 0;
    }

    return reinterpret_cast<jlong>(activeState);
}
