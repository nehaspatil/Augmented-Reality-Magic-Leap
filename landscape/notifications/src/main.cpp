
#include <lnotifications.h>

#include <ml_logging.h>

int main(int argc, char **argv)
{
  ML_LOG(Debug, "Notifications App  Starting.");
  lnotifications myApp;
  return myApp.run();
}
