/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
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

#include <Box2D/Dynamics/Contacts/b2CircleContact.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Common/b2BlockAllocator.h>
#include <Box2D/Collision/b2TimeOfImpact.h>

#include <new>
using namespace std;

b2Contact* b2CircleContact::Create(b2Fixture* fixtureA, int32, b2Fixture* fixtureB, int32, b2BlockAllocator* allocator)
{
	void* mem = allocator->Allocate(sizeof(b2CircleContact));
	return new (mem) b2CircleContact(fixtureA, fixtureB);
}

void b2CircleContact::Destroy(b2Contact* contact, b2BlockAllocator* allocator)
{
	((b2CircleContact*)contact)->~b2CircleContact();
	allocator->Free(contact, sizeof(b2CircleContact));
}

b2CircleContact::b2CircleContact(b2Fixture* fixtureA, b2Fixture* fixtureB)
	: b2Contact(fixtureA, 0, fixtureB, 0)
{
	b2Assert(m_fixtureA->GetType() == b2Shape::e_circle);
	b2Assert(m_fixtureB->GetType() == b2Shape::e_circle);
}

void b2CircleContact::Evaluate(b2Manifold* manifold, const b2Transform& xfA, const b2Transform& xfB)
{
	b2CollideCircles(manifold,
					(b2CircleShape*)m_fixtureA->GetShape(), xfA,
					(b2CircleShape*)m_fixtureB->GetShape(), xfB);
}
