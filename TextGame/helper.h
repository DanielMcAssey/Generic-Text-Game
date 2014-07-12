#ifndef HELPER_H
#define HELPER_H
 
class Helper {
public:
	Helper(void);
	~Helper(void);

	void setWindowTitle(LPCTSTR windowTitle);
	void resizeWindow(unsigned int x, unsigned int y);
	void maximizeWindow();
	int generateRandInt(int low, int high);
	std::string toLower(std::string text);
};
 
#endif