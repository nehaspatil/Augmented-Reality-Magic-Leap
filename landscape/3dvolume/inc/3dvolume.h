#include <lumin/LandscapeApp.h>
#include <lumin/InitArg.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
#include <L3DImageController.h>

class L3Dvolume : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
	L3Dvolume();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~L3Dvolume();

  /**
   * Disallows the copy constructor.
   */
  L3Dvolume(const L3Dvolume&) = delete;

  /**
   * Disallows the move constructor.
   */
  L3Dvolume(L3Dvolume&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  L3Dvolume& operator=(const L3Dvolume&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  L3Dvolume& operator=(L3Dvolume&&) = delete;

protected:
  /**
   * Initializes the Landscape Application.
   * @return - 0 on success, error code on failure.
   */
  int init() override;

  /**
   * Deinitializes the Landscape Application.
   * @return - 0 on success, error code on failure.
   */
  int deInit() override;

  /**
   * This is called each time the application is launched from the icon grid.
   * Most apps choose to create a new prism.
   * @param initArg - the initial application argument
   */
  void onAppStart(const lumin::InitArg&) override;


};
