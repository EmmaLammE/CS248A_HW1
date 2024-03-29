#ifndef CS248_DRAWSVG_H
#define CS248_DRAWSVG_H

#include <vector>

#include "CS248.h"
#include "renderer.h"
#include "svg.h"
#include "software_renderer.h"
#include "GLFW/glfw3.h"

namespace CS248 {

/**
 * The SVG renderer draws SVG files.
 */
class DrawSVG : public Renderer {
 public:

  /**
   * Constructor.
   * Creates a new SVG renderer and use the given draw method.
   * \param method Draw method to use.
   */
  DrawSVG() : 
    leftDown (false),
    sample_rate (1),
    current_tab (0),
    show_diff (false),
    show_zoom (false),
    norm_to_screen ( Matrix3x3::identity() )  { }

  /**
   * Destructor.
   * Destroys the drawsvg instance and frees all the resources used.
   * This includes all the loaded svg's, the framebuffer and the sample
   * buffer that is handed to the software renderer. 
   */
  ~DrawSVG( void );

  // BEGIN Implements Renderer //

  std::string name ( void );
  std::string info ( void );

  void init( void );
  void render( void );

  void resize( size_t width, size_t height );

  void keyboard_event(int key, int event, unsigned char mods);
  void char_event( unsigned int key );
  void mouse_event(int key, int event, unsigned char mods);
  void cursor_event( float x, float y );
  void scroll_event( float offset_x, float offset_y );

  // END Implements renderer  //

  /**
   * Clears out the previous render.
   */
  void clear( void );

  /** 
   * Draw a SVG illustration.
   */
  void drawIllustration( SVG& svg );

  /**
   * Load a svg into a new tab if there is one available.
   */
  void newTab( SVG* svg );

  /**
   * Delete a tab and in the renderer.
   */
  void delTab(size_t tab_index);

  /**
   * Switch to a tab.
   */
  void setTab(size_t tab_index);

  /**
   * Get the number of pixels different from the reference.
   */
  int getErrorCount( void ) const;

 private:

  /* window size */
  size_t width, height;

  /* left button clicked */
  bool leftDown;

  /* cursor position */
  float cursor_x; float cursor_y;
  
  /* info to post to viewer osd */
  std::string osd;

  /* software renderer */
  SoftwareRenderer* software_renderer;
  SoftwareRenderer* software_renderer_imp;
  SoftwareRenderer* software_renderer_ref;

  /* texture sampler */
  Sampler2D* sampler;
  Sampler2D* sampler_imp;
  Sampler2D* sampler_ref;

  /* tabs */
  std::vector<SVG*> tabs; size_t current_tab;
  std::vector<Viewport*> viewport_imp;
  std::vector<Viewport*> viewport_ref;
  
  /* diff */
  bool show_diff;
  bool normalize_diff;
  void draw_diff();
  
  /* zoom */
  bool show_zoom;
  void draw_zoom();

  /* samples rate (sqrt(s/pix)) */
  size_t sample_rate;
  void inc_sample_rate();
  void dec_sample_rate();

  /* regenerate mipmap */
  void regenerate_mipmap(size_t tab_index);

  /* audo-adjust canvas_to_norm */
  void auto_adjust(size_t tab_index);

  /* normalized coordiantes to screen coordinates */
  Matrix3x3 norm_to_screen;

  /* saved canvas_to_norm transformations */
  std::vector<Matrix3x3> viewport_save_imp;
  std::vector<Matrix3x3> viewport_save_ref;

  /* framebuffer for software renderer */
  std::vector<unsigned char> framebuffer;

  // update framebuffer
  void redraw();

  /* update framebuffer for software renderer */
  void display_pixels( const unsigned char* pixels ) const;

};

} // namespace CS248

#endif // CS248_DRAWSVG_H
