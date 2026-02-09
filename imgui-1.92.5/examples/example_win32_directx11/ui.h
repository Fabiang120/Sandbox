#pragma once

struct UIState {
    bool Open;
    bool CheckBoxValue;
    float Starting;
    int Starting1;
    char TextChars[64];
};

void RenderUI(UIState& state);
