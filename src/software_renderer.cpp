#include "software_renderer.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#include "triangulation.h"

using namespace std;

namespace CS248 {


// Implements SoftwareRenderer //

// fill a sample location with color
void SoftwareRendererImp::fill_sample(int sx, int sy, const Color &color) {
  // Task 2: implement this function
  // cout<<"sx: "<<sx<<", sy: "<<sy<<", supersampled_width: "<<supersampled_width<<", supersampled_height: "<<supersampled_height<<endl;
  // Calculate the starting supersampled coordinates for the pixel
    int start_sx = sx * sample_rate;
    int start_sy = sy * sample_rate;

    // Iterate over all samples within the pixel area in the supersampled buffer
    // cout<<"start_sx: "<<start_sx<<", start_sy: "<<start_sy<<", sample_rate: "<<sample_rate<<endl;
    for (int dy = 0; dy < sample_rate; ++dy) {
        for (int dx = 0; dx < sample_rate; ++dx) {
            // Calculate the index for each sample within the supersampled buffer
            int sxx = start_sx + dx;
            int syy = start_sy + dy;
            int index = 4 * (sxx + syy * supersampled_width);
            // cout<<"sx: "<<sx<<", sy: "<<sy<<", index: "<<index<<endl;
            // Fill the color for each sample
            supersampled_buffer[index] = (uint8_t)(color.r * 255);
            supersampled_buffer[index + 1] = (uint8_t)(color.g * 255);
            supersampled_buffer[index + 2] = (uint8_t)(color.b * 255);
            supersampled_buffer[index + 3] = (uint8_t)(color.a * 255);
        }
    }
}

// fill samples in the entire pixel specified by pixel coordinates
void SoftwareRendererImp::fill_pixel(int x, int y, const Color &color) {

	// Task 2: Re-implement this function
  Color my_pixel_color(0, 0, 0, 0);
  float sample_count = 0;
  // Iterate over samples within the pixel
  float inv255 = 1.0 / 255.0;
    
	// check bounds
	if (x < 0 || x >= width) return;
	if (y < 0 || y >= height) return;
  // cout<<"x: "<<x<<", y: "<<y<<", width: "<<width<<", height: "<<height<<endl;
	Color pixel_color;
	// float inv255 = 1.0 / 255.0;
	pixel_color.r = pixel_buffer[4 * (x + y * width)] * inv255;
	pixel_color.g = pixel_buffer[4 * (x + y * width) + 1] * inv255;
	pixel_color.b = pixel_buffer[4 * (x + y * width) + 2] * inv255;
	pixel_color.a = pixel_buffer[4 * (x + y * width) + 3] * inv255;
  
	pixel_color = ref->alpha_blending_helper(pixel_color, color);
  if(x==1312 && y==1174){
  // cout<<"EL x: "<<x<<", y: "<<y<<", pixel_color: "<<pixel_color<<", my_pixel_color: "<<my_pixel_color<<", sample_rate: "<<sample_rate<<endl;}
	pixel_buffer[4 * (x + y * width)] = (uint8_t)(pixel_color.r * 255);
	pixel_buffer[4 * (x + y * width) + 1] = (uint8_t)(pixel_color.g * 255);
	pixel_buffer[4 * (x + y * width) + 2] = (uint8_t)(pixel_color.b * 255);
	pixel_buffer[4 * (x + y * width) + 3] = (uint8_t)(pixel_color.a * 255);
}
}

void SoftwareRendererImp::draw_svg( SVG& svg ) {

  // set top level transformation
  transformation = canvas_to_screen;

  // canvas outline
  Vector2D a = transform(Vector2D(0, 0)); a.x--; a.y--;
  Vector2D b = transform(Vector2D(svg.width, 0)); b.x++; b.y--;
  Vector2D c = transform(Vector2D(0, svg.height)); c.x--; c.y++;
  Vector2D d = transform(Vector2D(svg.width, svg.height)); d.x++; d.y++;

  svg_bbox_top_left = Vector2D(a.x+1, a.y+1);
  svg_bbox_bottom_right = Vector2D(d.x-1, d.y-1);
  // cout<<"EL drawing svg"<<endl;
  // draw all elements
  for (size_t i = 0; i < svg.elements.size(); ++i) {
    draw_element(svg.elements[i]);
  }

  // draw canvas outline
  // cout<<"EL drawing canvas outline"<<endl;
  rasterize_line(a.x, a.y, b.x, b.y, Color::Black);
  rasterize_line(a.x, a.y, c.x, c.y, Color::Black);
  rasterize_line(d.x, d.y, b.x, b.y, Color::Black);
  rasterize_line(d.x, d.y, c.x, c.y, Color::Black);

  // resolve and send to pixel buffer
  resolve();

}

void SoftwareRendererImp::set_sample_rate( size_t sample_rate ) {

  // Task 2: 
  // You may want to modify this for supersampling support
  // cout<<"aaaaa\n";
  // cout<<"sample_rate: "<<sample_rate<<endl;
  this->sample_rate = sample_rate;
  if (supersampled_buffer) {
      delete[] supersampled_buffer;
      // cout<<"set_sample_rate: deleted supersampled_buffer\n";
  }
  // Calculate the dimensions for the supersampled buffer
  this->supersampled_width = width * sample_rate;
  // cout<<"supersampled_width: "<<supersampled_width<<endl;
  this->supersampled_height = height * sample_rate;
  // cout<<"supersampled_height: "<<supersampled_height<<endl;
  // // Allocate memory for the supersampled buffer
  supersampled_buffer = new unsigned char[4 * supersampled_width * supersampled_height];
  // cout<<"supersampled_buffer 1: "<<supersampled_buffer<<endl;
  std::fill_n(supersampled_buffer, 4 * supersampled_width * supersampled_height, 255);
  // cout<<"supersampled_buffer 2: "<<supersampled_buffer<<endl;
}

void SoftwareRendererImp::set_pixel_buffer( unsigned char* pixel_buffer,
                                             size_t width, size_t height ) {

  // Task 2: 
  // You may want to modify this for supersampling support
  this->pixel_buffer = pixel_buffer;
  this->width = width;
  this->height = height;
  // Update supersampled buffer dimensions and reallocate memory
  if (supersampled_buffer) {
      delete[] supersampled_buffer;
      // cout<<"deleted supersampled_buffer\n";
  }
  supersampled_width = width * sample_rate;
  // cout<<"set_pixel_buffer supersampled_width: "<<supersampled_width<<endl;
  supersampled_height = height * sample_rate;
  supersampled_buffer = new unsigned char[4 * supersampled_width * supersampled_height];
  // cout<<"set_pixel_buffer supersampled_buffer: "<<supersampled_buffer<<endl;
  std::fill_n(supersampled_buffer, 4 * supersampled_width * supersampled_height, 255);

}

void SoftwareRendererImp::draw_element( SVGElement* element ) {

	// Task 3 (part 1):
	// Modify this to implement the transformation stack
  // Save the current transformation matrix (CTM)
  // Matrix3x3 saved_ctm = ctm;

  // Concatenate the element's transform with the current transformation matrix
  // ctm = ctm * element->transform;
	switch (element->type) {
	case POINT:
		draw_point(static_cast<Point&>(*element));
		break;
	case LINE:
    // cout<<"EL drawing line"<<endl;
		draw_line(static_cast<Line&>(*element));
		break;
	case POLYLINE:
		draw_polyline(static_cast<Polyline&>(*element));
		break;
	case RECT:
		draw_rect(static_cast<Rect&>(*element));
		break;
	case POLYGON:
		draw_polygon(static_cast<Polygon&>(*element));
		break;
	case ELLIPSE:
		draw_ellipse(static_cast<Ellipse&>(*element));
		break;
	case IMAGE:
		draw_image(static_cast<Image&>(*element));
		break;
	case GROUP:
		draw_group(static_cast<Group&>(*element));
		break;
	default:
		break;
	}
  
}


// Primitive Drawing //

void SoftwareRendererImp::draw_point( Point& point ) {

  Vector2D p = transform(point.position);
  rasterize_point( p.x, p.y, point.style.fillColor );

}

void SoftwareRendererImp::draw_line( Line& line ) { 

  Vector2D p0 = transform(line.from);
  Vector2D p1 = transform(line.to);
  // cout<<"EL draw line from "<<p0<<" to "<<p1<<endl;
  // cout<<"canvas width "<< width<<", height "<<height<<endl;
  rasterize_line( p0.x, p0.y, p1.x, p1.y, line.style.strokeColor );

}

void SoftwareRendererImp::draw_polyline( Polyline& polyline ) {

  Color c = polyline.style.strokeColor;

  if( c.a != 0 ) {
    int nPoints = polyline.points.size();
    for( int i = 0; i < nPoints - 1; i++ ) {
      Vector2D p0 = transform(polyline.points[(i+0) % nPoints]);
      Vector2D p1 = transform(polyline.points[(i+1) % nPoints]);
      rasterize_line( p0.x, p0.y, p1.x, p1.y, c );
    }
  }
}

void SoftwareRendererImp::draw_rect( Rect& rect ) {

  Color c;
  
  // draw as two triangles
  float x = rect.position.x;
  float y = rect.position.y;
  float w = rect.dimension.x;
  float h = rect.dimension.y;

  Vector2D p0 = transform(Vector2D(   x   ,   y   ));
  Vector2D p1 = transform(Vector2D( x + w ,   y   ));
  Vector2D p2 = transform(Vector2D(   x   , y + h ));
  Vector2D p3 = transform(Vector2D( x + w , y + h ));
  
  // draw fill
  c = rect.style.fillColor;
  if (c.a != 0 ) {
    rasterize_triangle( p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, c );
    rasterize_triangle( p2.x, p2.y, p1.x, p1.y, p3.x, p3.y, c );
  }

  // draw outline
  c = rect.style.strokeColor;
  if( c.a != 0 ) {
    rasterize_line( p0.x, p0.y, p1.x, p1.y, c );
    rasterize_line( p1.x, p1.y, p3.x, p3.y, c );
    rasterize_line( p3.x, p3.y, p2.x, p2.y, c );
    rasterize_line( p2.x, p2.y, p0.x, p0.y, c );
  }

}

void SoftwareRendererImp::draw_polygon( Polygon& polygon ) {

  Color c;

  // draw fill
  c = polygon.style.fillColor;
  if( c.a != 0 ) {

    // triangulate
    vector<Vector2D> triangles;
    triangulate( polygon, triangles );

    // draw as triangles
    for (size_t i = 0; i < triangles.size(); i += 3) {
      Vector2D p0 = transform(triangles[i + 0]);
      Vector2D p1 = transform(triangles[i + 1]);
      Vector2D p2 = transform(triangles[i + 2]);
      rasterize_triangle( p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, c );
    }
  }

  // draw outline
  c = polygon.style.strokeColor;
  if( c.a != 0 ) {
    int nPoints = polygon.points.size();
    for( int i = 0; i < nPoints; i++ ) {
      Vector2D p0 = transform(polygon.points[(i+0) % nPoints]);
      Vector2D p1 = transform(polygon.points[(i+1) % nPoints]);
      rasterize_line( p0.x, p0.y, p1.x, p1.y, c );
    }
  }
}

void SoftwareRendererImp::draw_ellipse( Ellipse& ellipse ) {

  // Advanced Task
  // Implement ellipse rasterization

}

void SoftwareRendererImp::draw_image( Image& image ) {

  // Advanced Task
  // Render image element with rotation

  Vector2D p0 = transform(image.position);
  Vector2D p1 = transform(image.position + image.dimension);

  rasterize_image( p0.x, p0.y, p1.x, p1.y, image.tex );
}

void SoftwareRendererImp::draw_group( Group& group ) {

  for ( size_t i = 0; i < group.elements.size(); ++i ) {
    draw_element(group.elements[i]);
  }

}

// Rasterization //

// The input arguments in the rasterization functions 
// below are all defined in screen space coordinates

void SoftwareRendererImp::rasterize_point( float x, float y, Color color ) {

  // fill in the nearest pixel
  int sx = (int)floor(x);
  int sy = (int)floor(y);

  // check bounds
  if (sx < 0 || sx >= width) return;
  if (sy < 0 || sy >= height) return;

  // fill sample - NOT doing alpha blending!
  // TODO: Call fill_pixel here to run alpha blending
  pixel_buffer[4 * (sx + sy * width)] = (uint8_t)(color.r * 255);
  pixel_buffer[4 * (sx + sy * width) + 1] = (uint8_t)(color.g * 255);
  pixel_buffer[4 * (sx + sy * width) + 2] = (uint8_t)(color.b * 255);
  pixel_buffer[4 * (sx + sy * width) + 3] = (uint8_t)(color.a * 255);
  fill_pixel(sx, sy, color);
  // cout<<"EL coloring pixel sx "<<sx<<", sy: "<<sy<<", pixel_buffer: "<<pixel_buffer<<endl;
  for (int dx = 0; dx < sample_rate; ++dx) {
        for (int dy = 0; dy < sample_rate; ++dy) {
            fill_sample(sx + dx, sy + dy, color);
        }
    }
}

void SoftwareRendererImp::rasterize_line( float x0, float y0,
                                          float x1, float y1,
                                          Color color) {

  // Task 0: 
  // Implement Bresenham's algorithm (delete the line below and implement your own)
  // ref->rasterize_line_helper(x0, y0, x1, y1, width, height, color, this);
  ref->rasterize_line_bresenham(x0, y0, x1, y1, color, this);

  // Advanced Task
  // Drawing Smooth Lines with Line Width
}

void SoftwareRendererImp::rasterize_triangle( float x0, float y0,
                                              float x1, float y1,
                                              float x2, float y2,
                                              Color color ) {
  // Task 1: 
  // Implement triangle rasterization
  // Step 1: rearrange points in counter-closwise order
  // Calculate the signed area of the triangle
    float area = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);

    // If area is negative, the points are in clockwise order
    if (area < 0) {
        // Swap points to ensure counter-clockwise order
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    // step 2: find the bounding box to reduce computing time
    int minX = std::min({x0, x1, x2});
    int maxX = std::max({x0, x1, x2});
    int minY = std::min({y0, y1, y2});
    int maxY = std::max({y0, y1, y2});
    // std::cout<<"minX: "<<minX<<", maxX: "<<maxX<<", minY: "<<minY<<", maxY: "<<maxY<<std::endl;
    // step 3: Iterate over the bounding box of the triangle
    for (int px = minX; px <= maxX; px++) {
        for (int py = minY; py <= maxY; py++) {
            // Pixel center
            float pcx = px + 0.5f;
            float pcy = py + 0.5f;

    //         // Check if the pixel center is inside the triangle
            if (ref->is_inside_triangle(pcx, pcy, x0, y0, x1, y1, x2, y2)) {
    //             // std::cout<<"rasterizing point at: "<<pcx<<", "<<pcy<<std::endl;
                // rasterize_point(pcx, pcy, color);  // Draw the pixel
                
                int ssx = (int)floor(pcx);
                int ssy = (int)floor(pcy);
                // check bounds
                if (ssx < 0 || ssx >= width) return;
                if (ssy < 0 || ssy >= height) return;
                // fill sample - NOT doing alpha blending!
                // TODO: Call fill_pixel here to run alpha blending
                pixel_buffer[4 * (ssx + ssy * width)] = (uint8_t)(color.r * 255);
                pixel_buffer[4 * (ssx + ssy * width) + 1] = (uint8_t)(color.g * 255);
                pixel_buffer[4 * (ssx + ssy * width) + 2] = (uint8_t)(color.b * 255);
                pixel_buffer[4 * (ssx + ssy * width) + 3] = (uint8_t)(color.a * 255);
                for (int dx = 0; dx < sample_rate; ++dx) {
                    for (int dy = 0; dy < sample_rate; ++dy) {
                        fill_sample(ssx + dx, ssy + dy, color);
                        // if(px==0 && py==0){
                        // cout<<"ssx: "<<ssx<<", ssy:"<<ssy<<", dx:"<<dx<<",dy:"<<dy<<endl;}
                    }
                }
            }
        }
    }


  // Advanced Task
  // Implementing Triangle Edge Rules

}

void SoftwareRendererImp::rasterize_image( float x0, float y0,
                                           float x1, float y1,
                                           Texture& tex ) {
  // Task 4: 
  // Implement image rasterization
  int dest_width = static_cast<int>(x1 - x0);
  int dest_height = static_cast<int>(y1 - y0);

  // Calculate the step size for u and v texture coordinates
  float u_step = 1.0f / dest_width;
  float v_step = 1.0f / dest_height;

  for (int i = 0; i < dest_width; ++i) {
    for (int j = 0; j < dest_height; ++j) {
      // Calculate normalized texture coordinates for the current pixel
      float u = i * u_step;
      float v = j * v_step;
      u += 0.5f * u_step;
      v += 0.5f * v_step;
      // Use bilinear sampling to get the color from the texture
      Color sampled_color = sampler->sample_bilinear(tex, u, v, 0);
      // Convert the texture coordinates back to screen coordinates
      int screen_x = static_cast<int>(x0 + i);
      int screen_y = static_cast<int>(y0 + j);
      rasterize_point(screen_x, screen_y, sampled_color);
    }
  }
}

// resolve samples to pixel buffer
void SoftwareRendererImp::resolve( void ) {

  // Task 2: 
  // Implement supersampling
  // You may also need to modify other functions marked with "Task 2".
  for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            float r = 0, g = 0, b = 0, a = 0;
            for (size_t dy = 0; dy < sample_rate; dy++) {
                for (size_t dx = 0; dx < sample_rate; dx++) {
                    size_t index = 4 * ((x * sample_rate + dx) + (y * sample_rate + dy) * supersampled_width);
                    r += supersampled_buffer[index];
                    g += supersampled_buffer[index + 1];
                    b += supersampled_buffer[index + 2];
                    a += supersampled_buffer[index + 3];
                    // if(x==600 && y==700){
                    // cout<<"  x: "<<x<<", y: "<<y<<", dx: "<<dx<<", dy: "<<dy<<", supersampled_buffer: "<<r<<endl;}
                }
            }
            size_t count = sample_rate * sample_rate;
            pixel_buffer[4 * (x + y * width)] = r / count;
            pixel_buffer[4 * (x + y * width) + 1] = g / count;
            pixel_buffer[4 * (x + y * width) + 2] = b / count;
            pixel_buffer[4 * (x + y * width) + 3] = a / count;
            // if(x==600 && y==700){
            // cout<<"pixel_buffer: "<<r / count<<"\n-------";}
        }
    }
}

Color SoftwareRendererImp::alpha_blending(Color pixel_color, Color color)
{
  // Task 5
  // Implement alpha compositing
  float alpha = color.a;
    
    // Perform alpha blending for each color channel
    float r = alpha * color.r + (1 - alpha) * pixel_color.r;
    float g = alpha * color.g + (1 - alpha) * pixel_color.g;
    float b = alpha * color.b + (1 - alpha) * pixel_color.b;

    // The alpha of the resulting color should be set based on the blending,
    // assuming the background (pixel_color) is opaque.
    float a = 1.0f; // If the background can be transparent, this needs to be adjusted.

    return Color(r, g, b, a);
}


} // namespace CS248
