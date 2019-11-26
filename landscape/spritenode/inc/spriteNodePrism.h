
#include <lumin/LandscapeApp.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
/**
 * qa_texturePack Landscape Application
 */
class spriteNodePrism : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
	spriteNodePrism();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~spriteNodePrism();

  /**
   * Disallows the copy constructor.
   */
  spriteNodePrism(const spriteNodePrism&) = delete;

  /**
   * Disallows the move constructor.
   */
  spriteNodePrism(spriteNodePrism&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  spriteNodePrism& operator=(const spriteNodePrism&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  spriteNodePrism& operator=(spriteNodePrism&&) = delete;

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
   * Runs this method on the Landscape Application's Event Update Thread.
   * @param fDelta - time delta since last frame.
   * @return - true to continue running, false to terminate the application.
   */
  bool updateLoop(float fDelta) override;

  /**
   * Reacts to incoming events, runs on the Landscape Application's Event Update Thread.
   * @param event - incoming Server Event.
   * @return - true if the incoming event was consumed, false otherwise.
   */
  bool eventListener(lumin::ServerEvent* event) override;

private:
  lumin::Prism* prism_ = nullptr;  // represents the bounded space where the Scene Graph renders.
};
