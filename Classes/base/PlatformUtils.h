#ifndef PlatformUtil_h__
#define PlatformUtil_h__

#include <string>

using namespace std;

class PlatformUtils{
public:

	PlatformUtils();
	~PlatformUtils();

	static std::string CLASS_DEFAULT;
	void signInGoogle();
	void shareMyApp();
	void rateApp();
	void showHighScore();
	void updateScore(int score);
	void showInterstitialAd();
	void showVideoRewardAd();
	void initBanner();
	void showBanner();
	void hideBanner();
	void updateLeaderBoard(int mode, int score);
	void callAndroidFunction(std::string className, std::string methodName, std::string methodSignature, std::string parameters = "");
	
	static PlatformUtils *getInstance();
	static void destroyInstance();
};
#endif