#pragma once

#include <Modules/module.h>


namespace SlavaScript::modules {
    namespace draw_f {
        extern std::shared_ptr<SlavaScript::lang::Function> window, color, line, rect, frect, circle, fcircle, repaint, clear, framelimit, keypressed, mousehover, close;
    }

    class Draw : public Module<Draw> {
    public:
        static void initConstants();
        static void initFunctions();
    };
}
