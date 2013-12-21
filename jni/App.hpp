#ifndef APP_HPP
#define APP_HPP

namespace test {

  class App {

  public:
	void Init();
	void Update();
	void Draw();
	void Release();

	// handle some parameters form device
	void Touch(float newX, float newY);
	void ScreenSize(float newWidth, float newHeight);

  protected:
  private:
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
  };

}

#endif
