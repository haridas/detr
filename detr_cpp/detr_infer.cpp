#include <iostream>
#include <memory>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <torch/script.h> // One-stop header.
//#include <pybind11/pybind11.h>

using namespace cv;
using namespace std;

vector<int> random_scale(Mat image)
{
}

// Scale sizes

int main(int argc, const char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "usage: detr-app <path-to-exported-script-module> <image-path> \n";
    return -1;
  }

  torch::jit::script::Module module;
  try
  {
    // Deserialize the ScriptModule from a file using torch::jit::load().
    cv::Mat image;
    image = cv::imread(argv[2], 1);

    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::Size scale(500, 600);
    cv::resize(image, image, scale);
    image.convertTo(image, CV_32FC3, 1.0f / 255.0f);
    std::cout << "Image: " << image.size();

    auto input_tensor = torch::from_blob(image.data, {1, 500, 600, 3});
    input_tensor = input_tensor.permute({0, 3, 1, 2});
    std::cout << "Tensor: " << input_tensor[0][0].sizes();
    // Apply normalization based on imagenet data.
    input_tensor[0][0] = input_tensor[0][0].sub_(0.485).div_(0.229);
    input_tensor[0][1] = input_tensor[0][1].sub_(0.456).div_(0.224);
    input_tensor[0][2] = input_tensor[0][2].sub_(0.406).div_(0.225);

    module = torch::jit::load(argv[1]);
    // Create a vector of inputs.
    std::vector<torch::jit::IValue> inputs;
    //inputs.push_back(torch::ones({1, 3, 500, 600}));
    inputs.push_back(input_tensor);

    // Execute the model and turn its output into a tensor.
    c10::IValue output = module.forward(inputs);
    std::cout << output;
  }

  catch (const c10::Error &e)
  {
    std::cerr << "error loading the model\n";
    std::cout << e.what() << "\n";
    return -1;
  }

  std::cout << "ok\n";
}
