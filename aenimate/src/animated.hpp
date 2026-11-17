#ifndef ANIMATED_h
#define ANIMATED_h

class Animated {
public:
  Animated() = default;
  virtual ~Animated() = default;
  virtual void reset() = 0;
  virtual void animate(long time, long ticks) = 0;
  virtual void render() = 0;
};

#endif // ANIMATED_h
