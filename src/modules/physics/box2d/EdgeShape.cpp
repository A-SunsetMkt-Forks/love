/**
 * Copyright (c) 2006-2025 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#include "EdgeShape.h"

// Module
#include "Body.h"
#include "World.h"
#include "Physics.h"

namespace love
{
namespace physics
{
namespace box2d
{

love::Type EdgeShape::type("EdgeShape", &Shape::type);

EdgeShape::EdgeShape(Body *body, const b2EdgeShape &e)
	: Shape(body, e)
{
}

EdgeShape::~EdgeShape()
{
}

void EdgeShape::setNextVertex(float x, float y)
{
	throwIfShapeNotValid();
	b2EdgeShape *e = (b2EdgeShape *)shape;
	b2Vec2 v(x, y);
	e->m_vertex3 = Physics::scaleDown(v);
	e->m_oneSided = true;
}

b2Vec2 EdgeShape::getNextVertex() const
{
	throwIfShapeNotValid();
	b2EdgeShape *e = (b2EdgeShape *)shape;
	return Physics::scaleUp(e->m_vertex3);
}

void EdgeShape::setPreviousVertex(float x, float y)
{
	throwIfShapeNotValid();
	b2EdgeShape *e = (b2EdgeShape *)shape;
	b2Vec2 v(x, y);
	e->m_vertex0 = Physics::scaleDown(v);
	e->m_oneSided = true;
}

b2Vec2 EdgeShape::getPreviousVertex() const
{
	throwIfShapeNotValid();
	b2EdgeShape *e = (b2EdgeShape *)shape;
	return Physics::scaleUp(e->m_vertex0);
}

int EdgeShape::getPoints(lua_State *L)
{
	throwIfShapeNotValid();
	b2EdgeShape *e = (b2EdgeShape *)shape;
	b2Vec2 v1 = Physics::scaleUp(e->m_vertex1);
	b2Vec2 v2 = Physics::scaleUp(e->m_vertex2);
	lua_pushnumber(L, v1.x);
	lua_pushnumber(L, v1.y);
	lua_pushnumber(L, v2.x);
	lua_pushnumber(L, v2.y);
	return 4;

}

} // box2d
} // physics
} // love
