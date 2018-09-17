#include "CongratDialog.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "dragonBones\cocos2dx\CCFactory.h"
#include "SceneManager.h"
#include "base\GameConstant.h"

CongratDialog::CongratDialog()
{

}

CongratDialog::~CongratDialog()
{

}

bool CongratDialog::init()
{
	if (!BasePopupDialog::init())
		return false;
	Node* node = CSLoader::createNode("CongratDialog.csb");
	this->addChild(node);
	this->bgImage = node->getChildByName("bgImage");
	auto bgImage = this->bgImage;
	auto bgMessage = bgImage->getChildByName("bg_message");

	this->continueButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_continue"));
	this->continueButton->addClickEventListener(CC_CALLBACK_1(CongratDialog::onContinue, this));
	this->shareButton = dynamic_cast<ui::Button *>(bgImage->getChildByName("btn_share"));
	this->shareButton->addClickEventListener(CC_CALLBACK_1(CongratDialog::onShare, this));

	const auto factory = dragonBones::CCFactory::getFactory();
	//factory->loadDragonBonesData("mecha_1002_101d_show/mecha_1002_101d_show_ske.json");
	//factory->loadDragonBonesData("mecha_1002_101d_show/mecha_1002_101d_show_ske.dbbin");
	//factory->loadTextureAtlasData("mecha_1002_101d_show/mecha_1002_101d_show_tex.json");
	//const auto armatureDisplay = factory->buildArmatureDisplay("mecha_1002_101d", "mecha_1002_101d_show");
	//armatureDisplay->getAnimation()->play("idle");

	//armatureDisplay->setPosition(0.0f, -200.0f);
	//addChild(armatureDisplay);

	factory->loadDragonBonesData("skeleton_ske.json");
	factory->loadTextureAtlasData("skeleton_tex.json");
	const auto armatureDisplay = factory->buildArmatureDisplay("Win");
	bgImage->addChild(armatureDisplay);
	armatureDisplay->setPosition(ccp(this->bgImage->getContentSize().width/2, this->bgImage->getContentSize().height/2));
	armatureDisplay->getAnimation()->play();
	armatureDisplay->getEventDispatcher()->setEnabled(true);

	return true;
}

void CongratDialog::startDialog(PlayScene *parent)
{
	this->playLayer = parent;

	if (this->getParent() != NULL) {
		this->_removeFromParent();
	}
	SceneManager::getInstance()->currentScene->addChild(this, LAYER_DIALOG);
}

void CongratDialog::_removeFromParent()
{
	BasePopupDialog::_removeFromParent();
}

void CongratDialog::setCallBackFunc(CCCallFunc *callBackFunc)
{

}

void CongratDialog::onContinue(Ref *obj)
{
	this->closeDialog();
}

void CongratDialog::onShare(Ref *obj)
{

}

CongratDialog *congratDialogInstance = NULL;
CongratDialog *CongratDialog::getInstance()
{
	if (congratDialogInstance == NULL){
		congratDialogInstance = CongratDialog::create();
		congratDialogInstance->retain();
	}
	return congratDialogInstance;
}

void CongratDialog::destroyInstance()
{
	if (congratDialogInstance != NULL){
		congratDialogInstance->release();
		congratDialogInstance = NULL;
	}
}

