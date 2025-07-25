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

#include "PolygonShape.h"

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

love::Type PolygonShape::type("PolygonShape", &Shape::type);

PolygonShape::PolygonShape(Body *body, const b2PolygonShape &p)
	: Shape(body, p)
{
}

PolygonShape::~PolygonShape()
{
}

int PolygonShape::getPoints(lua_State *L)
{
	throwIfShapeNotValid();
	love::luax_assert_argc(L, 0);
	b2PolygonShape *p = (b2PolygonShape *)shape;
	int count = p->m_count;
	for (int i = 0; i<count; i++)
	{
		b2Vec2 v = Physics::scaleUp(p->m_vertices[i]);
		lua_pushnumber(L, v.x);
		lua_pushnumber(L, v.y);
	}
	return count*2;
}

bool PolygonShape::validate() const
{
	throwIfShapeNotValid();
	b2PolygonShape *p = (b2PolygonShape *)shape;
	return p->Validate();
}

} // box2d
} // physics
} // love
