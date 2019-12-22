#ifndef JULIA_SET_GENERATOR_H
#define JULIA_SET_GENERATOR_H

#include <memory>
#include <complex>
#include <limits>
#include <bitmap_image.hpp>

class JuliaSetGenerator;

/**
 * @brief The JuliaSetGeneratorConfig stores
 * configuration for JuliaSetGenerator
 */
struct JuliaSetGeneratorConfig {
  /*
   * Default constant config values
   */
  constexpr static const unsigned int DEFAULT_WIDTH = 800,
                                      DEFAULT_HEIGHT = 600,
                                      DEFAULT_MAX_INTERATIONS = 500;

  constexpr static const double DEFAULT_CONST_REALIS = -0.7,
                                DEFAULT_CONST_IMAGINALIS = 0.27015;

  JuliaSetGeneratorConfig() : width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT),
    max_iterations_(DEFAULT_MAX_INTERATIONS),
    c_realis_(DEFAULT_CONST_REALIS),
    c_imaginalis_(DEFAULT_CONST_IMAGINALIS),
    zoom_(1.0), off_x_(0.0), off_y_(0.0) {
    w2h_ = static_cast<double>(width_) / height_;
  }

  JuliaSetGeneratorConfig(unsigned int width,
                          unsigned int height,
                          double       c_realis,
                          double       c_imaginalis,
                          unsigned int max_iterations)
    : width_(width), height_(height),
    max_iterations_(max_iterations),
    c_realis_(c_realis),
    c_imaginalis_(c_imaginalis),
    zoom_(1.0), off_x_(0.0), off_y_(0.0) {
    w2h_ = static_cast<double>(width_) / height_;
  }

  unsigned int width_,
               height_,
               max_iterations_;
  double c_realis_,
         c_imaginalis_,
         zoom_,
         off_x_,
         off_y_,
         w2h_;
};

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
    JuliaSetGeneratorConfig cfg_;

  public:
    /**
     * @brief JuliaSetGenerator default constructor.
     *
     * For default values please refer to public static constants of JuliaSetGenerator
     */
    JuliaSetGenerator() : cfg_() {
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
      : cfg_(width, height, c_realis, c_imaginalis, max_iterations) {
    }

    /**
     * @brief getComplexPlaneBoundary returns min and max coordinates
     * of draw plane for currently set paraemters.
     *
     *
     * @param real_min - real part min coordinate
     * @param real_max - real part max coordinate
     * @param imaginalis_min - imaginalis part min coordinate
     * @param imaginalis_max - imaginalis part max coordinate
     */
    void getComplexPlaneBoundary(double *real_min, double *real_max,
                                 double *imaginalis_min, double *imaginalis_max) const {
      if (real_min) *real_min = getComplexPlaneRealCoordinate(0, cfg_);

      if (real_max) *real_max = getComplexPlaneRealCoordinate(cfg_.width_, cfg_);

      if (imaginalis_min) *imaginalis_min = getComplexPlaneImaginalisCoordinate(0, cfg_);

      if (imaginalis_max) *imaginalis_max = getComplexPlaneImaginalisCoordinate(cfg_.height_, cfg_);
    }

    /**
     * @brief setWidth
     * @param width - - output bitmap width in pixels
     * @return reference for "this"
     */
    JuliaSetGenerator& setWidth(unsigned int width) {
      cfg_.width_ = width;
      cfg_.w2h_ = compWidthToHeight(cfg_.width_, cfg_.height_);
      return *this;
    }

    /**
     * @brief setHeight
     * @param height - output bitmap height in pixels
     * @return reference for "this"
     */
    JuliaSetGenerator& setHeight(unsigned int height) {
      cfg_.height_ = height;
      cfg_.w2h_ = compWidthToHeight(cfg_.width_, cfg_.height_);

      return *this;
    }

    /**
     * @brief setConstantRealis
     * @param c_realis - real part of constant c added to z^2 part of julia set equation
     * @return reference for "this"
     */
    JuliaSetGenerator& setConstantRealis(double c_realis) {
      cfg_.c_realis_ = c_realis;
      return *this;
    }

    /**
     * @brief setConstantImaginalis
     * @param c_imaginalis - imaginary part of constant c added to z^2 part of julia set equation
     * @return reference for "this"
     */
    JuliaSetGenerator& setConstantImaginalis(double c_imaginalis) {
      cfg_.c_imaginalis_ = c_imaginalis;
      return *this;
    }

    /**
     * @brief setMaxIterations
     * @param max_iterations - max iterations for pixel
     * @return reference for "this"
     */
    JuliaSetGenerator& setMaxIterations(unsigned int max_iterations) {
      cfg_.max_iterations_ = max_iterations;
      return *this;
    }

    /**
     * @brief setZoom
     * @param zoom
     * @return
     */
    JuliaSetGenerator& setZoom(double zoom) {
      cfg_.zoom_ = zoom;
      return *this;
    }

    /**
     * @brief setOffsetX
     * @param off_x
     * @return
     */
    JuliaSetGenerator& setOffsetX(double off_x) {
      cfg_.off_x_ = off_x;
      return *this;
    }

    /**
     * @brief setOffsetY
     * @param off_y
     * @return
     */
    JuliaSetGenerator& setOffsetY(double off_y) {
      cfg_.off_y_ = off_y;
      return *this;
    }

    /**
     * @brief generate
     * @return unique pointer to generated julia set image
     */
    std::unique_ptr<bitmap_image> generate() {
      using namespace std::complex_literals;

      JuliaSetGeneratorConfig local_cfg = cfg_;

      auto fractal = std::make_unique<bitmap_image>(local_cfg.width_, local_cfg.height_);

      for (unsigned int y = 0; y < local_cfg.height_; ++y) {
        // Compute imaginalis coordinate on complex plane
        double coord_imag = getComplexPlaneImaginalisCoordinate(y, local_cfg);

        for (unsigned int x = 0; x < local_cfg.width_; ++x) {
          unsigned int it = computeCoordinateIterations(
              getComplexPlaneRealCoordinate(x, local_cfg),
              coord_imag,
              local_cfg);

          if (it < std::numeric_limits<unsigned int>::max()) {
            fractal->set_pixel(x, y, iterationsToColor(it, local_cfg));
          }
        }
      }

      return fractal;
    }

  private:


    /**
     * @brief iterationsToColor
     * @param iterations
     * @param cfg
     * @return
     */
    rgb_t iterationsToColor(unsigned int iterations, const JuliaSetGeneratorConfig& cfg) {
      if (iterations != std::numeric_limits<unsigned int>::max()) {
        unsigned int color_index = static_cast<unsigned int>((1000.0 * iterations) / cfg.max_iterations_);

        if (color_index > 1000) color_index = 1000;

        return jet_colormap[color_index];
      }

      return { 0, 0, 0 };
    }

    /**
     * @brief computeCoordinateIterations
     * @param coord_real
     * @param coord_imag
     * @param cfg
     * @return
     */
    unsigned int computeCoordinateIterations(double coord_real, double coord_imag, const JuliaSetGeneratorConfig& cfg) {
      using namespace std::complex_literals;

      // Equation:
      // z_1 = z_0^2+c

      const double c_real = cfg.c_realis_;
      const double c_imag = cfg.c_imaginalis_;


      // z_0 coordinates for first iteration
      double z_0_imag = coord_imag;
      double z_0_real = coord_real;

      // Helper optimisation variables
      double z_0_real_2, // squared z_0_real
             z_0_imag_2; // squared z_0_imag

      unsigned int max_i = cfg.max_iterations_;

      // Iterate ....
      for (unsigned int i = 0; i < max_i; ++i) {
        // Compute squared parts
        z_0_real_2 = z_0_real * z_0_real;
        z_0_imag_2 = z_0_imag * z_0_imag;

        // compute z_1 values and store it in z_0 for next iteration.
        //
        // Normally it could take two steps:
        // 1. compute z_1
        // 2. shift z_1 to z_0
        // This is optimized version. z_1 is only needed in next step as z_0.
        z_0_imag = 2 * z_0_real * z_0_imag + c_imag;
        z_0_real = z_0_real_2 - z_0_imag_2 + c_real;

        // Stop condition |z_1| >= 2
        if ( (z_0_real_2 + z_0_imag_2) >= 4.0) {
          return i;
        }
      }

      return std::numeric_limits<unsigned int>::max();
    }

    /**
     * @brief getComplexPlaneRealCoordinate maps pixel x coord. on drawing
     * to real part coordinate on complex plane
     * @param pixel_x
     * @param cfg generator config
     * @return real part of coordinate in complex plane
     */
    inline static double getComplexPlaneRealCoordinate(double                         pixel_x,
                                                       const JuliaSetGeneratorConfig& cfg) {
      return (cfg.w2h_) * 2.0 * ((2.0 * pixel_x) / cfg.width_ - 1.0) * cfg.zoom_ + cfg.off_x_;
    }

    /**
     * @brief getComplexPlaneImaginalisCoordinate  maps pixel Y coord. on drawing
     * to imaginalis part coordinate on complex plane
     * @param pixel_y
     * @param cfg generator config
     * @return imaginalis part of coordinate in complex plane
     */
    inline static double getComplexPlaneImaginalisCoordinate(double                         pixel_y,
                                                             const JuliaSetGeneratorConfig& cfg) {
      return 2.0 * ((2.0 * pixel_y) / cfg.height_ - 1.0) * cfg.zoom_ - cfg.off_y_;
    }

    /**
     * @brief compWidthToHeight
     * @param width
     * @param height
     * @return
     */
    static constexpr double compWidthToHeight(unsigned int width, unsigned int height) {
      return static_cast<double>(width) / height;
    }
};


#endif // JULIA_SET_GENERATOR_H
