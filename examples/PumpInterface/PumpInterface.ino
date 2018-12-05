#include <PumpInterface.h>


PumpInterface dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
