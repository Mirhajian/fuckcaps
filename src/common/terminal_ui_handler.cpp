#include "terminal_ui_handler.hpp"

#include <ftxui/dom/elements.hpp>

void TerminalUiHandler::drawScreen() {
    using namespace ftxui;

    Element document =
    vbox({
        text("The Window") | bold | color(Color::Blue),
        gauge(0.5),
        text("The Footer")
    });
    // Element document =
    //   hbox({
    //      text("left")    | border,
    //      text("middle")  | border | flex,
    //      text("right")   | border,
    //   });

    auto screen = Screen::Create(
        Dimension::Full(),  // width
        Dimension::Fit(document)  // height
    );

    // Render(screen, document);
    // screen.Print();

    document = border(document);

    // document = document | border;

    // document |= border;

    Render(screen, document);
    screen.Print();
}
