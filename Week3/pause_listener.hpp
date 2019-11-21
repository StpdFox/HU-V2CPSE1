#ifndef PAUSE_LISTENER_HPP
#define PAUSE_LISTENER_HPP

class Pause_listener {
public:
    Pause_listener(){};

    virtual void pause_detected(int n) = 0;
};

#endif // PAUSE_LISTENER_HPP
