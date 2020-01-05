#include <3dvolume.h>
#include <ml_logging.h>

int main(int argc, char **argv)
{
  ML_LOG(Debug, "3dvolume Starting.");
  L3Dvolume myApp;
  return myApp.run();
}
