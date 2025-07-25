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

#include "wrap_Sound.h"

#include "filesystem/wrap_Filesystem.h"
#include "data/DataStream.h"

// Implementations.
#include "lullaby/Sound.h"

namespace love
{
namespace sound
{

#define instance() (Module::getInstance<Sound>(Module::M_SOUND))

int w_newDecoder(lua_State *L)
{
	int bufferSize = (int)luaL_optinteger(L, 2, Decoder::DEFAULT_BUFFER_SIZE);
	love::Stream *stream = nullptr;

	if (love::filesystem::luax_cangetfile(L, 1))
	{
		Decoder::StreamSource source = Decoder::STREAM_FILE;

		const char* sourcestr = lua_isnoneornil(L, 3) ? nullptr : luaL_checkstring(L, 3);
		if (sourcestr != nullptr && !Decoder::getConstant(sourcestr, source))
			return luax_enumerror(L, "stream type", Decoder::getConstants(source), sourcestr);

		if (source == Decoder::STREAM_FILE)
		{
			auto file = love::filesystem::luax_getfile(L, 1);
			luax_catchexcept(L, [&]() { file->open(love::filesystem::File::MODE_READ); });
			stream = file;
		}
		else
		{
			luax_catchexcept(L, [&]()
			{
				StrongRef<love::filesystem::FileData> data(love::filesystem::luax_getfiledata(L, 1), Acquire::NORETAIN);
				stream = new data::DataStream(data);
			});
		}

	}
	else if (luax_istype(L, 1, Data::type))
	{
		Data *data = luax_checktype<Data>(L, 1);
		luax_catchexcept(L, [&]() { stream = new data::DataStream(data); });
	}
	else
	{
		stream = luax_checktype<Stream>(L, 1);
		stream->retain();
	}	

	Decoder *t = nullptr;
	luax_catchexcept(L,
		[&]() { t = instance()->newDecoder(stream, bufferSize); },
		[&](bool) { stream->release(); }
	);

	luax_pushtype(L, t);
	t->release();
	return 1;
}

int w_newSoundData(lua_State *L)
{
	SoundData *t = nullptr;

	if (lua_isnumber(L, 1))
	{
		int samples = (int) luaL_checkinteger(L, 1);
		int sampleRate = (int) luaL_optinteger(L, 2, Decoder::DEFAULT_SAMPLE_RATE);
		int bitDepth = (int) luaL_optinteger(L, 3, Decoder::DEFAULT_BIT_DEPTH);
		int channels = (int) luaL_optinteger(L, 4, Decoder::DEFAULT_CHANNELS);

		luax_catchexcept(L, [&](){ t = instance()->newSoundData(samples, sampleRate, bitDepth, channels); });
	}
	// Must be string or decoder.
	else
	{
		// Convert to Decoder, if necessary.
		if (!luax_istype(L, 1, Decoder::type))
		{
			w_newDecoder(L);
			lua_replace(L, 1);
		}

		luax_catchexcept(L, [&](){ t = instance()->newSoundData(luax_checkdecoder(L, 1)); });
	}

	luax_pushtype(L, t);
	t->release();
	return 1;
}

// List of functions to wrap.
static const luaL_Reg functions[] =
{
	{ "newDecoder",  w_newDecoder },
	{ "newSoundData",  w_newSoundData },
	{ 0, 0 }
};

static const lua_CFunction types[] =
{
	luaopen_sounddata,
	luaopen_decoder,
	0
};

extern "C" int luaopen_love_sound(lua_State *L)
{
	Sound *instance = instance();
	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new lullaby::Sound(); });
	}
	else
		instance->retain();


	WrappedModule w;
	w.module = instance;
	w.name = "sound";
	w.type = &Sound::type;
	w.functions = functions;
	w.types = types;

	return luax_register_module(L, w);
}

} // sound
} // love
