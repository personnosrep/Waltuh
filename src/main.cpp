#include <Geode/Geode.hpp>
#include <cocos2d.h>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCMenuItem.hpp>
#include <Geode/modify/CCDirector.hpp>
using namespace geode::prelude;

//summons him
//how did i do this i dont even know cpp
cocos2d::CCSprite* waltuh(float fin = 0.5f, float fout = 0.25f, float waitt = 0.0f, float targetOpacity = 255.0f) {
    auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    auto overlay = cocos2d::CCSprite::create("waltuh.png"_spr);

    if (overlay) {
        overlay->setPosition({ winSize.width / 2, winSize.height / 2 });

        // Stretch Walter to fit the screen. He’s gotta fill your life with joy
        float scaleX = winSize.width / overlay->getContentSize().width;
        float scaleY = winSize.height / overlay->getContentSize().height;
        overlay->setScale(winSize.width > winSize.height ? scaleX : scaleY);

        // Set opacity to zero if he's fading in. Otherwise, just materialize
        overlay->setOpacity(fin > 0 ? 0 : static_cast<GLubyte>(targetOpacity));
        cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(overlay, 1000);

        // walter's dramatic enterance and just as dramatic exit
        auto fadeIn = cocos2d::CCFadeTo::create(fin, targetOpacity);
        auto wait = cocos2d::CCDelayTime::create(waitt); 
        auto fadeOut = cocos2d::CCFadeTo::create(fout, 0); // He leaves when he's dissapointed

        auto sequence = cocos2d::CCSequence::create(fadeIn, wait, fadeOut, nullptr);
        overlay->runAction(sequence);
    }

    return overlay;
}

// make him stay there don't want him escaping the basement
class $modify(CCDirector) {
    void drawScene() {
        CCDirector::drawScene();

        auto scene = CCDirector::sharedDirector()->getRunningScene();

        if (scene && !scene->getChildByTag(42069)) {
            auto ghost = waltuh(0, 0, 9999999*69420, 4); 
            if (ghost) ghost->setTag(42069); // He’s tagged, so he only appears once and never leaves
        }
    }
};

// The father figure you never had
class $modify(CCMenuItem) {
    void activate() {
        CCMenuItem::activate();
        waltuh(0.25f, 0.5f); 
    }
};


class $modify(PlayLayer) {
    void levelComplete() {
        PlayLayer::levelComplete();
        waltuh(0.5f, 1.0f, 0.5f); // Maybe a little "well done" from Heisenberg, but not too much
    }
};

class $modify(PlayerObject) {
    void playDeathEffect() {
        PlayerObject::playDeathEffect();
        waltuh(0, 0.25f); // He ain't mad, just dissapointed
    }
};
