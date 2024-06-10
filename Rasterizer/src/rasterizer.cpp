#include "rasterizer.h"
#include <stdio.h>

using namespace std;

namespace CGL {

  RasterizerImp::RasterizerImp(PixelSampleMethod psm, LevelSampleMethod lsm,
    size_t width, size_t height,
    unsigned int sample_rate) {
    this->psm = psm;
    this->lsm = lsm;
    this->width = width;
    this->height = height;
    this->sample_rate = sample_rate;

    sample_buffer.resize(width * height * sample_rate, Color::White);
  }

  // Used by rasterize_point and rasterize_line
  void RasterizerImp::fill_pixel(size_t x, size_t y, Color c) {
    // TODO: Task 2: You might need to this function to fix points and lines (such as the black rectangle border in test4.svg)
    // NOTE: You are not required to implement proper supersampling for points and lines
    // It is sufficient to use the same color for all supersamples of a pixel for points and lines (not triangles)
      
    // Check if coordinates within the bounds
    if (x < width && y < height) {
        // Num of samples along each side
        unsigned int samples_per_side = std::sqrt(sample_rate);
        
        unsigned int buffer_width = width * samples_per_side;
        // unsigned int buffer_height = height * samples_per_side;

        // Calculate the start indices in the supersamplebuffer
        size_t startX = samples_per_side * x;
        size_t startY = samples_per_side * y;

        // Fill all supersamples with the color c
        for (size_t sx = 0; sx < samples_per_side; sx++) {
            for (size_t sy = 0; sy < samples_per_side; sy++) {
                size_t index = (startY + sy) * buffer_width + (startX + sx);
                sample_buffer[index] = c;
                //sample_buffer[y * width + x] = c;
            }
        }
    }
  }

  // Rasterize a point: simple example to help you start familiarizing
  // yourself with the starter code.
  //
  void RasterizerImp::rasterize_point(float x, float y, Color color) {
    // fill in the nearest pixel
    int sx = (int)floor(x);
    int sy = (int)floor(y);

    // check bounds
    if (sx < 0 || sx >= width) return;
    if (sy < 0 || sy >= height) return;

    fill_pixel(sx, sy, color);
    return;
  }

  // Rasterize a line.
  void RasterizerImp::rasterize_line(float x0, float y0,
    float x1, float y1,
    Color color) {
    if (x0 > x1) {
      swap(x0, x1); swap(y0, y1);
    }

    float pt[] = { x0,y0 };
    float m = (y1 - y0) / (x1 - x0);
    float dpt[] = { 1,m };
    int steep = abs(m) > 1;
    if (steep) {
      dpt[0] = x1 == x0 ? 0 : 1 / abs(m);
      dpt[1] = x1 == x0 ? (y1 - y0) / abs(y1 - y0) : m / abs(m);
    }

    while (floor(pt[0]) <= floor(x1) && abs(pt[1] - y0) <= abs(y1 - y0)) {
      rasterize_point(pt[0], pt[1], color);
      pt[0] += dpt[0]; pt[1] += dpt[1];
    }
  }

  // Rasterize a triangle.
  void RasterizerImp::rasterize_triangle(float x0, float y0,
    float x1, float y1,
    float x2, float y2,
    Color color) {
    // TODO: Task 1: Implement basic triangle rasterization here, no supersampling
      float min_x = std::min({x0, x1, x2});
      float max_x = std::max({x0, x1, x2});
      float min_y = std::min({y0, y1, y2});
      float max_y = std::max({y0, y1, y2});
      
      // Setting up for supersampling
      unsigned int samples_per_side = std::sqrt(sample_rate);
      unsigned int buffer_width = width * samples_per_side;
      unsigned int buffer_height = height * samples_per_side;
      
      // Sampling over the bounding box at the supersampled resolution
      for (int x = (int)min_x; x <= (int)max_x; x++) {
          for (int y = (int)min_y; y <= (int)max_y; y++) {
              for (unsigned int sx = 0; sx < samples_per_side; sx++) {
                  for (unsigned int sy = 0; sy < samples_per_side; sy++) {
                      // Center of the pixel supersample's center coordinates
                      float px = x + (sx + 0.5f) / samples_per_side;
                      float py = y + (sy + 0.5f) / samples_per_side;
                      // Point-in-triangle test: uses barycentric coordinates to determine if a point is inside the triangle. Barycentric coordinates are always non-negative for points inside the triangle, regardless of the winding order of the vertices.
                      float alpha = (-(px-x1)*(y2-y1) + (py-y1)*(x2-x1)) / (-(x0-x1)*(y2-y1) + (y0-y1) * (x2-x1));
                      float beta = (-(px-x2)*(y0-y2) + (py-y2)*(x0-x2)) / (-(x1-x2)*(y0-y2) + (y1-y2) * (x0-x2));
                      float gamma = 1-alpha-beta;
                      if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                          int bufferX = (int)(x * samples_per_side + sx);
                          int bufferY = (int)(y * samples_per_side + sy);
                          // Ensure supersamples index within bounds of ss buffer
                          if (bufferX >= 0 && bufferX < buffer_width && bufferY >= 0 && bufferY < buffer_height) {
                              int index = bufferY * buffer_width + bufferX;
                              // Fill supersample in the sample_buffer
                              sample_buffer[index] = color;
                          }
                          /*if (x >= 0 && x < width && y >= 0 && y < height) {
                           fill_pixel(x, y, color);*/
                      }
                   }
              }
          }
      }
    // TODO: Task 2: Update to implement super-sampled rasterization
  }

  void RasterizerImp::rasterize_interpolated_color_triangle(float x0, float y0, Color c0,
    float x1, float y1, Color c1,
    float x2, float y2, Color c2)
  {
    // TODO: Task 4: Rasterize the triangle, calculating barycentric coordinates and using them to interpolate vertex colors across the triangle
    // Hint: You can reuse code from rasterize_triangle
      float min_x = std::min({x0, x1, x2});
      float max_x = std::max({x0, x1, x2});
      float min_y = std::min({y0, y1, y2});
      float max_y = std::max({y0, y1, y2});

      for (int x = (int)min_x; x <= (int)max_x; x++) {
          for (int y = (int)min_y; y <= (int)max_y; y++) {
              // Center of the pixel
              float px = x + 0.5;
              float py = y + 0.5;
              // Point-in-triangle test: Barycentric coordinates
              float alpha = (-(px-x1)*(y2-y1) + (py-y1)*(x2-x1)) / (-(x0-x1)*(y2-y1) + (y0-y1) * (x2-x1));
              float beta = (-(px-x2)*(y0-y2) + (py-y2)*(x0-x2)) / (-(x1-x2)*(y0-y2) + (y1-y2) * (x0-x2));
              float gamma = 1-alpha-beta;
              if (alpha >=0 && beta >= 0 && gamma >= 0) {
                  if (x >= 0 && x < width && y >= 0 && y < height) {
                      Color interpolated_color = c0 * alpha + c1 * beta + c2 * gamma;
                      fill_pixel(x, y, interpolated_color);
                  }
              }
          }
      }
  }


  void RasterizerImp::rasterize_textured_triangle(float x0, float y0, float u0, float v0,
    float x1, float y1, float u1, float v1,
    float x2, float y2, float u2, float v2,
    Texture& tex)
  {
    // TODO: Task 5: Fill in the SampleParams struct and pass it to the tex.sample function.
      SampleParams sp;
      sp.psm = this->psm;
      sp.lsm = this->lsm;
      float min_x = std::min({x0, x1, x2});
      float max_x = std::max({x0, x1, x2});
      float min_y = std::min({y0, y1, y2});
      float max_y = std::max({y0, y1, y2});
      
      for (int x = (int)min_x; x <= (int)max_x; x++) {
          for (int y = (int)min_y; y <= (int)max_y; y++) {
              // Center of the pixel
              float px = x + 0.5;
              float py = y + 0.5;
              // Point-in-triangle test: Barycentric coordinates
              float alpha = (-(px-x1)*(y2-y1) + (py-y1)*(x2-x1)) / (-(x0-x1)*(y2-y1) + (y0-y1) * (x2-x1));
              float beta = (-(px-x2)*(y0-y2) + (py-y2)*(x0-x2)) / (-(x1-x2)*(y0-y2) + (y1-y2) * (x0-x2));
              float gamma = 1-alpha-beta;
              // For (x+1, y)
              float alpha_x_plus_1 = (-(px-x1+1)*(y2-y1) + (py-y1)*(x2-x1)) / (-(x0-x1)*(y2-y1) + (y0-y1) * (x2-x1));
              float beta_x_plus_1 = (-(px+1-x2)*(y0-y2) + (py-y2)*(x0-x2)) / (-(x1-x2)*(y0-y2) + (y1-y2) * (x0-x2));
              float gamma_x_plus_1 = 1-alpha_x_plus_1-beta_x_plus_1;
              // For (x, y+1)
              float alpha_y_plus_1 = (-(px-x1)*(y2-y1) + (py+1-y1)*(x2-x1)) / (-(x0-x1)*(y2-y1) + (y0-y1) * (x2-x1));
              float beta_y_plus_1 = (-(px-x2)*(y0-y2) + (py+1-y2)*(x0-x2)) / (-(x1-x2)*(y0-y2) + (y1-y2) * (x0-x2));
              float gamma_y_plus_1 = 1-alpha_y_plus_1-beta_y_plus_1;
              
              if (alpha >=0 && beta >= 0 && gamma >= 0) {
                  if (x >= 0 && x < width && y >= 0 && y < height) {
                      float u = alpha * u0 + beta * u1 + gamma * u2;
                      float v = alpha * v0 + beta * v1 + gamma * v2;
                      sp.p_uv = Vector2D(u, v);
                      
                      // Calculate UV coordinates for (x+1, y)
                      float u_x_plus_1 = alpha_x_plus_1 * u0 + beta_x_plus_1 * u1 + gamma_x_plus_1 * u2;
                      float v_x_plus_1 = alpha_x_plus_1 * v0 + beta_x_plus_1 * v1 + gamma_x_plus_1 * v2;
                      sp.p_dx_uv = Vector2D(u_x_plus_1, v_x_plus_1) - sp.p_uv;

                      // Calculate UV coordinates for (x, y+1)
                      float u_y_plus_1 = alpha_y_plus_1 * u0 + beta_y_plus_1 * u1 + gamma_y_plus_1 * u2;
                      float v_y_plus_1 = alpha_y_plus_1 * v0 + beta_y_plus_1 * v1 + gamma_y_plus_1 * v2;
                      sp.p_dy_uv = Vector2D(u_y_plus_1, v_y_plus_1) - sp.p_uv;
                      
                      Color tex_color = tex.sample(sp);
                      fill_pixel(x, y, tex_color);
                  }
              }
          }
      }
  }

  void RasterizerImp::set_sample_rate(unsigned int rate) {
    // TODO: Task 2: You may want to update this function for supersampling support
      
    this->sample_rate = rate;

    // Calculate the samples per side
    unsigned int samples_per_side = std::sqrt(sample_rate);

    // Calculate the dimensions of the sample buffer by multiplying roiginal frambuffers w and h
    unsigned int buffer_width = width * samples_per_side;
    unsigned int buffer_height = height * samples_per_side;
    
    // Resize samplebuffer vec to hold all supersampled pixels
    this->sample_buffer.resize(buffer_width * buffer_height, Color::White);
  }


  void RasterizerImp::set_framebuffer_target(unsigned char* rgb_framebuffer,
    size_t width, size_t height)
  {
    // TODO: Task 2: You may want to update this function for supersampling support
    this->width = width;
    this->height = height;
    this->rgb_framebuffer_target = rgb_framebuffer;
      
    unsigned int samples_per_side = std::sqrt(sample_rate);
    unsigned int supersampled_width = width * samples_per_side;
    unsigned int supersampled_height = height * samples_per_side;

    // Resize the sample_buffer to accommodate the supersampled resolution
    this->sample_buffer.resize(supersampled_width * supersampled_height, Color::White);
  }


  void RasterizerImp::clear_buffers() {
    std::fill(rgb_framebuffer_target, rgb_framebuffer_target + 3 * width * height, 255);
    std::fill(sample_buffer.begin(), sample_buffer.end(), Color::White);
  }


  // This function is called at the end of rasterizing all elements of the
  // SVG file.  If you use a supersample buffer to rasterize SVG elements
  // for antialising, you could use this call to fill the target framebuffer
  // pixels from the supersample buffer data.
  void RasterizerImp::resolve_to_framebuffer() {
    // TODO: Task 2: You will likely want to update this function for supersampling support
      // Calculate the samples per side
      unsigned int samples_per_side = std::sqrt(sample_rate);
          for (size_t x = 0; x < width; ++x) {
              for (size_t y = 0; y < height; ++y) {
                  Color avgColor(0, 0, 0);
                  float totalSamples = samples_per_side * samples_per_side;
                  for (size_t sx = 0; sx < samples_per_side; sx++) {
                      for (size_t sy = 0; sy < samples_per_side; sy++) {
                          size_t sampleIndex = (y * samples_per_side + sy) * (width * samples_per_side) + (x * samples_per_side + sx);
                          avgColor += sample_buffer[sampleIndex];
                      }
                  }
                  
                  // This part below done by gpt
                  // Divide each color component by the total num of samples
                  avgColor.r /= totalSamples;
                  avgColor.g /= totalSamples;
                  avgColor.b /= totalSamples;
                  
                  // Convert the avgColor to 8-bit values and write to rgb_framebuffer_target
                  size_t framebufferIndex = 3 * (y * width + x);
                  rgb_framebuffer_target[framebufferIndex] = static_cast<unsigned char>(std::min(255.0f, std::max(0.0f, avgColor.r * 255.0f)));
                  rgb_framebuffer_target[framebufferIndex + 1] = static_cast<unsigned char>(std::min(255.0f, std::max(0.0f, avgColor.g * 255.0f)));
                  rgb_framebuffer_target[framebufferIndex + 2] = static_cast<unsigned char>(std::min(255.0f, std::max(0.0f, avgColor.b * 255.0f)));
              }
          }
  }

  Rasterizer::~Rasterizer() { }


}// CGL
