#ifndef CS248_VIEWPORT_H
#define CS248_VIEWPORT_H

#include "CS248.h"
#include "svg.h"

namespace CS248 {

class Viewport {
 public:

  Viewport( ) : svg_2_norm( Matrix3x3::identity() ) { }
  // Matrix3x3 canvas_to_norm;
  inline Matrix3x3 get_canvas_to_norm() {
    return svg_2_norm;
  }

  inline void set_canvas_to_norm( Matrix3x3 m ) {
    svg_2_norm = m;
  }

  // set viewbox to look at (x,y) in svg coordinate space. Span defineds 
  // the view radius of the viewbox in number of pixels (the amout of pixels
  // included in the viewbox in both x and y direction).
  virtual void set_viewbox( float x, float y, float span ) = 0;

  // Move the viewbox by (dx,dy) in svg coordinate space. Scale the the view 
  // range by scale.
  virtual void update_viewbox( float dx, float dy, float scale ) = 0;

 protected:

  // current viewbox properties
  float x, y, span;

  // SVG coordinate to normalized display coordinates
  Matrix3x3 svg_2_norm;

}; // class Viewport


class ViewportImp : public Viewport {
 public:
  
  virtual void set_viewbox( float x, float y, float size );
  virtual void update_viewbox( float dx, float dy, float scale );

}; // class ViewportImp


class ViewportRef : public Viewport {
 public:
  
  virtual void set_viewbox( float x, float y, float size );
  virtual void update_viewbox( float dx, float dy, float scale );

}; // class ViewportRef


} // namespace CS248

#endif // CS248_VIEWPORT_H
