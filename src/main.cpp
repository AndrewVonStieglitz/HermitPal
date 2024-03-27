#include "SDL.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "An SDL2 window with DirectX 11",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize DirectX 11
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* backBufferRTV = nullptr;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = 640;
    swapChainDesc.BufferDesc.Height = 480;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = GetActiveWindow(); // Assumes you only have one window
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &context);

    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &backBufferRTV);
    backBuffer->Release();

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Set our Render Target
        context->OMSetRenderTargets(1, &backBufferRTV, nullptr);

        // Clear the back buffer to a deep blue
        float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
        context->ClearRenderTargetView(backBufferRTV, clearColor);

        // Present the back buffer to the screen
        swapChain->Present(0, 0);
    }

    // Cleanup DirectX
    if(backBufferRTV) backBufferRTV->Release();
    if(swapChain) swapChain->Release();
    if(context) context->Release();
    if(device) device->Release();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
