#include "texture.h"
#include "CGL/color.h"

#include <cmath>
#include <algorithm>

namespace CGL {

  Color Texture::sample(const SampleParams& sp) {
    // TODO: Task 6: Fill this in.
      Color color;
      // Get minmap lv based on change in the uv coordinates in pixels.
      float level = get_level(sp);
      // Determine the sample by switching lv sampling method
      switch (sp.lsm) {
              case L_ZERO: {
                  // Sampled  highest resolution texture
                  if (sp.psm == P_NEAREST) {
                      // For faster result
                      color = sample_nearest(sp.p_uv, 0);
                  } else if (sp.psm == P_LINEAR) {
                      // For smoother results
                      color = sample_bilinear(sp.p_uv, 0);
                  }
                  break;
              }
              case L_NEAREST: {
                  level = round(level);
                  if (sp.psm == P_NEAREST) {
                      // Nearest neighbor sampling at the rounded mipmap level.
                      color = sample_nearest(sp.p_uv, static_cast<int>(level));
                  } else if (sp.psm == P_LINEAR) {
                      // Nearest Bilinear sampling at the rounded mipmap level.
                      color = sample_bilinear(sp.p_uv, static_cast<int>(level));
                  }
                  break;
              }
              case L_LINEAR: {
                  // Calculate the lower and upper mipmap levels for interpolation and the blend factor
                  int lower_level = static_cast<int>(floor(level));
                  int upper_level = static_cast<int>(ceil(level));
                  float blend = level - lower_level;
                  Color color_lower, color_upper;
                  
                  if (sp.psm == P_NEAREST) {
                      color_lower = sample_nearest(sp.p_uv, lower_level);
                      color_upper = sample_nearest(sp.p_uv, upper_level);
                  } else if (sp.psm == P_LINEAR) {
                      color_lower = sample_bilinear(sp.p_uv, lower_level);
                      color_upper = sample_bilinear(sp.p_uv, upper_level);
                  }
                  // Linearly interpolate between the two colors
                  color = color_lower * (1 - blend) + color_upper * blend;
                  break;
              }
              default: {
                  std::cerr << "Error" << std::endl;
                  exit(EXIT_FAILURE);
              }
          }
          // Return final sample color
          return color;
  }

  float Texture::get_level(const SampleParams& sp) {
    // TODO: Task 6: Fill this in.
    // Get the rate of change of the texture coordinates
    Vector2D duvdx = sp.p_dx_uv;
    Vector2D duvdy = sp.p_dy_uv;

    // Scale the coordinates by the dimension to get the rate of change per pixel
    duvdx.x *= width;
    duvdy.y *= height;

    // Calculate the length
    float len_duvdx = sqrt(duvdx.x * duvdx.x + duvdx.y * duvdx.y);
    float len_duvdy = sqrt(duvdy.x * duvdy.x + duvdy.y * duvdy.y);

    // Choose the max rate of change in U or V to compute level
    float max_duv_len = std::max(len_duvdx, len_duvdy);

    // Calculate the mipmap level by Log2ing it.
    float level = log2(max_duv_len);

    // Ensure the lv doesnt exceed bounds of available mipmap lvs.
    level = std::max(0.0f, std::min(level, static_cast<float>(mipmap.size() - 1)));
      
    return level;
  }

  Color MipLevel::get_texel(int tx, int ty) {
    return Color(&texels[tx * 3 + ty * width * 3]);
  }

  Color Texture::sample_nearest(Vector2D uv, int level) {
    // TODO: Task 5: Fill this in.
    if (level < 0) {
        return Color(1, 0, 1);    // return magenta for invalid level
    }
      
    auto& mip = mipmap[level];
    int x = uv.x * mip.width;
    int y = uv.y * mip.height;
      
    return mip.get_texel(x, y);
  }

  Color Texture::sample_bilinear(Vector2D uv, int level) {
    // TODO: Task 5: Fill this in.
    if (level < 0) {
        return Color(1, 0, 1);    // return magenta for invalid level
    }
      
    auto& mip = mipmap[level];
    // Get the red dot coordinate
    float u = uv.x * mip.width;
    float v = uv.y * mip.height;
      
    // Surrounding coordinates
    int x0 = static_cast<int>(floor(u));
    int x1 = x0 + 1;
    int y0 = static_cast<int>(floor(v));
    int y1 = y0 + 1;
    
    float s = u - x0;
    float t = v - y1;
    
    Color u00 = mip.get_texel(x0, y0);
    Color u01 = mip.get_texel(x0, y1);
    Color u10 = mip.get_texel(x1, y0);
    Color u11 = mip.get_texel(x1, y1);
      
    // lerp
    Color u0 = u00 + s * Color(u10.r - u00.r, u10.g - u00.g, u10.b - u00.b);
    Color u1 = u01 + s * Color(u11.r - u01.r, u11.g - u01.g, u11.b - u01.b);

    return u0 + t * Color(u1.r - u0.r, u1.g - u0.g, u1.b - u0.b);
  }



  /****************************************************************************/

  // Helpers

  inline void uint8_to_float(float dst[3], unsigned char* src) {
    uint8_t* src_uint8 = (uint8_t*)src;
    dst[0] = src_uint8[0] / 255.f;
    dst[1] = src_uint8[1] / 255.f;
    dst[2] = src_uint8[2] / 255.f;
  }

  inline void float_to_uint8(unsigned char* dst, float src[3]) {
    uint8_t* dst_uint8 = (uint8_t*)dst;
    dst_uint8[0] = (uint8_t)(255.f * max(0.0f, min(1.0f, src[0])));
    dst_uint8[1] = (uint8_t)(255.f * max(0.0f, min(1.0f, src[1])));
    dst_uint8[2] = (uint8_t)(255.f * max(0.0f, min(1.0f, src[2])));
  }

  void Texture::generate_mips(int startLevel) {

    // make sure there's a valid texture
    if (startLevel >= mipmap.size()) {
      std::cerr << "Invalid start level";
    }

    // allocate sublevels
    int baseWidth = mipmap[startLevel].width;
    int baseHeight = mipmap[startLevel].height;
    int numSubLevels = (int)(log2f((float)max(baseWidth, baseHeight)));

    numSubLevels = min(numSubLevels, kMaxMipLevels - startLevel - 1);
    mipmap.resize(startLevel + numSubLevels + 1);

    int width = baseWidth;
    int height = baseHeight;
    for (int i = 1; i <= numSubLevels; i++) {

      MipLevel& level = mipmap[startLevel + i];

      // handle odd size texture by rounding down
      width = max(1, width / 2);
      //assert (width > 0);
      height = max(1, height / 2);
      //assert (height > 0);

      level.width = width;
      level.height = height;
      level.texels = vector<unsigned char>(3 * width * height);
    }

    // create mips
    int subLevels = numSubLevels - (startLevel + 1);
    for (int mipLevel = startLevel + 1; mipLevel < startLevel + subLevels + 1;
      mipLevel++) {

      MipLevel& prevLevel = mipmap[mipLevel - 1];
      MipLevel& currLevel = mipmap[mipLevel];

      int prevLevelPitch = prevLevel.width * 3; // 32 bit RGB
      int currLevelPitch = currLevel.width * 3; // 32 bit RGB

      unsigned char* prevLevelMem;
      unsigned char* currLevelMem;

      currLevelMem = (unsigned char*)&currLevel.texels[0];
      prevLevelMem = (unsigned char*)&prevLevel.texels[0];

      float wDecimal, wNorm, wWeight[3];
      int wSupport;
      float hDecimal, hNorm, hWeight[3];
      int hSupport;

      float result[3];
      float input[3];

      // conditional differentiates no rounding case from round down case
      if (prevLevel.width & 1) {
        wSupport = 3;
        wDecimal = 1.0f / (float)currLevel.width;
      }
      else {
        wSupport = 2;
        wDecimal = 0.0f;
      }

      // conditional differentiates no rounding case from round down case
      if (prevLevel.height & 1) {
        hSupport = 3;
        hDecimal = 1.0f / (float)currLevel.height;
      }
      else {
        hSupport = 2;
        hDecimal = 0.0f;
      }

      wNorm = 1.0f / (2.0f + wDecimal);
      hNorm = 1.0f / (2.0f + hDecimal);

      // case 1: reduction only in horizontal size (vertical size is 1)
      if (currLevel.height == prevLevel.height) {
        //assert (currLevel.height == 1);

        for (int i = 0; i < currLevel.width; i++) {
          wWeight[0] = wNorm * (1.0f - wDecimal * i);
          wWeight[1] = wNorm * 1.0f;
          wWeight[2] = wNorm * wDecimal * (i + 1);

          result[0] = result[1] = result[2] = 0.0f;

          for (int ii = 0; ii < wSupport; ii++) {
            uint8_to_float(input, prevLevelMem + 3 * (2 * i + ii));
            result[0] += wWeight[ii] * input[0];
            result[1] += wWeight[ii] * input[1];
            result[2] += wWeight[ii] * input[2];
          }

          // convert back to format of the texture
          float_to_uint8(currLevelMem + (3 * i), result);
        }

        // case 2: reduction only in vertical size (horizontal size is 1)
      }
      else if (currLevel.width == prevLevel.width) {
        //assert (currLevel.width == 1);

        for (int j = 0; j < currLevel.height; j++) {
          hWeight[0] = hNorm * (1.0f - hDecimal * j);
          hWeight[1] = hNorm;
          hWeight[2] = hNorm * hDecimal * (j + 1);

          result[0] = result[1] = result[2] = 0.0f;
          for (int jj = 0; jj < hSupport; jj++) {
            uint8_to_float(input, prevLevelMem + prevLevelPitch * (2 * j + jj));
            result[0] += hWeight[jj] * input[0];
            result[1] += hWeight[jj] * input[1];
            result[2] += hWeight[jj] * input[2];
          }

          // convert back to format of the texture
          float_to_uint8(currLevelMem + (currLevelPitch * j), result);
        }

        // case 3: reduction in both horizontal and vertical size
      }
      else {

        for (int j = 0; j < currLevel.height; j++) {
          hWeight[0] = hNorm * (1.0f - hDecimal * j);
          hWeight[1] = hNorm;
          hWeight[2] = hNorm * hDecimal * (j + 1);

          for (int i = 0; i < currLevel.width; i++) {
            wWeight[0] = wNorm * (1.0f - wDecimal * i);
            wWeight[1] = wNorm * 1.0f;
            wWeight[2] = wNorm * wDecimal * (i + 1);

            result[0] = result[1] = result[2] = 0.0f;

            // convolve source image with a trapezoidal filter.
            // in the case of no rounding this is just a box filter of width 2.
            // in the general case, the support region is 3x3.
            for (int jj = 0; jj < hSupport; jj++)
              for (int ii = 0; ii < wSupport; ii++) {
                float weight = hWeight[jj] * wWeight[ii];
                uint8_to_float(input, prevLevelMem +
                  prevLevelPitch * (2 * j + jj) +
                  3 * (2 * i + ii));
                result[0] += weight * input[0];
                result[1] += weight * input[1];
                result[2] += weight * input[2];
              }

            // convert back to format of the texture
            float_to_uint8(currLevelMem + currLevelPitch * j + 3 * i, result);
          }
        }
      }
    }
  }

}
