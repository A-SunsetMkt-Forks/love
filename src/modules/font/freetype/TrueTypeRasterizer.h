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

#ifndef LOVE_FONT_FREETYPE_TRUE_TYPE_RASTERIZER_H
#define LOVE_FONT_FREETYPE_TRUE_TYPE_RASTERIZER_H

// LOVE
#include "filesystem/FileData.h"
#include "font/TrueTypeRasterizer.h"

// FreeType2
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace love
{
namespace font
{
namespace freetype
{

/**
 * Holds data for a font object.
 **/
class TrueTypeRasterizer : public love::font::TrueTypeRasterizer
{
public:

	TrueTypeRasterizer(FT_Library library, love::Data *data, int size, const Settings &settings, float defaultdpiscale);
	virtual ~TrueTypeRasterizer();

	// Implement Rasterizer
	int getLineHeight() const override;
	int getGlyphSpacing(uint32 glyph) const override;
	int getGlyphIndex(uint32 glyph) const override;
	GlyphData *getGlyphDataForIndex(int index) const override;
	int getGlyphCount() const override;
	bool hasGlyph(uint32 glyph) const override;
	float getKerning(uint32 leftglyph, uint32 rightglyph) const override;
	DataType getDataType() const override;
	TextShaper *newTextShaper() override;

	ptrdiff_t getHandle() const override { return (ptrdiff_t) face; }

	static bool accepts(FT_Library library, love::Data *data);

private:

	static FT_UInt hintingToLoadOption(Hinting hinting);

	// TrueType face
	FT_Face face;

	// Font data
	StrongRef<love::Data> data;

	Hinting hinting;

}; // TrueTypeRasterizer

} // freetype
} // font
} // love

#endif // LOVE_FONT_FREETYPE_TRUE_TYPE_RASTERIZER_H
