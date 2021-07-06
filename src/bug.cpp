#include "bug.h"

void Bug::Update() {
    UpdateDir();
    UpdateHead();
}

void Bug::UpdateDir() {
    if (*count != 5) {
        *count += 1;
    } else {
        direction = Direction(random_dir(engine));
        *count = 0;
    }
}