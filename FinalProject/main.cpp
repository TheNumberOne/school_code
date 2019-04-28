#include <iostream>
#include <random>
#include <cmath>
#include <boost/math/quadrature/trapezoidal.hpp>
#include <boost/math/tools/minima.hpp>

int main()
{
    const double min_x = 0.0;
    const double max_x = 8.0;
    const int bits_minima_precision = 20; // approximately 6 decimal digits
    const int num_samples = 100000;
    const int num_bins = 100;
    
    // 1a
    auto p = [](double e)
    {
        return .4865 * std::sinh(std::sqrt(2 * e)) * std::exp(-e);
    };
    // 1b
    double p_total_area = boost::math::quadrature::trapezoidal(p, min_x, max_x);
    std::cout << "Area under p in [" << min_x << ", " << max_x << "] is " << p_total_area << std::endl;
    
    //2a
    auto negative_p = [&](double e) { return -p(e); };
    // 20 binary digit precision = 6 decimal digit precision
    auto[max_e, _] = boost::math::tools::brent_find_minima(negative_p, min_x, max_x, bits_minima_precision);
    // We could use the value returned by brent find minimum but since we're negating the
    //function it won't be correct
    auto max_p = p(max_e);
    std::cout << "Maximum value of P(E) is: E = " << max_e << ", P(E) = " << max_p << std::endl;
    
    
    //3a
    std::random_device r_device;
    std::mt19937 rand(r_device());
    std::uniform_real_distribution x_range{min_x, max_x};
    std::uniform_real_distribution y_range{0.0, max_p};
    
    //4a
    std::vector<std::pair<double, double>> sample;
    
    //5a
    for (int i = 0; i < num_samples; i++) {
        //3a
        auto point = std::make_pair(x_range(rand), y_range(rand));
        
        //4a
        auto[x, y] = point;
        if (y <= p(x)) {
            sample.emplace_back(point);
        }
    }
    //5a
    std::cout << "Number of items in sample: " << sample.size() << std::endl;
    
    //6a
    std::vector<int> bins(num_bins);
    double bin_size = (max_x - min_x) / num_bins;
    for (auto[x, _] : sample) {
        int bin = std::floor((x - min_x) / bin_size);
        bins[bin]++;
    }
    
    std::cout << "Bins:" << std::endl;
    std::cout << "Bin #:";
    for (int i = 0; i < num_bins; i++) {
        std::cout << std::setw(7) << std::right << i;
    }
    std::cout << std::endl;
    
    std::cout << "Count:";
    for (int bin : bins) {
        std::cout << std::setw(7) << std::right << bin;
    }
    std::cout << std::endl;
    
    
    return 0;
}