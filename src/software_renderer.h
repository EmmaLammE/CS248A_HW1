#ifndef CS248_SOFTWARE_RENDERER_H
#define CS248_SOFTWARE_RENDERER_H

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

#ifdef USE_PTHREAD
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#endif

#include "CS248.h"
#include "texture.h"
#include "svg_renderer.h"

namespace CS248 { // CS248

#ifdef USE_PTHREAD
double Get_Current_Time();
double Initialize_Timer();
#endif

class SoftwareRendererRef;

class SoftwareRenderer : public SVGRenderer {
 public:

  SoftwareRenderer( ) : sample_rate (1) { }

  // Free used resources
  virtual ~SoftwareRenderer( ) { }

  // Draw an svg input to pixel buffer
  virtual void draw_svg( SVG& svg ) = 0;

  // Set sample rate
  virtual void set_sample_rate( size_t sample_rate ) = 0;
  
  // Set pixel buffer
  virtual void set_pixel_buffer( unsigned char* pixel_buffer,
                                  size_t width, size_t height ) = 0;

  // Clear pixel buffer
  inline void clear_buffer() {
    memset(pixel_buffer, 255, 4 * width * height);
  }

  // Set texture sampler
  inline void set_tex_sampler( Sampler2D* sampler ) {
    this->sampler = sampler;
  }

  // Set svg to screen transformation
  inline void set_canvas_to_screen( Matrix3x3 canvas_to_screen ) {
    this->canvas_to_screen = canvas_to_screen;
  }

 protected:

  // Sample rate (square root of samples per pixel)
  size_t sample_rate;

  // Pixel buffer memory location
  unsigned char* pixel_buffer; 

  // Pixel buffer dimension (in pixels)
  size_t width; size_t height;

  // SVG outline bbox (in pixels)
	Vector2D svg_bbox_top_left, svg_bbox_bottom_right;

  // Texture sampler being used
  Sampler2D* sampler;

  // SVG coordinates to screen space coordinates
  Matrix3x3 canvas_to_screen;

}; // class SoftwareRenderer


class SoftwareRendererImp : public SoftwareRenderer {
public:

	SoftwareRendererImp(SoftwareRendererRef *ref = NULL) : SoftwareRenderer(), ref(ref) { }
	~SoftwareRendererImp() {
        // Deallocate the supersampled buffer if it has been allocated
        if (supersampled_buffer) {
            delete[] supersampled_buffer;
            supersampled_buffer = nullptr;
        }
    }

	// draw an svg input to pixel buffer
	void draw_svg(SVG& svg);

	// set sample rate
	void set_sample_rate(size_t sample_rate);

	// set pixel buffer
	void set_pixel_buffer(unsigned char* pixel_buffer,
		size_t width, size_t height);

	void fill_sample(int sx, int sy, const Color& color);
	void fill_pixel(int x, int y, const Color& color);

private:
	 // EL - Pixel buffer memory location
	unsigned char* supersampled_buffer; 

	// EL - super sampled buffer dimension (in pixels)
	size_t supersampled_width; size_t supersampled_height;
	// Primitive Drawing //

	// Draws an SVG element
	void draw_element(SVGElement* element);

	// Draws a point
	void draw_point(Point& p);

	// Draw a line
	void draw_line(Line& line);

	// Draw a polyline
	void draw_polyline(Polyline& polyline);

	// Draw a rectangle
	void draw_rect(Rect& rect);

	// Draw a polygon
	void draw_polygon(Polygon& polygon);

	// Draw a ellipse
	void draw_ellipse(Ellipse& ellipse);

	// Draws a bitmap image
	void draw_image(Image& image);

	// Draw a group
	void draw_group(Group& group);

	// Rasterization //

	// rasterize a point
	void rasterize_point(float x, float y, Color color);

	// rasterize a line
	void rasterize_line(float x0, float y0,
		float x1, float y1,
		Color color);

	// rasterize a triangle
	void rasterize_triangle(float x0, float y0,
		float x1, float y1,
		float x2, float y2,
		Color color);

	// rasterize an image
	void rasterize_image(float x0, float y0,
		float x1, float y1,
		Texture& tex);

	// resolve samples to pixel buffer
	void resolve(void);

	// task5 alpha compositing
	Color alpha_blending(Color pixel_color, Color color);

	SoftwareRendererRef *ref;
}; // class SoftwareRendererImp


class SoftwareRendererRef : public SoftwareRenderer {
public:

	SoftwareRendererRef(int thread_count);

	virtual ~SoftwareRendererRef();

	// draw an svg input to pixel buffer
	struct THREAD_DATA
	{
		SoftwareRendererRef* ref;
		SVG* svg;
		int x0, y0;
		int x1, y1;
		Matrix3x3 transformation;
		int tid;
	};

#ifdef USE_PTHREAD
	std::queue<int> queue;

	static void* threaded_run(void* data)
	{
		THREAD_DATA* thread_data = (THREAD_DATA*)data;
		SoftwareRendererRef* ref = thread_data->ref;
		while (1) {
			pthread_mutex_lock(&ref->queue_lock);
			while (ref->queue.empty()) {
				ref->active_threads--;
				if (ref->active_threads == 0) pthread_cond_signal(&ref->done_condition);
				ref->inactive_threads++;
				pthread_cond_wait(&ref->todo_condition, &ref->queue_lock);
				ref->active_threads++;
				ref->inactive_threads--;
			}

			int id = ref->queue.front();
			ref->queue.pop();
			pthread_mutex_unlock(&ref->queue_lock);
			if (id == -1) pthread_exit(0);
			else ref->draw_svg_threaded(&ref->thread_data[id]);
		}
		return 0;
	}

	void draw_svg_threaded(THREAD_DATA* thread_data);
#endif

	void draw_svg(SVG& svg);

	// Clear pixel buffer
	inline void clear_buffer();

	// set sample rate
	void set_sample_rate(size_t sample_rate);

	// set pixel buffer
	void set_pixel_buffer(unsigned char* pixel_buffer,
		size_t width, size_t height);

	// Exposing/reimplementing these functions for CS248

	// alpha blending helper
	Color alpha_blending_helper(Color color1, Color color2);

	// rasterize a line
	void rasterize_line_helper(float x0, float y0,
		float x1, float y1, int width, int height,
		Color color, SoftwareRendererImp* imp);
	
	// EL - rasterize a line using Bresenham's algorithm
	void rasterize_line_bresenham(float x0, float y0, float x1, float y1, Color color, SoftwareRendererImp* imp){
		int dx = std::abs(x1 - x0);
		int dy = -std::abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx + dy;  // error value e_xy
		// cout<<"   x0: "<<x0<<", x1: "<<x1<<", y0: "<<y0<<", y1: "<<y1<<", dx: "<<dx<<", dy: "<<dy<<", sx: "<<sx<<", sy: "<<sy<<", err:"<<err<<endl;
		while (true) {
		// for(int i=0;i<480;i++){
			// rasterize_point(x0, y0, color);  // Draw the pixel at (x0, y0)
			// fill in the nearest pixel
			int ssx = (int)floor(x0);
			int ssy = (int)floor(y0);
			// check bounds
			if (ssx < 0 || ssx >= width) return;
			if (ssy < 0 || ssy >= height) return;
			// fill sample - NOT doing alpha blending!
			// TODO: Call fill_pixel here to run alpha blending
			pixel_buffer[4 * (ssx + ssy * width)] = (uint8_t)(color.r * 255);
			pixel_buffer[4 * (ssx + ssy * width) + 1] = (uint8_t)(color.g * 255);
			pixel_buffer[4 * (ssx + ssy * width) + 2] = (uint8_t)(color.b * 255);
			pixel_buffer[4 * (ssx + ssy * width) + 3] = (uint8_t)(color.a * 255);
			
			if (sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1))<sqrt(1.5)) break;
			int e2 = 2 * err;
			if (e2 >= dy) { 
				err += dy; 
				x0 += sx; 
			}
			if (e2 <= dx) {
				err += dx;
				y0 += sy;
			}
			for (int dxx = 0; dxx < sample_rate; ++dxx) {
                for (int dyy = 0; dyy < sample_rate; ++dyy) {
                    fill_sample(ssx + dxx, ssy + dyy, color);
                    // if(sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1))<sqrt(4)){
                    // cout<<"ssx: "<<ssx<<", ssy:"<<ssy<<", dxx:"<<dxx<<",dyy:"<<dyy<<endl;}
                }
            }
			// cout<<"   err: "<<err<<", err2: "<<e2<<", x0: "<<x0<<", y0: "<<y0<<", color: "<<color<<endl;
		// }
		}
	};

	bool is_inside_triangle(float px, float py, float x0, float y0, float x1, float y1, float x2, float y2) {
    	// Function to check if a point is on the inside side of an edge
    	auto edge_check = [](float ex0, float ey0, float ex1, float ey1, float px, float py) {
			float nx = ey1 - ey0; // Normal x (perpendicular to the edge)
			float ny = ex0 - ex1; // Normal y
			// Vector from edge point to point in question
			float vx = px - ex0;
			float vy = py - ey0;
			// Dot product
			return nx * vx + ny * vy;
		};

    // Check against all three edges
    bool inside0 = edge_check(x0, y0, x1, y1, px, py) <= 0;
    bool inside1 = edge_check(x1, y1, x2, y2, px, py) <= 0;
    bool inside2 = edge_check(x2, y2, x0, y0, px, py) <= 0;

    return inside0 && inside1 && inside2;
	}
private:

	// Primitive Drawing //

	// Draws an SVG element
	void draw_element(SVGElement* element, void* thread_data = NULL);

	// Draws a point
	void draw_point(Point& p, void* thread_data = NULL);

	// Draw a line
	void draw_line(Line& line, void* thread_data = NULL);

	// Draw a polyline
	void draw_polyline(Polyline& polyline, void* thread_data = NULL);

	// Draw a rectangle
	void draw_rect(Rect& rect, void* thread_data = NULL);

	// Draw a polygon
	void draw_polygon(Polygon& polygon, void* thread_data = NULL);

	// Draw a ellipse
	void draw_ellipse(Ellipse& ellipse, void* thread_data = NULL);

	// Draws a bitmap image
	void draw_image(Image& image, void* thread_data = NULL);

	// Draw a group
	void draw_group(Group& group, void* thread_data = NULL);

	// Rasterization //

	// rasterize a point
	void rasterize_point(float x, float y, Color color, void* thread_data = NULL);

	// rasterize a line
	void rasterize_line(float x0, float y0,
		float x1, float y1,
		Color color, void* thread_data = NULL);

	// rasterize a triangle
	void rasterize_triangle(float x0, float y0,
		float x1, float y1,
		float x2, float y2,
		Color color, void* thread_data = NULL);

	void rasterize_ellipse(double cx, double cy,
		double rx, double ry,
		Color color, void* thread_data = NULL);

	// rasterize an image
	void rasterize_image(Image& image);

	// resolve samples to pixel buffer
	void resolve(void);

	// Helpers //
	void fill_sample(float sx, float sy, const Color& c, void* thread_data = NULL);
	void fill_pixel(int x, int y, const Color& c, void* thread_data = NULL);

	// SSAA sample buffer
	std::vector<unsigned char> sample_buffer;

#ifdef USE_PTHREAD
	std::vector<pthread_t> threads;
	pthread_attr_t attr;
	pthread_mutex_t queue_lock;
	pthread_cond_t done_condition, todo_condition;
	int active_threads, inactive_threads;
	int thread_count;
	int sqrt_thread_count;
	std::vector<THREAD_DATA> thread_data;
#endif

}; // class SoftwareRendererRef


} // namespace CS248

#endif // CS248_SOFTWARE_RENDERER_H
