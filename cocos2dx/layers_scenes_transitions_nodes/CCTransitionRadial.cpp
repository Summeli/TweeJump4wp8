/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* Copyright (c) 2010-2011 cocos2d-x.org
* Copyright (c) 2009      Lam Pham
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "pch.h"

#include "CCTransitionRadial.h"
#include "CCDirector.h"
#include "CCRenderTexture.h"
#include "CCActionInstant.h"
#include "CCActionProgressTimer.h"
#include "CCPointExtension.h"

namespace   cocos2d {

//#import "CCDirector.h"
//#import "CCRadialTransition.h"
//#import "CCRenderTexture.h"
//#import "CCLayer.h"
//#import "CCInstantAction.h"
//#import "Support/CCPointExtension.h"

enum {
	kSceneRadial = 0xc001,
};

void CCTransitionRadialCCW::sceneOrder()
{
	m_bIsInSceneOnTop = false;
}

CCProgressTimerType CCTransitionRadialCCW::radialType()
{
	return kCCProgressTimerTypeRadialCCW;
}

void CCTransitionRadialCCW::onEnter()
{
	CCTransitionScene::onEnter();
	// create a transparent color layer
	// in which we are going to add our rendertextures
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// create the second render texture for outScene
	CCRenderTexture *outTexture = CCRenderTexture::renderTextureWithWidthAndHeight((int)size.width, (int)size.height);

	if (NULL == outTexture)
	{
		return;
	}
	
	outTexture->getSprite()->setAnchorPoint(ccp(0.5f,0.5f));
	outTexture->setPosition(ccp(size.width/2, size.height/2));
	outTexture->setAnchorPoint(ccp(0.5f,0.5f));

	// render outScene to its texturebuffer
	outTexture->clear(0,0,0,1);
	outTexture->begin();
	m_pOutScene->visit();
	outTexture->end();

	//	Since we've passed the outScene to the texture we don't need it.
	this->hideOutShowIn();

	//	We need the texture in RenderTexture.
	CCProgressTimer *outNode = CCProgressTimer::progressWithTexture(outTexture->getSprite()->getTexture());
	// but it's flipped upside down so we flip the sprite
	outNode->getSprite()->setFlipY(true);
	//	Return the radial type that we want to use
	outNode->setType(radialType());
	outNode->setPercentage(100.f);
	outNode->setPosition(ccp(size.width/2, size.height/2));
	outNode->setAnchorPoint(ccp(0.5f,0.5f));

	// create the blend action
	CCAction * layerAction = CCSequence::actions
	(
		CCProgressFromTo::actionWithDuration(m_fDuration, 100.0f, 0.0f),
		CCCallFunc::actionWithTarget(this, callfunc_selector(CCTransitionScene::finish)),
		NULL
	);
	// run the blend action
	outNode->runAction(layerAction);

	// add the layer (which contains our two rendertextures) to the scene
	this->addChild(outNode, 2, kSceneRadial);
}


// clean up on exit
void CCTransitionRadialCCW::onExit()
{
	// remove our layer and release all containing objects 
	this->removeChildByTag(kSceneRadial, false);
	CCTransitionScene::onExit();
}

CCTransitionRadialCCW* CCTransitionRadialCCW::transitionWithDuration(ccTime t, CCScene* scene)
{
    CCTransitionRadialCCW* pScene = new CCTransitionRadialCCW();
    pScene->initWithDuration(t, scene);
    pScene->autorelease();

    return pScene;
}

CCProgressTimerType CCTransitionRadialCW::radialType()
{
	return kCCProgressTimerTypeRadialCW;
}

CCTransitionRadialCW* CCTransitionRadialCW::transitionWithDuration(ccTime t, CCScene* scene)
{
    CCTransitionRadialCW* pScene = new CCTransitionRadialCW();
    pScene->initWithDuration(t, scene);
    pScene->autorelease();

    return pScene;
}

}//namespace   cocos2d 
