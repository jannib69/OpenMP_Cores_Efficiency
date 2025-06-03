#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>
#include <fstream>
#include <cmath>
#include <limits>

// Generiraj podatke
void generate_data(std::vector<double>& x, std::vector<double>& y, int n) {
    std::mt19937 rng(42);
    std::uniform_real_distribution<> dist_x(0, 100);
    std::normal_distribution<> noise(0, 5);
    for (int i = 0; i < n; ++i) {
        x[i] = dist_x(rng);
        y[i] = 3.5 * x[i] + 7 + noise(rng);
    }
}

// Linearna regresija
void linear_regression(const std::vector<double>& x, const std::vector<double>& y, double& a, double& b) {
    double x_mean = 0.0, y_mean = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        x_mean += x[i];
        y_mean += y[i];
    }
    x_mean /= x.size();
    y_mean /= y.size();

    double num = 0.0, den = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        num += (x[i] - x_mean) * (y[i] - y_mean);
        den += (x[i] - x_mean) * (x[i] - x_mean);
    }

    a = num / den;
    b = y_mean - a * x_mean;
}

// RMSE izračun
double compute_rmse(const std::vector<double>& x, const std::vector<double>& y, double a, double b) {
    double sum_sq_error = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double y_pred = a * x[i] + b;
        sum_sq_error += (y[i] - y_pred) * (y[i] - y_pred);
    }
    return std::sqrt(sum_sq_error / x.size());
}

int main() {
    const int N = 10'000'000;
    const int REPEAT = 100;
    std::vector<int> thread_counts = {1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<double> x(N), y(N);
    generate_data(x, y, N);

    std::ofstream csv("timing_results.csv");
    csv << "threads,time_seconds,best_rmse,a,b\n";

    for (int threads : thread_counts) {
        omp_set_num_threads(threads);
        std::cout << "Zagon z " << threads << " threadi..." << std::endl;

        double best_rmse = std::numeric_limits<double>::max();
        double best_a = 0.0, best_b = 0.0;

        auto start = std::chrono::high_resolution_clock::now();

        #pragma omp parallel
        {
            double local_a = 0.0, local_b = 0.0;
            double local_best_rmse = std::numeric_limits<double>::max();
            double local_best_a = 0.0, local_best_b = 0.0;

            #pragma omp for
            for (int i = 0; i < REPEAT; ++i) {
                double a = 0.0, b = 0.0;
                linear_regression(x, y, a, b);
                double rmse = compute_rmse(x, y, a, b);
                if (rmse < local_best_rmse) {
                    local_best_rmse = rmse;
                    local_best_a = a;
                    local_best_b = b;
                }
            }

            #pragma omp critical
            {
                if (local_best_rmse < best_rmse) {
                    best_rmse = local_best_rmse;
                    best_a = local_best_a;
                    best_b = local_best_b;
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        double seconds = std::chrono::duration<double>(end - start).count();

        std::cout << "Čas: " << seconds << " s | Najboljši RMSE: " << best_rmse
                  << " | a = " << best_a << " | b = " << best_b << "\n\n";

        csv << threads << "," << seconds << "," << best_rmse << "," << best_a << "," << best_b << "\n";
    }

    csv.close();
    std::cout << "Shranjeno v timing_results.csv\n";
    return 0;
}