#include "port/imgui.h"

#include <array>
#include <atomic>
#include <filesystem>
#include <aurora/gfx.h>
#include <chrono>
#include <cmath>
#include <fmt/format.h>
#include <imgui.h>
#include <numeric>
#include <thread>
#include <SDL3/SDL_dialog.h>

#if _WIN32
#include "Windows.h"
#endif

static bool m_frameRate = true;
static bool m_pipelineInfo = false;
static bool m_graphicsBackend = true;
static int m_debugOverlayCorner = 0; // top-left

using namespace std::string_literals;
using namespace std::string_view_literals;

static void SetOverlayWindowLocation(int corner)
{
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImVec2 workPos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 workSize = viewport->WorkSize;
    ImVec2 windowPos;
    ImVec2 windowPosPivot;
    constexpr float padding = 10.0f;
    windowPos.x = (corner & 1) != 0 ? (workPos.x + workSize.x - padding) : (workPos.x + padding);
    windowPos.y = (corner & 2) != 0 ? (workPos.y + workSize.y - padding) : (workPos.y + padding);
    windowPosPivot.x = (corner & 1) != 0 ? 1.0f : 0.0f;
    windowPosPivot.y = (corner & 2) != 0 ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
}

static void ImGuiStringViewText(std::string_view text)
{
    // begin()/end() do not work on MSVC
    ImGui::TextUnformatted(text.data(), text.data() + text.size());
}

static std::string BytesToString(size_t bytes)
{
    constexpr std::array suffixes{"B"sv, "KB"sv, "MB"sv, "GB"sv, "TB"sv, "PB"sv, "EB"sv};
    uint32_t s = 0;
    auto count = static_cast<double>(bytes);
    while (count >= 1024.0 && s < 7)
    {
        s++;
        count /= 1024.0;
    }
    if (count - floor(count) == 0.0)
    {
        return fmt::format(FMT_STRING("{}{}"), static_cast<size_t>(count), suffixes[s]);
    }
    return fmt::format(FMT_STRING("{:.1f}{}"), count, suffixes[s]);
}

const char* imgui_get_image_path_from_popup()
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    const std::filesystem::path exeDir = std::filesystem::path(exePath).parent_path();

    const char* filesToCheck[] = { "GMPE01_00.iso", "GMPE01_00.rvz" };

    static std::string foundPath;

    for (const char* file : filesToCheck) {
        std::filesystem::path filePath = exeDir / file;
        if (exists(filePath)) {
            foundPath = filePath.string();
            return foundPath.c_str();
        }
    }

    // --- Not found: ask the user ---

    struct DialogState {
        std::string selectedPath;
        bool        hasResult = false;
        bool        cancelled = false;
    } dlg;

    auto fileDialogCallback = [](void* userdata, const char* const* filelist, int /*filter*/) {
        auto* state = static_cast<DialogState*>(userdata);
        if (filelist && *filelist) {
            state->selectedPath = *filelist;
            state->cancelled    = false;
        } else {
            state->cancelled = true;
        }
        state->hasResult = true;
    };

    static constexpr SDL_DialogFileFilter filters[] = {
        { "GameCube Images", "iso;rvz" },
    };

    ImGui::GetIO().FontGlobalScale = 1.5f;

    bool dialogOpen = false;

    while (true) {
        aurora_update();
        aurora_begin_frame();

        ImGui::OpenPopup("Missing game image");
        if (ImGui::BeginPopupModal("Missing game image", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("GMPE01_00.iso or GMPE01_00.rvz not found next to the exe.");
            ImGui::Text("Please select the file manually.");
            ImGui::Spacing();

            // Show result / error from a previous attempt
            if (dlg.hasResult && dlg.cancelled) {
                ImGui::TextColored({1, 0.4f, 0.4f, 1}, "No file selected. Please try again.");
            }
            if (dlg.hasResult && !dlg.cancelled) {
                // Validate the chosen file name
                std::filesystem::path chosen(dlg.selectedPath);
                std::string name = chosen.filename().string();
                foundPath = dlg.selectedPath;
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                aurora_end_frame();

                ImGui::GetIO().FontGlobalScale = 1.0f;
                return foundPath.c_str();
            }

            ImGui::Spacing();

            if (dialogOpen) {
                ImGui::BeginDisabled();
                ImGui::Button("Browse...");
                ImGui::EndDisabled();
                ImGui::SameLine();
                ImGui::TextDisabled("(dialog open)");
            } else {
                if (ImGui::Button("Browse...")) {
                    dlg.hasResult = false;
                    dlg.cancelled = false;
                    dialogOpen    = true;
                    SDL_ShowOpenFileDialog(
                        fileDialogCallback,
                        &dlg,
                        nullptr,
                        filters,
                        std::size(filters),
                        nullptr,
                        false
                    );
                }
            }

            // Check if the async callback has fired
            if (dialogOpen && dlg.hasResult) {
                dialogOpen = false;
            }

            ImGui::EndPopup();
        }

        aurora_end_frame();
    }

    return nullptr;
}

void imgui_main(const AuroraInfo *info)
{

    ImGuiIO &io = ImGui::GetIO();
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration |
                                   ImGuiWindowFlags_AlwaysAutoResize |
                                   ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (m_debugOverlayCorner != -1)
    {
        SetOverlayWindowLocation(m_debugOverlayCorner);
        windowFlags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.65f);
    if (ImGui::Begin("Debug Overlay", nullptr, windowFlags))
    {
        bool hasPrevious = false;
        if (m_frameRate)
        {
            if (hasPrevious)
            {
                ImGui::Separator();
            }
            hasPrevious = true;

            ImGuiStringViewText(fmt::format(FMT_STRING("FPS: {:.1f}\n"), io.Framerate));
        }
        if (m_graphicsBackend)
        {
            if (hasPrevious)
            {
                ImGui::Separator();
            }
            hasPrevious = true;

            std::string_view backendString = "Unknown"sv;
            switch (info->backend)
            {
            case BACKEND_D3D12:
                backendString = "D3D12"sv;
                break;
            case BACKEND_METAL:
                backendString = "Metal"sv;
                break;
            case BACKEND_VULKAN:
                backendString = "Vulkan"sv;
                break;
            case BACKEND_OPENGL:
                backendString = "OpenGL"sv;
                break;
            case BACKEND_OPENGLES:
                backendString = "OpenGL ES"sv;
                break;
            case BACKEND_WEBGPU:
                backendString = "WebGPU"sv;
                break;
            case BACKEND_NULL:
                backendString = "Null"sv;
                break;
            }
            ImGuiStringViewText(fmt::format(FMT_STRING("Backend: {}\n"), backendString));
        }
        if (m_pipelineInfo)
        {
            if (hasPrevious)
            {
                ImGui::Separator();
            }
            hasPrevious = true;
            auto stats = aurora_get_stats();

            ImGuiStringViewText(
                fmt::format(FMT_STRING("Queued pipelines:  {}\n"), stats->queuedPipelines));
            ImGuiStringViewText(
                fmt::format(FMT_STRING("Created pipelines:    {}\n"), stats->createdPipelines));
            ImGuiStringViewText(
                fmt::format(FMT_STRING("Draw call count:   {}\n"), stats->drawCallCount));
            ImGuiStringViewText(fmt::format(FMT_STRING("Merged draw calls: {}\n"),
                                            stats->mergedDrawCallCount));
            ImGuiStringViewText(fmt::format(FMT_STRING("Vertex size:       {}\n"),
                                            BytesToString(stats->lastVertSize)));
            ImGuiStringViewText(fmt::format(FMT_STRING("Uniform size:      {}\n"),
                                            BytesToString(stats->lastUniformSize)));
            ImGuiStringViewText(fmt::format(FMT_STRING("Index size:        {}\n"),
                                            BytesToString(stats->lastIndexSize)));
            ImGuiStringViewText(fmt::format(FMT_STRING("Storage size:      {}\n"),
                                            BytesToString(stats->lastStorageSize)));
            ImGuiStringViewText(fmt::format(
                FMT_STRING("Total:             {}\n"),
                BytesToString(stats->lastVertSize + stats->lastUniformSize +
                              stats->lastIndexSize + stats->lastStorageSize)));
        }
    }
    ImGui::End();
}

class Limiter
{
    using delta_clock = std::chrono::high_resolution_clock;
    using duration_t = std::chrono::nanoseconds;

  public:
    void Reset()
    {
        m_oldTime = delta_clock::now();
    }

    void Sleep(duration_t targetFrameTime)
    {
        if (targetFrameTime.count() == 0)
        {
            return;
        }

        auto start = delta_clock::now();
        duration_t adjustedSleepTime = SleepTime(targetFrameTime);
        if (adjustedSleepTime.count() > 0)
        {
            NanoSleep(adjustedSleepTime);
            duration_t overslept = TimeSince(start) - adjustedSleepTime;
            if (overslept < duration_t{targetFrameTime})
            {
                m_overheadTimes[m_overheadTimeIdx] = overslept;
                m_overheadTimeIdx = (m_overheadTimeIdx + 1) % m_overheadTimes.size();
            }
        }
        Reset();
    }

    duration_t SleepTime(duration_t targetFrameTime)
    {
        const auto sleepTime = duration_t{targetFrameTime} - TimeSince(m_oldTime);
        m_overhead = std::accumulate(m_overheadTimes.begin(), m_overheadTimes.end(), duration_t{}) /
                     m_overheadTimes.size();
        if (sleepTime > m_overhead)
        {
            return sleepTime - m_overhead;
        }
        return duration_t{0};
    }

  private:
    delta_clock::time_point m_oldTime;
    std::array<duration_t, 4> m_overheadTimes{};
    size_t m_overheadTimeIdx = 0;
    duration_t m_overhead = duration_t{0};

    duration_t TimeSince(delta_clock::time_point start)
    {
        return std::chrono::duration_cast<duration_t>(delta_clock::now() - start);
    }

#if _WIN32
    bool m_initialized;
    double m_countPerNs;

    void NanoSleep(const duration_t duration)
    {
        if (!m_initialized)
        {
            LARGE_INTEGER freq;
            QueryPerformanceFrequency(&freq);
            m_countPerNs = static_cast<double>(freq.QuadPart) / 1000000000.0;
            m_initialized = true;
        }

        DWORD ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        auto tickCount =
            static_cast<LONGLONG>(static_cast<double>(duration.count()) * m_countPerNs);
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        if (ms > 10)
        {
            // Adjust for Sleep overhead
            ::Sleep(ms - 10);
        }
        auto end = count.QuadPart + tickCount;
        do
        {
            QueryPerformanceCounter(&count);
        } while (count.QuadPart < end);
    }
#else
    void NanoSleep(const duration_t duration)
    {
        std::this_thread::sleep_for(duration);
    }
#endif
};

static Limiter g_frameLimiter;
void frame_limiter()
{
    g_frameLimiter.Sleep(
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{1}) / 60);
}
