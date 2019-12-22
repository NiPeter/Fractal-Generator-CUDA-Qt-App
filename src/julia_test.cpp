#include <cmath>

#include <julia_set_generator.h>

int main() {
  const unsigned int width = 1500;
  const unsigned int height = 1000;
  const unsigned int max_iterations = 300;
  const double cr = -0.7000;
  const double ci =  0.27015;

  JuliaSetGenerator gen;

  gen.setWidth(width).
  setHeight(height).setMaxIterations(max_iterations).
  setConstantRealis(cr).setConstantImaginalis(ci);

  auto fractal = gen.setZoom(0.6).generate();
  auto img = fractal->get_image();

  std::string file_name = "temp.bmp";
  std::ofstream stream(file_name.c_str(), std::ios::binary);

  if (!stream) {
    std::cerr << "bitmap_image::save_image(): Error - Could not open file "
              << file_name << " for writing!" << std::endl;
    return 0;
  }

  stream.write(reinterpret_cast<const char *>(img.get()), fractal->get_size());

//  char str[] = { 1, 2, 3, 4 };
//  stream.write(str, 4);
//  stream.write(str, 4);

  stream.close();

//  const unsigned int n = 50;

//  double zooms[n];
//  double zoom_start = 0.1;
//  double zoom_end = 0.00001;
//  double step = (zoom_start - zoom_end) / n;

//  std::cout << step << std::endl;
//  return 0;

//  for (size_t i = 1; i < (n + 1); i++) {
//    zooms[i - 1] = i * step;
//  }

//  for (size_t i = 0; i < n; i++) {
//    auto fractal = gen.setZoom(zooms[i]).setOffsetX(0.0999).setOffsetY(0.09899).generate();
//    std::string str;
//    str = "julia_" + std::to_string(zooms[i]) + ".bmp";
//    fractal->save_image(str);
//  }

  return 0;
}

//constexpr size_t KbytesToBytes(size_t bytes) {
//  return 1024 * bytes;
//}

//constexpr size_t MbytesToBytes(size_t kbytes) {
//  return 1024 * KbytesToBytes(kbytes);
//}

//#include <chrono>
//#include <thread>
//int main() {
//  constexpr size_t N = MbytesToBytes(2048);

//  std::cout << N << std::endl;

//  std::unique_ptr<unsigned char[]> data = std::make_unique<unsigned char[]>(N);

////  for (size_t i = 0; i < (N); i++) {
////    data[i] = static_cast<unsigned char>(i);
////  }

//  using namespace std::chrono_literals;
//  std::this_thread::sleep_for(10s);

////  for (size_t i = 0; i < (N); i++) {
////    std::cout << data.get()[i];
////  }

//  return 0;
//}
