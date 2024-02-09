#include "texture.h"
#include "color.h"

#include <assert.h>
#include <iostream>
#include <algorithm>

using namespace std;

namespace CS248 {

inline void uint8_to_float( float dst[4], const unsigned char* src ) {
  uint8_t* src_uint8 = (uint8_t *)src;
  dst[0] = src_uint8[0] / 255.f;
  dst[1] = src_uint8[1] / 255.f;
  dst[2] = src_uint8[2] / 255.f;
  dst[3] = src_uint8[3] / 255.f;
}

inline void float_to_uint8( unsigned char* dst, float src[4] ) {
  uint8_t* dst_uint8 = (uint8_t *)dst;
  dst_uint8[0] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[0])));
  dst_uint8[1] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[1])));
  dst_uint8[2] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[2])));
  dst_uint8[3] = (uint8_t) ( 255.f * max( 0.0f, min( 1.0f, src[3])));
}

void Sampler2DImp::generate_mips(Texture& tex, int startLevel) {

  // NOTE: 
  // This starter code allocates the mip levels and generates a level 
  // map by filling each level with placeholder data in the form of a 
  // color that differs from its neighbours'. You should instead fill
  // with the correct data!

  // Advanced Task
  // Implement mipmap for trilinear filtering

  // check start level
  if ( startLevel >= tex.mipmap.size() ) {
    std::cerr << "Invalid start level"; 
  }

  // allocate sublevels
  int baseWidth  = tex.mipmap[startLevel].width;
  int baseHeight = tex.mipmap[startLevel].height;
  int numSubLevels = (int)(log2f( (float)max(baseWidth, baseHeight)));

  numSubLevels = min(numSubLevels, kMaxMipLevels - startLevel - 1);
  tex.mipmap.resize(startLevel + numSubLevels + 1);

  int width  = baseWidth;
  int height = baseHeight;
  for (int i = 1; i <= numSubLevels; i++) {

    MipLevel& level = tex.mipmap[startLevel + i];

    // handle odd size texture by rounding down
    width  = max( 1, width  / 2); assert(width  > 0);
    height = max( 1, height / 2); assert(height > 0);

    level.width = width;
    level.height = height;
    level.texels = vector<unsigned char>(4 * width * height);

  }

  // fill all 0 sub levels with interchanging colors
  Color colors[3] = { Color(1,0,0,1), Color(0,1,0,1), Color(0,0,1,1) };
  for(size_t i = 1; i < tex.mipmap.size(); ++i) {

    Color c = colors[i % 3];
    MipLevel& mip = tex.mipmap[i];

    for(size_t i = 0; i < 4 * mip.width * mip.height; i += 4) {
      float_to_uint8( &mip.texels[i], &c.r );
    }
  }

}

Color Sampler2DImp::sample_nearest(Texture& tex, 
                                   float u, float v, 
                                   int level) {

  // Task 4: Implement nearest neighbour interpolation
  
  // return magenta for invalid level
  return Color(1,0,1,1);

}

Color Sampler2DImp::sample_bilinear(Texture& tex, 
                                    float u, float v, 
                                    int level) {
  
  // Task 4: Implement bilinear filtering
  level = 0;
  size_t width = tex.mipmap[level].width;
  size_t height = tex.mipmap[level].height;
  // Convert u, v into texture space coordinates
  float x = u * width;
  float y = v * height;
  int x0 = static_cast<int>(floor(x - 0.5f));
  int y0 = static_cast<int>(floor(y - 0.5f));
  float u_ratio = x - (x0 + 0.5f);
  float v_ratio = y - (y0 + 0.5f);
  int x1 = x0 + 1;
  int y1 = y0 + 1;
  // four texel values
  Color c00 = get_texel(tex, level, x0, y0);
  Color c10 = get_texel(tex, level, x1, y0);
  Color c01 = get_texel(tex, level, x0, y1);
  Color c11 = get_texel(tex, level, x1, y1);
  Color interpolated_color;
  interpolated_color.r = bilinear_interpolate(c00.r, c10.r, c01.r, c11.r, u_ratio, v_ratio);
  interpolated_color.g = bilinear_interpolate(c00.g, c10.g, c01.g, c11.g, u_ratio, v_ratio);
  interpolated_color.b = bilinear_interpolate(c00.b, c10.b, c01.b, c11.b, u_ratio, v_ratio);
  interpolated_color.a = bilinear_interpolate(c00.a, c10.a, c01.a, c11.a, u_ratio, v_ratio);

  return interpolated_color;
  // return magenta for invalid level
  // return Color(1,0,1,1);

}

Color Sampler2DImp::get_texel(const Texture& tex, int level, int x, int y) {
  const MipLevel& mip = tex.mipmap[level];
  // x and y to be within the texture bounds
  x = std::max(0, std::min(x, (int)mip.width - 1));
  y = std::max(0, std::min(y, (int)mip.height - 1));
  int index = 4 * (x + y * mip.width);
  float color[4];
  uint8_to_float(color, &mip.texels[index]);

  return Color(color[0], color[1], color[2], color[3]);
}

float Sampler2DImp::bilinear_interpolate(float c00, float c10, float c01, float c11, float u_ratio, float v_ratio) {
  float u_opposite = 1 - u_ratio;
  float v_opposite = 1 - v_ratio;

  // Interpolate between the four corner texels
  return (c00 * u_opposite + c10 * u_ratio) * v_opposite +
         (c01 * u_opposite + c11 * u_ratio) * v_ratio;

}

Color Sampler2DImp::sample_trilinear(Texture& tex, 
                                     float u, float v, 
                                     float u_scale, float v_scale) {

  // Advanced Task
  // Implement trilinear filtering

  // return magenta for invalid level
  return Color(1,0,1,1);

}

} // namespace CS248
