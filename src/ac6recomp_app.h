#pragma once

#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/rex_app.h>
#include <rex/ui/overlay/debug_overlay.h>

#include "render_hooks.h"

REXCVAR_DECLARE(bool, vfetch_index_rounding_bias);

class Ac6recompApp : public rex::ReXApp {
 public:
  using rex::ReXApp::ReXApp;

  static std::unique_ptr<rex::ui::WindowedApp> Create(
      rex::ui::WindowedAppContext& ctx) {
    return std::unique_ptr<Ac6recompApp>(new Ac6recompApp(ctx, "ac6recomp",
        PPCImageConfig));
  }

 protected:
  void OnPreSetup(rex::RuntimeConfig& config) override {
    REXCVAR_SET(vfetch_index_rounding_bias, true);
    REXCVAR_SET(ac6_unlock_fps, true);
    REXCVAR_SET(vsync, false);
  }

  void OnCreateDialogs(rex::ui::ImGuiDrawer* drawer) override {
    debug_overlay()->SetStatsProvider([] {
      auto gs = ac6::GetFrameStats();
      return rex::ui::FrameStats{gs.frame_time_ms, gs.fps, gs.frame_count};
    });
  }

};
