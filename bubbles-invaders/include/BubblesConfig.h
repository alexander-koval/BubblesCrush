#ifndef BUBBLESCONFIG_H
#define BUBBLESCONFIG_H

namespace Bubbles {
    const int TIME = 500;

    const float MIN_RADIUS = 20;
    const float MAX_RADIUS = 50;

    const float MIN_SPEED = 50;
    const float MAX_SPEED = 400;

    const float MIN_POINTS = 10;
    const float MAX_POINTS = 100;

    float getSpeed(int radius) {
        float ratio = (radius - MIN_RADIUS) / (MAX_RADIUS - MIN_RADIUS);
        float speed = (MAX_SPEED + MIN_SPEED) -
                (MAX_SPEED + MIN_SPEED) * ratio + MIN_SPEED;
        return speed;
    }

    int getScore(int radius) {
        float ratio = (radius - MIN_RADIUS) / (MAX_RADIUS - MIN_RADIUS);
        int score = (MAX_POINTS + MIN_POINTS) -
                (MAX_POINTS + MIN_POINTS) * ratio + MIN_POINTS;
        return score;
    }
}

#endif // BUBBLESCONFIG_H
