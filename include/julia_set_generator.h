#ifndef JULIA_SET_GENERATOR_H
#define JULIA_SET_GENERATOR_H

#include <memory>
#include <complex>
#include <bitmap_image.hpp>
#include <iostream>
/**
 * @brief The JuliaSetGenerator class generates a bitmap of
 * the juli set for the given parameters.
 *
 * For parameters description refer to JuliaSetGenerator constructors.
 *
 * Code base found at https://www.partow.net/programming/bitmap/index.html#simpleexample04
 * Also bitmap library comes from that site :)
 *
 * Very thanks arash@partow.net for Your work!
 *
 */
class JuliaSetGenerator {
  private:
    unsigned int width_,
                 height_,
                 max_iterations_;
    double c_realis_,
           c_imaginalis_,
           zoom_,
           off_x_,
           off_y_;
  public:

    /*
     * Default constant config values
     */
    constexpr static const unsigned int DEFAULT_WIDTH = 800,
                                        DEFAULT_HEIGHT = 600,
                                        DEFAULT_MAX_INTERATIONS = 500;

    constexpr static const double DEFAULT_CONST_REALIS = -0.7,
                                  DEFAULT_CONST_IMAGINALIS = 0.27015;


    /**
     * @brief JuliaSetGenerator default constructor.
     *
     * For default values please refer to public static constants of JuliaSetGenerator
     */
    JuliaSetGenerator()
      : width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT),
      max_iterations_(DEFAULT_MAX_INTERATIONS),
      c_realis_(DEFAULT_CONST_REALIS), c_imaginalis_(DEFAULT_CONST_IMAGINALIS),
      zoom_(1.0), off_x_(0.0), off_y_(0.0) {
    }

    /**
     * @brief JuliaSetGenerator full parameter constructor
     *
     * For more info refere to wiki:
     * https://en.wikipedia.org/wiki/Julia_set
     *
     * @param width - output bitmap width in pixels
     * @param height - output bitmap height in pixels
     * @param c_realis - real part of constant c added to z^2 part of julia set equation
     * @param c_imaginalis - imaginary part of constant c added to z^2 part of julia set equation
     * @param max_iterations - max iterations for pixel
     */
    JuliaSetGenerator(unsigned int width,
                      unsigned int height,
                      double       c_realis,
                      double       c_imaginalis,
                      unsigned int max_iterations)
      : width_(width), height_(height),
      max_iterations_(max_iterations),
      c_realis_(c_realis), c_imaginalis_(c_imaginalis),
      zoom_(1.0), off_x_(0.0), off_y_(0.0) {
    }

    /**
     * @brief setWidth
     * @param width - - output bitmap width in pixels
     * @return reference for "this"
     */
    JuliaSetGenerator& setWidth(unsigned int width) {
      width_ = width;
      return *this;
    }

    /**
     * @brief setHeight
     * @param height - output bitmap height in pixels
     * @return reference for "this"
     */
    JuliaSetGenerator& setHeight(unsigned int height) {
      height_ = height;
      return *this;
    }

    /**
     * @brief setConstantRealis
     * @param c_realis - real part of constant c added to z^2 part of julia set equation
     * @return reference for "this"
     */
    JuliaSetGenerator& setConstantRealis(double c_realis) {
      c_realis_ = c_realis;
      return *this;
    }

    /**
     * @brief setConstantImaginalis
     * @param c_imaginalis - imaginary part of constant c added to z^2 part of julia set equation
     * @return reference for "this"
     */
    JuliaSetGenerator& setConstantImaginalis(double c_imaginalis) {
      c_imaginalis_ = c_imaginalis;
      return *this;
    }

    /**
     * @brief setMaxIterations
     * @param max_iterations - max iterations for pixel
     * @return reference for "this"
     */
    JuliaSetGenerator& setMaxIterations(unsigned int max_iterations) {
      max_iterations_ = max_iterations;
      return *this;
    }

    /**
     * @brief setZoom
     * @param zoom
     * @return
     */
    JuliaSetGenerator& setZoom(double zoom) {
      zoom_ = zoom;
      return *this;
    }

    /**
     * @brief setOffsetX
     * @param off_x
     * @return
     */
    JuliaSetGenerator& setOffsetX(double off_x) {
      off_x_ = off_x;
      return *this;
    }

    /**
     * @brief setOffsetY
     * @param off_y
     * @return
     */
    JuliaSetGenerator& setOffsetY(double off_y) {
      off_y_ = off_y;
      return *this;
    }

    /**
     * @brief generate
     * @return unique pointer to generated julia set image
     */
    std::unique_ptr<bitmap_image> generate() {
      auto fractal = std::make_unique<bitmap_image>(width_, height_);
      double w2h = static_cast<double>(width_) / height_;

      double prevr, previ;

      for (unsigned int y = 0; y < fractal->height(); ++y) {
        for (unsigned int x = 0; x < fractal->width(); ++x) {
          double nextr =  w2h * (2.0 * zoom_ * x / fractal->width() - zoom_ + off_x_);
          double nexti =  (2.0 * zoom_ * y / fractal->height() - zoom_ + off_y_);
          bool b = false;

          for (unsigned int i = 0; i < max_iterations_; ++i) {
            prevr = nextr;
            previ = nexti;

            nextr =     prevr * prevr - previ * previ + c_realis_;
            nexti = 2 * prevr * previ + c_imaginalis_;

//            double nextr_2 = nextr * nextr;
//            double nexti_2 = nexti * nexti;

            double sum_squares = nextr * nextr + nexti * nexti;

            if (sum_squares > 4) {
              double it = (i + 2 - log(log(sum_squares) / log(2)) / log(2));
              unsigned int c_i = static_cast<unsigned int>((1000.0 * it) / max_iterations_);

              if (c_i > 1000) c_i = 1000;

              rgb_t c = jet_colormap[c_i];

              fractal->set_pixel(x, y, c);
              b = true;
              break;
            }
          }

          if (!b) {
            rgb_t c;
            c.red = 0;
            c.blue = 0;
            c.green = 0;

            fractal->set_pixel(x, y, c);
          }
        }
      }

      return fractal;
    }
};


#endif // JULIA_SET_GENERATOR_H
